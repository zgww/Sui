// urgc.cpp
//

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <mutex>
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>
#include <unordered_map>

#include <cassert>

#include "Urgc.h"
#include "urgc_api.h"


//有timer/多线程资源加载，必须用锁？后续可以改为每个线程自己一个队列，就不用锁了
//开不开锁，好像基本没有影响.之前测试多了2Ms，似乎是加载资源时，每个资源创建了一个线程，所以慢?
//把资源线程注释掉后，
//1) 不释放内存（打开NO_URGC_REF)，EditorMain.react耗时约3-4ms
//2) 正常urgc:耗时约5-6ms
//3) 正常urgc,但不使用锁:耗时约5-6ms; 说明不是锁的问题?
//4) 正常urgc,但不使用锁,Ref/urgc.ref/urgc.deref 都加上inline:耗时约5-6ms; 说明不是锁的问题?
//5) 正常urgc,但不使用锁,Ref/urgc.ref/urgc.deref 都加上Inline,事件收集改vector=>array:耗时约4-5ms; vector还是有点影响？
//6) 正常urgc,但不使用锁,Ref/urgc.ref/urgc.deref 都加上Inline,事件收集改vector=>array,local里去掉typeid:耗时约3-5ms; typeid有点影响？
//7) 正常urgc,local里去掉typeid:耗时约4-6ms; typeid有点影响哈
//结论，urgc对性能的影响在gui场景下，影响较小，可接受；可选的优化方法有：
//1) 事件收集vector=>array 
//2) 去掉锁(未测试实际影响)
//4) 语言提供机制。确保urgc对实例化的影响就是多了两条指令（进入scope和离开scope)
//3) 直接在硬件层加指令。避开锁的影响

//可优化为 thread_local 队列，免去锁。 队列push_back,直接用数组实现

/*
objpool: [v] nice; is faster; 
on notebook first window :
nourgc + new : 14ms;
urgc + new: 23ms;
urgc + pool(recursive_mutex) :20ms
urgc + pool(spinlock) : 19ms;
nourgc + pool(spinlock) :14ms;
urgc(spinlock) + pool(spinlock):18ms; slower ? ? why
*/

#define USE_LOCK 
//注意，如果关闭GC_THREAD,同时有别的线程ref/deref,就会导致数据异常;因为非多线程，未使用uselock
#define USE_GC_THREAD

//各线程单独队列时，需要打开
// 有问题。 开多线程后，CtorGuard 就没办法保证.就有可能会强引用成环了
#define DEFER_DELETE

//让GC_THREAD直接返回
//#define EMPTY_GC_THREAD

#ifdef NO_URGC_REF
static Urgc *_urgc = NULL;// = new Urgc(); //不释放。防止程序结束时，无序提早释放了urgc
#else
static Urgc *_urgc = new Urgc(); //不释放。防止程序结束时，无序提早释放了urgc
#endif
Urgc& urgc = *_urgc;
//static unsigned long ROOT_REF = -1l;

static std::vector<void*> free_later_list;
static std::vector<void*> free_ing_list;
static std::mutex free_later_mutex;

//批量延迟删除
static void do_free_later(){
	{
		//防止锁住太久
		std::lock_guard<std::mutex> g(free_later_mutex);
		//交换
		free_later_list.swap(free_ing_list);
	}
	for (auto p : free_ing_list){
		free(p);
	}
	free_ing_list.clear();
}

/*
 入引用管理
 */

static long long g_gid = 0;
RefMgr::RefMgr()
{
	this->gid = g_gid++;
	target = nullptr;
}
RefMgr::RefMgr(void *_target) : target(_target)
{
	/*char data[1][2][3][4];
	auto v = data[0];*/
	this->gid = g_gid++;
}
//设置强引用
void RefMgr::set_unit_source(void *obj)
{
	unit_source = obj;
	ghost_source = nullptr;
	// printf("\t设置强引用:%p=>%p\n", obj, target);
}

void RefMgr::ref(void *source)
{
	//第一次引用，直接
	//没有强引用, 就占据
	if (!unit_source)//all_sources.size() == 0)
	{
		unit_source = source;
		// printf("\t第一次引用。记录唯一引用:%p=>%p\n", source, target);
	}
	all_sources.push_back(source);
}
//从all_sources删除第一个source
void RefMgr::remove_first_matched_source_from_all_sources(void *source)
{
	// printf("删除出引用 s=%p\n", source);
	// printf("删除出引用 s=%p size=%d\n", source, all_sources.size());
	for (auto it = begin(all_sources); it != end(all_sources); it++)
	{
		if (*it == source)
		{
			all_sources.erase(it);
			return;
			// break;
		}
	}
	// printf("\t删除出引用 s=%p\n", source);
	// printf("\n\tXXXXXXXXXX  删除非unique引用异常.未找到引用记录:%p => %p\n\n", source, this->target);
}
//std::unordered_map<long long, RefMgr> deletedMap;
void RefMgr::delete_target()
{
	//auto it = deletedMap.find((long long)target);
	//isDeleted = it != deletedMap.end();
	//if (isDeleted) {
	//	conflictRefMgr = &it->second;
	//}
	//if (target) {
	//	int addr = target ? 0 : isDeleted;
	//	target = (void*)(((long long)target) + (addr));

	//}
	//if (isDeleted) {
	//	printf("self:%p,conflictRefMgr:%p, gid:%lld,%lld, %d target:%p,   conflictTarget:%p %d\n", 
	//		this, conflictRefMgr, this->gid, conflictRefMgr->gid, this->gid == conflictRefMgr->gid, 
	//		target, conflictRefMgr->target, target == conflictRefMgr->target);
	//}
	//printf("delete target:%s\n", typeid(*(GcObj*)target).name());
	//if (true) return;
	if (deleter == nullptr)
	{
		auto tmp = (GcObj*)target;
		//printf("delete target :%s\n", typeid(*tmp).name());
		printf("delete target :%p\n", target);
		delete (GcObj*)target;
	}
	else
	{
		//printf("deleter target :%p\n", target);
		deleter(target);
	}

	deleted = true;//表示已经删除

	//deletedMap[(long long)target] = *this;
	//后面还要用target来查找
	//target = nullptr;
}

void RefMgr::setDeleter(std::function<void(void*)> deleter)
{
	if (this->deleter != nullptr) {
		auto tmp = (GcObj*)target;
		printf("异常:覆盖了对象的deleter %p\n", tmp);
		throw std::exception("异常:覆盖了对象的deleter\n");
	}
	this->deleter = deleter;
}



/*唯一强引用gc*/
//通过被引用者查找入引用管理
RefMgr *Urgc::get_ref_mgr_by_target(void *target)
{
	if (target_in_ref_mgr.find(target) != target_in_ref_mgr.end())
	{
		return &target_in_ref_mgr[target];
	}
	return nullptr;
}
Urgc::Urgc() {
	//int a = 0;
	//printf("%d\n", a);
}
//urgc全局变量，有可能早释放了。  导致Ref<XX>全局变量(晚释放，全局变量释放顺序也是无序)访问到异常的内存
Urgc::~Urgc() {
	//int a = 0;
	//printf("%d\n", a);
}
//不存在就创建 入引用
RefMgr *Urgc::goc_ref_mgr_by_target(void *target, std::function<void(void *)> deleter)
{
	RefMgr *mgr = get_ref_mgr_by_target(target);
	if (mgr == nullptr)
	{
		RefMgr tmp(target);
		tmp.deleter = deleter;
		target_in_ref_mgr[target] = tmp;
	}
	mgr = get_ref_mgr_by_target(target);
	if (deleter && !mgr->deleter) {
		mgr->setDeleter(deleter);
		//mgr->deleter = deleter;
	}
	return mgr;
}
//source-target构成Key. 用来唯一引用一个RefMgr
string Urgc::fmt_key(void *source, void *target)
{
	char ckey[64];
	sprintf(ckey, "%p-%p", source, target);
	return string(ckey);
}
//thread_local vector<RefEventItem>* items = new vector<RefEventItem>(20000);
//thread_local RefEventItem* items2 = new RefEventItem[20000];
//thread_local int items2Len = 0;
class EventLists;
extern vector<EventLists*> eventListsAllThreads;
bool _mainThreadStarted = 0;

static mutex& getMutexForMakeEventLists() {
	//使用静态变量，来避开   thread_local/全局变量初始化顺序不确定的问题。
	static mutex eventListsLock;
	return eventListsLock;
}
class EventLists {
public:
	~EventLists();
	RefEventItemList* collecting = new RefEventItemList(10000);
	RefEventItemList* processing = new RefEventItemList(10000);
}; 
EventLists::~EventLists() {
	std::lock_guard<mutex> g(getMutexForMakeEventLists());
	eventListsAllThreads.erase(
		std::find(eventListsAllThreads.begin(), eventListsAllThreads.end(), this));
}

vector<EventLists*> eventListsAllThreads;

static EventLists* makeEventLists(){
	//if (!_mainThreadStarted) { //主线程（含）之前的线程，不需要eventlists
	//	return nullptr;
	//}
	EventLists* eventLists = new EventLists();
	{
		std::lock_guard<mutex> g(getMutexForMakeEventLists());
		eventListsAllThreads.push_back(eventLists);
	}
	return eventLists;
}
//全局变量和thread_local初始化顺序不确定。出现 makeEventLists时，锁还未初始化的情况。
//同时，其他系统线程也会makeEentLists,那时多余的。所以我们加个全局变量，在主线程启动后的线程才有eventLists
static void _onMainThreadStarted() {
	_mainThreadStarted = true;
	//当前在主线程;主线程启动时，_mainThreadStarted也是false,所以主线程也没有eventLists.此处补上
}
//每个线程自己一个队列
#ifdef NO_URGC_REF
thread_local EventLists* eventLists = NULL; //= makeEventLists();
#else
thread_local EventLists* eventLists = makeEventLists();
#endif
volatile uint64_t incid = 0;

//记录引用
inline void Urgc::ref(void* source, void* target, std::function<void(void*)> deleter, string label)
{
	refCount++;
	//if (true) return;
#ifdef NO_URGC_REF
	if (true) return;
#endif
#ifdef DEFER_DELETE

	//if (deleter == nullptr) {
		//printf("set no deleter . isGcObj\n");
	//}

	#ifdef USE_LOCK
	std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
	#endif

	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 0;
	item.target = target;
	item.source = source;
	item.deleter = deleter;
	//item.label = label;
	incid = incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		// std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
		c->expandCap();
	}
#else

#ifdef USE_GC_THREAD
	#ifdef USE_LOCK
		std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
		//std::lock_guard<__SpinLock> g(swap_collecting_mutex);
	#endif
		/*tmplist[1] = { 0, source, target, deleter, label };
		tmplistindex++;*/
		//items->push_back({ 0, source, target, deleter, label });
		collecting->push_back({ 0, source, target, deleter, label });
	//items2[0].label = label;
	//items2[0].deleter = 0;// deleter;
	//items2[0].target = target;
	//items2[0].source = source;
	//items2[0].op_type = 0;
	//items2Len++;
	
	
	
#else
	do_ref(source, target, deleter);
#endif

#endif

	//不用加锁;还是要加锁呀。因为有timer线程的存在。 等于是有多个生产者
	//printf("ref\n");
}


/*
	 解引用:从target的被引用列表(all_sources)中删除，删除source->target的出引用记录
*/
// BUG,  启用NO_URGC_REF时，就编译不过
#ifndef NO_URGC_REF 
inline
#endif
void Urgc::deref(void* source, void* target, string label) {

	derefCount++;
	//if (true) return;

#ifdef NO_URGC_REF
	if (true) return;
#endif


	//8.5  nopush 7.0  nolock/nopush 6 代价2.5
	//notebook: 6.2(无锁无push) 8.4(无锁) 9.2(有锁有push)
	//notebook: 6.85(threadload items2+len)
	//notebook: 6.25(threadload items2+len, 去掉deleter/label(有函数调用))
	//notebook: 4.8(NO_URGC_LOCAL)
	//经测试，可以认为使用无锁，无函数调用的队列，性能损失可能低于5%(甚至更低，因为有可能是系统调度导致的波动);可以确认损失在函数调用上
	//NO_URGC_LOCAL为什么性能更好，极大可能deleter/label的string构造函数起到较大影响,后面可以把label/deleter去掉，应该效果会更优;
	//如果cpu直接提供指令，那么极限情况下，只有几个指令的代价
	//TODO 之后再优化为无锁无函数调用的队列,同时去掉deleter/label这类有函数调用代价的类。最少的信息只要op_type,target,source。
#ifdef DEFER_DELETE

	#ifdef USE_LOCK
	std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
	#endif

	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 1;
	item.source = source;
	item.target = target;
	item.label = label;
	incid = incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		// std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
		c->expandCap();
	}
#else
#ifdef USE_GC_THREAD
	//不用加锁
#ifdef USE_LOCK
	std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
	//std::lock_guard<__SpinLock> g(swap_collecting_mutex);
#endif
	//tmplistindex--;
	//items->push_back({ 1, source, target, nullptr, label });
	collecting->push_back({ 1, source, target, nullptr, label });

	//性能代价5%以下
	//items2[0].label = label;
	//items2[0].deleter = 0;
	//items2[0].target = target;
	//items2[0].source = source;
	//items2[0].op_type = 1;
	//items2Len++;

#else
	do_deref(source, target);
#endif
	//printf("deref\n");
#endif
}

void Urgc::do_ref(void *source, void *target, std::function<void(void *)> deleter, string label)
{
	if (target == nullptr)
	{
		return;
	}
	//std::lock_guard< std::recursive_mutex> g(_mutex);
	assert(source != nullptr && "source不能为nullptr");
	assert(target != nullptr && "target不能为nullptr");

	RefMgr *mgr = goc_ref_mgr_by_target(target, deleter);
	mgr->target_id = label;

	//记录出引用
	add_out_ref_mgr(source, mgr);

	// printf("\turgc:引用指针:source:%p => target:%p\n", source, target);
	//记录引用
	mgr->ref(source);
	/*if (!mgr->deleter) {
		printf(" do_ref no deleter\n");
	}*/
}

//记录出 引用管理器
void Urgc::add_out_ref_mgr(void *p, RefMgr *mgr)
{
	//不存在就创建关联
	auto it = out_ref_mgrs_map.find(p);
	if (it == out_ref_mgrs_map.end())
	{
		out_ref_mgrs_map[p] = {mgr};
	}
	else
	{
		(it->second).push_back(mgr);
	}
}
//移除出 引用管理器
void Urgc::remove_out_ref_mgr(void *p, RefMgr *mgr)
{
	auto it = out_ref_mgrs_map.find(p);
	if (it != out_ref_mgrs_map.end())
	{
		auto found = find(it->second.begin(), it->second.end(), mgr);
		//映射数组项
		if (found != it->second.end())
		{
			it->second.erase(found);
		}
		//数组空了，删除映射
		if (it->second.size() == 0)
		{
			out_ref_mgrs_map.erase(it);
		}
	}
}
void Urgc::do_deref(void *source, void *target)
{
	//std::lock_guard< std::recursive_mutex> g(_mutex);
	assert(source != nullptr && "source不能为nullptr");
	assert(target != nullptr && "target不能为nullptr");
	// printf("deref :%p=>%p\n", source, target);

	RefMgr *mgr = get_ref_mgr_by_target(target);
	if (mgr == nullptr)
	{
		printf("XXXXXXXXXXXXXX target:%p未受urgc管理。 \n", target);
		//target未受urgc管理
		return;
	}
	//移除出引用
	remove_out_ref_mgr(source, mgr);
	// printf("\tderef:remove_out_ref_mgr :%p=>%p\n", source, target);

	//判断:TODO(已经实现了？) 实际上，有可能该强引用失效，但是子树有其他可能的强引用转正，进而导致当前项无须删除。这需要进一步处理，留待之后.

	if (_deref_then_check_need_delete(mgr, source))
	{
		//// printf("\tderef:deref_then_check :%p=>%p\n", source, target);

		// printf("\t\t解引用导致需要删除:%p=>%p %s\n", source, mgr->target, typeid(mgr->target).name());
		/*
			 子树处理:
			 记录当前节点到“待删除节点列表“中，
			 子树处理:
			 强引用失效后
			 遍历子节点，置空unit_source,转入ghost_source, （备用，有可能回复）
			 查找新的强引用。要求新的强引用，不是循环引用，也不会引用到当前处理中的节点。
			 如果有找到，就使用新的强引用，置空ghost_source. 该子节点处理完成。
			 如果没有找到，记录该子节点到“待删除节点列表”中，然后递归处理该子节点的子节点。
			 所以节点处理完成后，遍历”待删除节点列表“， 重新查找强引用。 如果有找到，就归位，同时遍历子树中没有强引用的节点，更新强引用。
			 最后再次遍历”待删除节点列表“，删除节点
			 */
		vector<RefMgr *> will_deletes{mgr};
		children_find_new_chance(mgr->target, will_deletes);
		// printf("\tchildren_find_new_chance :deref_then_check :%p=>%p\n", source, target);
		recover_will_deletes(will_deletes);
		// printf("\trecover will deletes :deref_then_check :%p=>%p\n", source, target);
//#ifdef DEFER_DELETE
		//加入延迟删除队列;错误。不删除，就会导致后续其他对象recover时，找到已经被删除的对象
		//defer_will_deletes.insert(defer_will_deletes.end(), will_deletes.begin(), will_deletes.end());
//#else
		delete_will_deletes(will_deletes);
//#endif
		// printf("\tdelete  will deletes :deref_then_check :%p=>%p\n", source, target);
	}
	// printf("\tderef:return :%p=>%p\n", source, target);
}
void Urgc::stop_process_thread() {
	process_thread_running = false;
	if (process_thread) {
		process_thread->join();
		printf("gc线程任务结束\n");
	}
}
#ifdef DEFER_DELETE
void Urgc::process_on_thread()
{

#ifdef NO_URGC_REF
	if (true) return;
#endif
	int i = 0;
	vector<RefEventItem> mergedList;
	//FILE* f = fopen("a.txt", "w+");
	//mergedList.resize(2000);
	while (process_thread_running) {
		vector<RefEventItemList*> listList;
		{
			std::lock_guard<mutex> g(getMutexForMakeEventLists());
			for (auto eventList : eventListsAllThreads) {
				std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);

				//指针定入是原子的吧,可以不用加锁
				//交换两个队列 
				auto tmp = eventList->collecting;
				eventList->collecting = eventList->processing;
				eventList->processing = tmp;
				listList.push_back(tmp);
				//TODO 有可能 bug.因为tmp是当前collecting, 如果当前collecting在工作线程，正在expand
				//那下文的合并@[锁问题]，就可能出现并发写异常， 导致野指针
				//所以交换时，必须加锁， 确定交换期间，工作线程没有对collecting处理
			}
			//合并
			for (auto threadEventList : listList) {
				// 如果size()时，正好在c->length++之前，就会出现事件丢失
				for (int i = 0, l = threadEventList->size(); i < l; i++) {
					//TODO 此处的锁，应该还可以更优化。锁加在这里，好像也不行。 
					//读值时，有可能工作线程正在expandCap, 如果需要加锁
					std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);

					//[锁问题] 这里是有问题的。 因为threadEventList在工作线程可能还在操作中。
					RefEventItem &e = threadEventList->at(i);

					mergedList.push_back(e);
				}
				threadEventList->clear();
			}
		}

		//排序; 算法核心要保证对同一个对象的引用解引用有序。特别是初始的引用和CtorGuard的引用。中间的引用和解引用对的顺序其实无所谓。
		//有bug,会影响到事件的顺序，可能跟int溢出有关？，事件错误，导致对象被误释放，或者释放时没有deleter
		//可是不排序，多线程就会有顺序问题啊。。。
		std::sort(mergedList.begin(), mergedList.end(), [](RefEventItem& a, RefEventItem& b) {
			return a.incid < b.incid;
		});
		
		// if (mergedList.size() > 1000) {
			// printf("urgc 待处理事件数量很多:%u\n", mergedList.size());
			// printf("urgc events waits too many:%llu\n", mergedList.size());
		// }
		 
		//延迟会。因为没有锁，有可能其他线程读到的是交换前的，就会出现 其他线程在操作processing,自己这个线程也在
		//操作processing。所以等一下
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	
		delete_cnt = 0;
		delete_classnames.clear();
		auto processing = &mergedList;
		int size = (int)processing->size();
		// printf("处理事件队列。 size:%d\n", processing->size());
		long long costMs = 0;
		long long refCostUs = 0;
		long long derefCostUs = 0;
		long long guardCostUs = 0;
		long long deguardCostUs = 0;
		long long setDeleterCostUs = 0;

		int refCount = 0;
		int derefCount = 0;
		int guardCount = 0;
		int deguardCount = 0;
		int setDeleterCount = 0;

		if (size > 0) {
			long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


			//auto& list = *processing;
			for (int i = 0, l = processing->size(); i < l; i++) {
				auto& e = processing->at(i);

				#ifdef RECORD_TARGET_REF_EVENTS
				this->record_target_ref_event(e);
				#endif

				if (e.op_type == 1) {
					RefMgr* mgr = get_ref_mgr_by_target(e.target);
					if (mgr == nullptr) {
						//被环提前释放了
						continue;
					}
					if (mgr->incid && e.incid < mgr->incid) {
						//因为内存释放后，会被重用。 所以相同的Target地址，可能是不同的对象了。
						//e.incid < mgr->incid 说明是之前的对象了。 
						// 析构函数中，解引用成员时会产生此现象
						continue;
					}
				}
				/*printf("%05d %s 处理事件. opttype:%d incid:%d %p=>%p pid:%lld\n", 
					i, e.label.c_str(), e.op_type, e.incid, e.source, e.target, e.threadid);
				char buff[256];
				sprintf(buff, "%05d %s 处理事件. opttype:%d incid:%d %p=>%p pid:%lld\n",
					i, e.label.c_str(), e.op_type, e.incid, e.source, e.target, e.threadid);
				fwrite(buff, 1, strlen(buff), f);
				fflush(f);*/
				//printf("处理事件:%d optype:%d :%p=>%p type:%s\n", i, e.op_type, e.source, e.target, e.label.c_str());

				auto target = (GcObj*)e.target;
				//printf("处理事件:%d optype:%d :%p=>%p type:%s\n", i, e.op_type, e.source, e.target, typeid(*(GcObj*)e.target).name());
				//printf("处理事件:%d optype:%d :%p=>%p deleter:%s\n", i, e.op_type, e.source, e.target, e.deleter ?"has":"none");
			//for (auto& e : list) {
				if (e.op_type == 0) {
					long long t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					do_ref(e.source, e.target, e.deleter, e.label);
					long long t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					refCostUs += t1 - t0;
					refCount++;
				}
				else if (e.op_type == 1) {
					/*if (dynamic_cast<Window*>((GcObj*)e.target)) {
						printf("do deref window\n");
					}*/
					long long t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

					do_deref(e.source, e.target);
					long long t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					derefCostUs += t1 - t0;
					derefCount++;
				}
				else if (e.op_type == 2) {//ctor guard
					long long t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					auto obj = e.target;
					auto mgr = urgc.goc_ref_mgr_by_target(obj);
					if (e.deleter) {
						//mgr->deleter = e.deleter;
						mgr->setDeleter(e.deleter);
					}
					if (!mgr->unit_source) {//还未被保护
						mgr->unit_source = e.source;
					}
					if (mgr->incid == 0) {
						mgr->incid = e.incid;
					}
					long long t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					guardCostUs += t1 - t0;
					guardCount++;
				}
				else if (e.op_type == 3) {//ctor guard cancel
					long long t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					auto obj = e.target;
					auto mgr = urgc.goc_ref_mgr_by_target(obj);
					if (mgr->unit_source == e.source) {
						mgr->unit_source = nullptr;
					}
					long long t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					deguardCostUs += t1 - t0;
					deguardCount++;
				}
				else if (e.op_type == 4) {//set deleter
					long long t0 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					auto obj = e.target;
					auto mgr = urgc.goc_ref_mgr_by_target(obj);
					if (e.deleter) {
						//mgr->deleter = e.deleter;
						mgr->setDeleter(e.deleter);
					}
					long long t1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
					setDeleterCostUs += t1 - t0;
					setDeleterCount++;
				}

			}
			long long ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

			int count = processing->size();

			//auto classnames = StrUtil::join(delete_classnames, ",");
			//printf("处理结束, 事件数:%d, 删除:%d:%s\n", size, urgc.delete_cnt, classnames.c_str());
			//printf("处理结束, 事件数:%d, 删除:%d\n", size, urgc.delete_cnt);
			processing->clear();

			long long ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			costMs = ms3 - ms;

			// /*
			if (costMs >= 20){
				int objCount = target_in_ref_mgr.size();
				printf("%lld,%5d-%4d 处理事件[%d]结束, 耗时:%lld ms %lldms. cost ref:%d,%lldus, deref:%d, %lldus guard:%d, %lldus degurad:%d, %lldus setDeleter:%d, %lldus\n", 
					ms3, objCount, delete_cnt,
					count, ms2 - ms, ms3 - ms2, 
					refCount, refCostUs, 
					derefCount, derefCostUs, 
					guardCount, guardCostUs, 
					deguardCount, deguardCostUs,
					setDeleterCount, setDeleterCostUs
				);
			}

			do_free_later();

			// */
		}
			
		//真正删除。注意，此时的列表有可能出现需要删除的target多次。 因为多线程不同队列，有可能出现引用多次到达0的情况
		//去重
		/*std::sort(defer_will_deletes.begin(), defer_will_deletes.end());
		defer_will_deletes.erase(std::unique(defer_will_deletes.begin(), defer_will_deletes.end()), defer_will_deletes.end());
		
		delete_will_deletes(defer_will_deletes);
		defer_will_deletes.clear();*/

		i++;
		if (i % 10 == 2) {
			// report_type_cnts();
			// report("usage");
			// printf(" event list size:%d,\n", size );
		}

		long long sleepMs = 40 - costMs;
		if (sleepMs > 0) {

			//printf("sleep_for：%lld\n", sleepMs);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepMs));
		}
		//printf("sleep_for end：%d\n", process_thread_running);
	}
	printf("gc线程结束：%d\n", process_thread_running);
}
#else
void Urgc::process_on_thread()
{

#ifdef NO_URGC_REF
	if (true) return;
#endif
	int i = 0;
	while (process_thread_running) {
		{
			//printf("交换事件队列：%d\n", process_thread_running);
#ifdef USE_LOCK
			std::lock_guard<std::recursive_mutex> g(swap_collecting_mutex);
			//std::lock_guard<__SpinLock> g(swap_collecting_mutex);
#endif
			//指针定入是原子的吧,可以不用加锁
			//交换两个队列
			auto tmp = collecting;
			collecting = processing;
			processing = tmp;
		}

#ifndef USE_LOCK
		//延迟会。因为没有锁，有可能其他线程读到的是交换前的，就会出现 其他线程在操作processing,自己这个线程也在
		//操作processing。所以等一下
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
#endif

		int size = (int)processing->size();
		//printf("处理事件队列。 size:%d\n", processing->size());
		if (size > 0) {
			delete_cnt = 0;
			delete_classnames.clear();

			//auto& list = *processing;
			for (int i = 0, l = processing->size(); i < l; i++){
				auto& e = processing->at(i);

				if (e.op_type == 1) {
					RefMgr* mgr = get_ref_mgr_by_target(e.target);
					if (mgr == nullptr){
						//被环提前释放了
						continue;
					}
				}
				//printf("处理事件:%d optype:%d :%p=>%p type:%s\n", i, e.op_type, e.source, e.target, e.label.c_str());

				auto target = (GcObj*)e.target;
				//printf("处理事件:%d optype:%d :%p=>%p type:%s\n", i, e.op_type, e.source, e.target, typeid(*(GcObj*)e.target).name());
			//for (auto& e : list) {
				if (e.op_type == 0) {
					do_ref(e.source, e.target, e.deleter, e.label);
				}
				else if (e.op_type == 1) {
					/*if (dynamic_cast<Window*>((GcObj*)e.target)) {
						printf("do deref window\n");
					}*/
					do_deref(e.source, e.target);
				}
				else if (e.op_type == 2) {//ctor guard
					auto obj = e.target;
					auto mgr = urgc.goc_ref_mgr_by_target(obj);
					if (!mgr->unit_source) {//还未被保护
						mgr->unit_source = e.source;
					}
				}
				else if (e.op_type == 3) {//ctor guard cancel
					auto obj = e.target;
					auto mgr = urgc.goc_ref_mgr_by_target(obj);
					if (mgr->unit_source == e.source) {
						mgr->unit_source = nullptr;
					}
				}
			}
			//auto classnames = StrUtil::join(delete_classnames, ",");
			//printf("处理结束, 事件数:%d, 删除:%d:%s\n", size, urgc.delete_cnt, classnames.c_str());
			//printf("处理结束, 事件数:%d, 删除:%d\n", size, urgc.delete_cnt);
			processing->clear();
		}
		i++;
		if (i % 1000 == 50) {
			report_type_cnts();
		}
		//printf("sleep_for：%d\n", process_thread_running);
		std::this_thread::sleep_for(std::chrono::milliseconds(90));
		//printf("sleep_for end：%d\n", process_thread_running);
	}
	printf("gc线程结束：%b\n", process_thread_running);
}
#endif
void Urgc::report_type_cnts() {
	if (1) {
		printf("urgc 生存数:%d\n", (int) target_in_ref_mgr.size());
		return;
	}
	// if (1) return;
	unordered_map<string, int> cnt_map;
	for (auto& it : target_in_ref_mgr) {
		string type = typeid(*((GcObj*)it.first)).name();
		if (cnt_map.find(type) == cnt_map.end()) {
			cnt_map[type] = 1;
		}
		else cnt_map[type]++;
	}
	int cnt = 0;
	printf("生存数:%d\n", (int) target_in_ref_mgr.size());
	for (auto& it : cnt_map) {
		cnt += it.second;
		printf("\t%s:%d   累计:%d\n", it.first.c_str(), it.second, cnt);
	}
}
void Urgc::start_process_thread() {

#ifdef EMPTY_GC_THREAD
	if (true) return;
#endif


#ifdef USE_GC_THREAD
	if (process_thread) {
		return;
	}
	process_thread = new std::thread(&Urgc::process_on_thread, this);
#endif
}


/*
	 子树处理:
	 记录当前节点到“待删除节点列表“中，
	 子树处理:
	 强引用失效后
	 遍历子节点，置空unit_source,转入ghost_source, （备用，有可能回复）
	 查找新的强引用。要求新的强引用，不是循环引用，也不会引用到当前处理中的节点。
	 如果有找到，就使用新的强引用，置空ghost_source. 该子节点处理完成。
	 如果没有找到，记录该子节点到“待删除节点列表”中，然后递归处理该子节点的子节点。
	 所以节点处理完成后，遍历”待删除节点列表“， 重新查找强引用。 如果有找到，就归位，同时遍历子树中没有强引用的节点，更新强引用。
	 最后再次遍历”待删除节点列表“，删除指针,删除节点的mgr,删除节点的出引用
	 */
//执行最终的删除
void Urgc::delete_will_deletes(vector<RefMgr *> &will_deletes)
{
	//提前删除所有出引用和出引用列表记录. 
	// 与下文的erase mgr分开处理。 不然可能导致，mgr已释放，但是出引用还依赖着，导致崩溃
	// printf("删除 出引用 \n");
	for (auto mgr : will_deletes)
	{
		if (mgr->unit_source == nullptr){ //未能恢复成功
			//删除所有出引用和出引用列表记录,
			auto out_it = out_ref_mgrs_map.find(mgr->target);
			// printf("\t\t结点最终删除2:%p %s\n", mgr->target, typeid(mgr->target).name());
			if (out_it != out_ref_mgrs_map.end())
			{
				auto kid_mgrs = out_it->second;
				//删除出引用
				for (auto kid_mgr : kid_mgrs)
				{
					kid_mgr->remove_first_matched_source_from_all_sources(
						mgr->target);
				}
				//删除出引用列表记录
				out_ref_mgrs_map.erase(out_it);
			}
		}
	}
	// printf("delete_will_deletes \n");
	for (auto mgr : will_deletes)
	{
		if (mgr->unit_source == nullptr)
		{ //未能恢复成功
			// printf("\t\t结点最终删除:%p %s\n", mgr->target, typeid(mgr->target).name());

			// printf("\t\turgc:释放指针:%p\n", mgr->target);
			//需要释放
			//delete mgr->target;
			delete_cnt++;
			auto obj = (GcObj*)mgr->target;
			if (obj) {
				//delete_classnames.push_back(typeid(*(obj)).name());
			}
			mgr->delete_target(); 
			 //printf("\t\t\turgc:释放指针完成:%p\n", mgr->target);

			//删除mgr. 此处删除了，有可能后续delete依赖了此mgr,导致访问被释放的内存
			auto it = target_in_ref_mgr.find(mgr->target);
			if (it != target_in_ref_mgr.end())
			{
				target_in_ref_mgr.erase(it);
			}
			// printf("\t\t\turgc:释放指针完成2:%p\n", mgr->target);
		}
	}
	// printf("\t\t\turgc:完释放:\n");
}

//子树出路寻找完毕后，有些待删除节点，可以回归. 此时的节点，unit_source=null, ghost_source=原强引用。
void Urgc::recover_will_deletes(vector<RefMgr *> &will_deletes)
{
	// printf("recorver_will_delets\n");
	for (auto mgr : will_deletes)
	{
		for (auto source : mgr->all_sources)
		{
			//重新查找强引用。 如果有找到，就归位
			// printf("recover_will_deletes:%p=>%p\n", source, mgr->target);
			if (check_ref(source, mgr->target))
			{
				//恢复子树
				recover_node(mgr, source);
				break; //处理下一个will_delete
			}
		}
	}
}
//子树恢复
void Urgc::recover_node(RefMgr *mgr, void *source)
{
	// printf("\t\t结点恢复:%p=>%p\n", source, mgr->target);
	mgr->set_unit_source(source);

	//子树处理
	auto it = out_ref_mgrs_map.find(mgr->target);
	if (it == out_ref_mgrs_map.end())
	{ //未找到出引用
		return;
	}
	auto &out_ref_mgrs = it->second;
	for (auto kid_mgr : out_ref_mgrs)
	{
		if (kid_mgr->unit_source == nullptr)
		{ //该结点，没有强引用
			//递归处理子树
			recover_node(kid_mgr, mgr->target);
		}
	}
}
//子树寻找新的出路
void Urgc::children_find_new_chance(void *parent,
									vector<RefMgr *> &will_deletes)
{
	// printf("children find new chance\n");
	auto it = out_ref_mgrs_map.find(parent);
	if (it == out_ref_mgrs_map.end())
	{ //未找到出引用
		return;
	}
	auto &out_ref_mgrs = it->second;
	for (auto mgr : out_ref_mgrs)
	{
		if (mgr->unit_source == parent)
		{ //只找子树(唯一强引用关联的）.
			child_find_new_chance(parent, mgr, will_deletes);
		}
	}
}
void Urgc::child_find_new_chance(void *parent, RefMgr *mgr,
								 vector<RefMgr *> &will_deletes)
{
	// printf("child find new chance\n");
	//遍历子节点，置空unit_source, 转入ghost_source, （备用，有可能回复）
	mgr->ghost_source = mgr->unit_source;
	mgr->unit_source = nullptr;
	//查找新的强引用
	for (auto source : mgr->all_sources)
	{
		if (source != parent)
		{
			//新的强引用
			// printf("child_find_new_chance:%p=>%p\n", source, mgr->target);
			if (check_ref(source, mgr->target))
			{
				// printf("\t\t找到新生机:%p=>%p\n", source, mgr->target);
				mgr->set_unit_source(source); //使用新的强引用
				return;						  //该子结点处理完成
			}
		}
	}
	//未找到新的强引用：如果没有找到，记录该子节点到“待删除节点列表”中，然后递归处理该子节点的子节点。
	will_deletes.push_back(mgr);
	children_find_new_chance(mgr->target, will_deletes);
}

//设置指针。
void Urgc::set_pointer(void *source, void **ptr, void *target)
{
	*ptr = target;
	ref(source, target);
}
//判断是不是循环引用
//进行环识别：唯一强引用构成树，所以，构成唯一强引用环的唯一可能，是新的强引用来自子树
//所以，通过上溯父，到根，如果不会找到自己，就说明该引用来自子树外。所以可用。
bool Urgc::is_cycle_ref(void *source, void *target)
{
	// printf("is_cycle_ref\n");
	while (source && (unsigned long long)source != ROOT_REF)
	{ //有源，且源非根引用
		// printf("\t check is_cycle_ref : %p=>%p\n", source, target);
		if (source == target)
		{
			return true;
		}
		auto mgr = get_ref_mgr_by_target(source);
		if (mgr == nullptr)
		{
			break;
		}
		source = mgr->unit_source;
	}
	return false;
}
//向上判断引用是否可用：非环，也不会到unit_source==nullptr(无效的引用)的情况
bool Urgc::check_ref(void *source, void *target)
{
	// printf("check_ref\n");
	while (true)
	{ //有源，且源非根引用
		// printf("\t检查引用可用:%p=>%p\n", source, target);
		if (source == nullptr)
		{ //无效的引用
			return false;
		}
		if ((unsigned long long)source == ROOT_REF)
		{ //根引用
			return true;
		}
		if (source == target)
		{ //ring 环. 该引用会产生环，不能用
			// printf("\tcheck_ref遇到环 source == target:%p=>%p\n", source, target);
			return false;
		}
		auto mgr = get_ref_mgr_by_target(source);
		if (mgr == nullptr)
		{ //未记录的source
			return true;
		}
		source = mgr->unit_source;
	}
}
//解引用。返回是否需要释放
bool Urgc::_deref_then_check_need_delete(RefMgr *mgr, void *source)
{
	// printf("_deref_then_check_need_delete");
	//当unit_source为空时
	//当要解引用的，是唯一强引用，需要进行环识别：唯一强引用构成树，所以，构成唯一强引用环的唯一可能，是新的强引用来自子树
	//所以，通过上溯父，到根，如果不会找到自己，就说明该引用来自子树外。所以可用。
	if (mgr->unit_source && mgr->unit_source == source)
	{
		//先从all_sources中删除该强引用
		mgr->remove_first_matched_source_from_all_sources(mgr->unit_source);
		mgr->unit_source = nullptr;

		//寻找新的唯一强引用
		for (auto cur_source : mgr->all_sources)
		{
			if (!is_cycle_ref(cur_source, mgr->target))
			{
				// printf("\t找到新的唯一强引用\n");
				mgr->set_unit_source(cur_source); //更新唯一引用
				return false;
			}
		}
		//未找到唯一强引用,需要释放
		return true;
	}
	else
	{ //解非强引用,直接移除即可
		mgr->remove_first_matched_source_from_all_sources(source);
		return false;
	}
}
//报告
void Urgc::report(string title)
{
	//if (1) return;
	printf("=========%s=================\n", title.c_str());
	int ref_cnt = 0;
	for (auto &it : target_in_ref_mgr)
	{
		auto target = it.first;
		printf("\t唯一强引用关系:%p(%s) => %p(%s). ghost:%p(%s)\n", 
				it.second.unit_source, 
				(unsigned long long)it.second.unit_source == ROOT_REF ? ""
				: typeid(*(GcObj*)it.second.unit_source).name(),
			    target, typeid(*(GcObj*)target).name(),
				it.second.ghost_source, typeid((GcObj*)it.second.ghost_source).name());
		ref_cnt += it.second.all_sources.size();
		for (auto source : it.second.all_sources)
		{
			printf("\t\t所有引用:%p(%s)=>%p(%s)\n", 
				source,
				(unsigned long long)source == ROOT_REF ? ""
			    : typeid(*(GcObj*)source).name(), 
				target, 
				typeid(*(GcObj*)target).name());
		}
	}
	int ungc_size = target_in_ref_mgr.size();
	int out_size = out_ref_mgrs_map.size();
	printf("$$$$$urgc:未回收指针数量: %d. 出引用数量: %d. 引用数:%d\n", ungc_size, out_size, ref_cnt);
}

void urgc_report_sources_of(void *p){
	urgc.report_sources_of(p);
}
void Urgc::report_sources_of(void* target)
{
	printf("========================================report_sources_of:%p\n", target);
	auto it = target_in_ref_mgr.find(target);
	if (it != target_in_ref_mgr.end()) {
		// printf("目标[%s@%llx]的所有源：\n", typeid(*((GcObj*)target)).name(), (int64_t)target);
		auto &refMgr = it->second;

		for (auto source : refMgr.all_sources)
		{
			printf("\t\t%p(%s)=>%p(%s) %s\n",
				source,
				(unsigned long long)source == ROOT_REF ? ""
				: "",
				// : typeid(*(GcObj*)source).name(),
				target,
				"",
				// typeid(*(GcObj*)target).name(),
				refMgr.unit_source == source ? "!":""
			);
		}
	}
}

void Urgc::report_source_chain(void* target)
{
	printf("目标[%s@%p]的unit源链：\n", typeid(*((GcObj*)target)).name(), target);
	auto cur = target;
	while ((unsigned long long)cur!= ROOT_REF) {
		auto it = target_in_ref_mgr.find(cur);
		if (it == target_in_ref_mgr.end()) {
			break;
		}
		 cur = it->second.unit_source;
		printf("\t[%s@%p]\n",
			(unsigned long long)cur == ROOT_REF?"": typeid(*((GcObj*)cur)).name(), cur);
	}

}


//局部变量引用指针

static GcObj *_global_source = nullptr;

void Ref_set_global_source(GcObj *source)
{
	_global_source = source;
}
GcObj *Ref_get_global_source()
{
	return _global_source;
}

//#define set(source, expr, target) \
//    expr = target;\
//    urgc.ref(source, target)



Closure<void()>* closure_of(std::string name)
{
#ifndef NO_URGC_REF
	urgc.swap_collecting_mutex.lock();
#endif
	//urgc.closure_mutex.lock();


	Closure<void()>* closure = new Closure<void()>;
	closure->name = name;
	return closure;
}


static int v = 0;
CtorGuard::CtorGuard(void* obj) {

	urgc.guardCount++;

#ifdef NO_URGC_REF
	if (true) {
		this->obj = obj;
		return;
	}
#endif



#ifdef DEFER_DELETE
	this->obj = obj;
	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 2;
	item.source = &v;
	item.target = obj;
	incid = incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
		c->expandCap();
	}
#else

#ifdef USE_GC_THREAD
#ifdef USE_LOCK
	std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
	//std::lock_guard<__SpinLock> g(urgc.swap_collecting_mutex);
#endif
	this->obj = obj;
	urgc.collecting->push_back({2, &v, obj, nullptr});

#else
	std::lock_guard<std::recursive_mutex> g(urgc._mutex);
	auto mgr = urgc.goc_ref_mgr_by_target(obj);
	if (!mgr->unit_source) {//还未被保护
		mgr->unit_source = &v;
		this->obj = obj;
		guarding = true;
	}
	printf("GcCtorGuard：protect:%p\n", obj);
#endif
#endif
}
CtorGuard::~CtorGuard() {

	urgc.deguardCount++;


#ifdef NO_URGC_REF
	if (true) return;
#endif



	// std::this_thread::get_id();

#ifdef DEFER_DELETE
	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 3;
	item.source = &v;
	item.target = obj;
	incid = incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
		c->expandCap();
	}
#else
#ifdef USE_GC_THREAD
#ifdef USE_LOCK
	std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
	//std::lock_guard<__SpinLock> g(urgc.swap_collecting_mutex);
#endif
	urgc.collecting->push_back({3, &v, obj, nullptr});
#else
	if (guarding) { 
		guarding = false;
		std::lock_guard< std::recursive_mutex> g(urgc._mutex);
		auto mgr = urgc.goc_ref_mgr_by_target(obj);
		mgr->unit_source = nullptr;
	}
	printf("~GcCtorGuard: release:%p\n", obj);
#endif
#endif
}

inline void RefEventItemList::push_back(const RefEventItem&& item) {
	if (length >= cap) {
		expandCap();
	}
	data[length] = item;
	length++;
}

inline void RefEventItemList::expandCap() {
	auto newcap = cap * 2;
	auto newData = new RefEventItem[newcap];
	for (int i = 0; i < length; i++) {
		newData[i] = data[i];
	}
	//memcpy(newData, data, sizeof(RefEventItem) * cap);
	delete[] data;
	data = newData;
	cap = newcap;
}

void RefEventItemList::clear() {
	for (int i = 0; i < length; i++) {
		data[i] = RefEventItem();
	}
	length = 0;
}
void urgc_set_deleter(void* p, void (*deleter)(void*)) {
	#ifdef NO_URGC_REF
	if (1) return;
	#endif
	urgc.setDeleterCount++;

	std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 4;
	item.source = NULL;
	item.target = p;
	item.deleter = deleter;
	incid = incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		// std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
		c->expandCap();
	}
}
void urgc_guard(void* obj, void (*deleter)(void *p)) {
	#ifdef NO_URGC_REF
	if (1) return;
	#endif
	urgc.guardCount++;
	if (deleter == nullptr) {
		printf("guard set no deleter . isGcObj\n");
	}
	std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 2;
	item.source = &v;
	item.target = obj;
	item.deleter = deleter;
	incid=incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		// std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
		c->expandCap();
	}
}
URGC_DLLAPI void urgc_ref(void* source, void* target, void (*deleter)(void*)) {
	#ifdef NO_URGC_REF
	if (1) return;
	#endif
	urgc.ref(source, target, deleter);
}
URGC_DLLAPI void urgc_deref(void* source, void* target) {
	#ifdef NO_URGC_REF
	if (1) return;
	#endif
	urgc.deref(source, target);
}
void urgc_deguard(void* obj) {
	#ifdef NO_URGC_REF
	if (1) return;
	#endif
	urgc.deguardCount++;

	std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
	auto c = eventLists->collecting;
	auto& item = c->data[c->length];
	item.op_type = 3;
	item.source = &v;
	item.target = obj;
	incid=incid+1;
	item.incid = incid;
	//item.threadid = (uint64_t)eventLists;
	c->length++;
	if (c->length >= c->cap) {
		// std::lock_guard<std::recursive_mutex> g(urgc.swap_collecting_mutex);
		c->expandCap();
	}

}
void* urgc_set_field_by_offset(void* host, int field_offset, void* p) {
	return urgc_set_field(host, (void**)(((char *)host) + field_offset), p);
}
//set_field
void* urgc_set_field(void* host, void** field, void* p) {
	if ((size_t)field < 10240) { //说明 field不是真实地址，是相对于0的偏移
		field = (void**)((size_t)host + (size_t)field);
	}


	#ifdef NO_URGC_REF
	*field = p;
	if (1) return p;
	#endif

	//先解引用
	if (*field != NULL) {
		urgc.deref(host, (GcObj*)(*field));
	}
	*field = p;
	if (*field != NULL) {
		urgc.ref(host, (GcObj*)p, nullptr);
	}
	return p;
}

//set var
void* urgc_set_var(void** pvar, void* p) {
	#ifdef NO_URGC_REF
	*pvar = p;
	if (1) return p;
	#endif
	if (pvar != NULL) { //orc接收return值时， __outRef__可能值为NULL
		//先解引用
		if (*pvar != NULL) {
			urgc.deref(pvar, (GcObj*)(*pvar));
		}

		*pvar = p;
		if (*pvar != NULL) {
			urgc.ref(pvar, (GcObj*)p, nullptr);
		}
	}
	return p;
}


//set var
void* urgc_set_var_for_return(void** pvar, void* p) {
	#ifdef NO_URGC_REF
		*pvar = p;
	if (1) return p;
	#endif
	if (pvar != NULL) { //orc接收return值时， __outRef__可能值为NULL
		//先解引用
		if (*pvar != NULL) {
			urgc.deref(pvar, (GcObj*)(*pvar));
		}

		*pvar = p;
		if (*pvar != NULL) {
			urgc.ref(pvar, (GcObj*)p, nullptr);
		}
	}
	else {//没有接收者时
		urgc.ref((void*)ROOT_REF, (GcObj*)p, nullptr);
		urgc.deref((void*)ROOT_REF, (GcObj*)p);
		//没有接收者，直接返回NULL。因为此值是失效的
		return NULL;
	}
	return p;
}

//set var
// void* urgc_set_var_for_return_with_deleter(void** pvar, void* p, void (*deleter)(void *p)) {
// 	#ifdef NO_URGC_REF
// 		*pvar = p;
// 	if (1) return p;
// 	#endif

// 	if (pvar != NULL) { //orc接收return值时， __outRef__可能值为NULL
// 		//先解引用
// 		if (*pvar != NULL) {
// 			urgc.deref(pvar, (GcObj*)(*pvar));
// 		}

// 		*pvar = p;
// 		if (*pvar != NULL) {
// 			urgc.ref(pvar, (GcObj*)p, deleter);
// 		}
// 	}
// 	else {//没有接收者时
// 		urgc.ref((void*)ROOT_REF, (GcObj*)p, deleter);
// 		urgc.deref((void*)ROOT_REF, (GcObj*)p);
// 	}
// 	return p;
// }
//init var
void* urgc_init_var(void** pvar, void* p) {
	#ifdef NO_URGC_REF
	*pvar = p;
	if (1) return p;
	#endif
	//给变量赋初值时，变量可能有脏数据
	////先解引用
	//if (*pvar != NULL) {
	//	urgc.deref(pvar, (GcObj*)(*pvar));
	//}
	//已经引用上了。  在 Type *a = new Type() 时，会被转义为  Type*a = urgc_init_var(&a, Type_new(&a)); Type_new就会提前让a引用新对象
	if (*pvar == p){
		return p;
	}

	*pvar = p;
	if (*pvar != NULL) {
		urgc.ref(pvar, (GcObj*)p, nullptr);
	}
	return p;
}

// URGC_DLLAPI void* urgc_init_var_with_deleter(void** pvar, void* p, void (*deleter)(void*)) {
// 	#ifdef NO_URGC_REF
// 	*pvar = p;
// 	if (1) return p;
// 	#endif
// 	*pvar = p;
// 	if (*pvar != NULL) {
// 		urgc.ref(pvar, (GcObj*)p, deleter);
// 	}
// 	return p;
// }

void urgc_start_process_thread() {
	#ifdef NO_URGC_REF
	if (1) return ;
	#endif
	urgc.start_process_thread();
}
void urgc_stop_process_thread() {
	urgc.stop_process_thread();
}



void urgc_refvar_cleanup(void *p) {
	#ifdef NO_URGC_REF
	if (1) return ;
	#endif
    void** pobj = (void **)p;
    //printf("cleanup ref:p=%p obj=%p\n", pobj, *pobj);
    //urgc_set_var(pobj, NULL);//记录引用
	urgc.deref(pobj, (GcObj*)(*pobj));
}

int urgc_countEvent()
{

	int c = urgc.refCount
	+ urgc.derefCount
	+ urgc.guardCount
	+ urgc.deguardCount
	+ urgc.setDeleterCount;

	urgc.refCount = 0;
	urgc.derefCount = 0;
	urgc.guardCount = 0;
	urgc.deguardCount = 0;
	urgc.setDeleterCount = 0;
	return c;
}

TargetRefRecords* Urgc::get_target_ref_records(void* target) {
	auto it = target_ref_records_map.find(target);
	if (it == target_ref_records_map.end()) {
		return NULL;
	}
	return &it->second;
}
bool Urgc::save_target_ref_records(void* target){
	auto records = this->get_target_ref_records(target);
	if (records == NULL) {
		printf("no records for target:%p\n", target);
		return false;
	}

	FILE *f = fopen("urgc_ref_records.txt", "w+");
	for (int i = 0, l = records->events.size(); i < l; i++) {
		auto &evt = records->events[i];
		fprintf(f, "%d %d %p\n", i, evt.op_type, evt.source);
	}
	fclose(f);
	return true;
}

void Urgc::record_target_ref_event(RefEventItem& item){
	auto records = this->get_target_ref_records(item.target);
	if (records == NULL) {
		TargetRefRecords ent;
		ent.target = item.target;
		target_ref_records_map[item.target] = ent;
		records = &target_ref_records_map[item.target];
	}
	RefRecord record;
	record.op_type = item.op_type;
	record.source = item.source;
	record.incid = item.incid;
	records->events.push_back(record);
	//只记录100条
	if (records->events.size() > 100) {
		records->events.erase(records->events.begin());
	}	
}

//用于DEFER_DELETE
void urgc_defer_free(void *p){
	free(*((void**)p));
}

void urgc_free_later(void *p){
	std::lock_guard<std::mutex> g(free_later_mutex);
	free_later_list.push_back(p);
}