#pragma once

#include <cstdint>
#pragma warning( disable: 4251 )

#include "UrgcPredef.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <functional>
#include <unordered_map>

#include <cassert>
#include <type_traits>
#include <mutex>

#include "./GcObj.h"


using std::string;
using std::vector;
using std::mutex;
using std::unordered_map;


//使用urgc,要求类必须要有虚函数
//不要在全局变量/全局static 中使用Ref.因为c++全局变量的初始化顺序是ub;

//根引用。 
#define ROOT_REF (unsigned long long)-1l

//debug模式下，local小函数极大降低性能.可以在DEBUG模式下直接禁用local,禁用后，就不会产生ref/deref,内存从不释放
// #define NO_URGC_REF

// 是否记录每个target的所有引用事件
#define RECORD_TARGET_REF_EVENTS

//潜在bug. 释放顺序的问题。 如果析构函数依赖的对象在此对象之前释放了。怎么办？ 提供finalize虚函数， 预释放依赖，然后虚函数里，不要依赖其他对象?
//等于是  不真的释放，统一执行了释放前的处理，再统一释放，这样就没有析构函数依赖的问题
//例: Drag::~Drag中依赖了 offhub->clear. offhub依赖了emitter. emitter在依赖图中，释放顺序不固定，不能确保在~Drag之后再释放
//例2：循环引用。 每个析构函数都依赖了下一个对象，不可能根据析构函数分析出哪个对象要先释放的
//
//修正：真正的潜在bug，其实是析构函数，不要再去解除引用了。~drag不要再调用offhub->clear。因为到了析构函数了，就说明没有被引用了.
//都是要一起被释放的,根本不用在析构函数再去做解除引用的工作。

//Ref<T> T 可以不用继承GcObj

//自旋锁
class  URGC_DLLAPI  __SpinLock {
public:
	void lock() {
		/*bool expected = false;
		while (!flag_.compare_exchange_weak(expected, true)) {
			expected = false;
		}*/
	}
	void unlock() {
		//flag_.store(false);
	}

private:
	//std::atomic<bool> flag_ = false;
};


/*
 入引用管理
 */
class  URGC_DLLAPI  RefMgr {
public:
	char flag[10] = "RefMgr789";
	long long gid;
	//null:表示未确定唯一引用
	//ROOT_REF:来自根的引用
	//other: 其他
	void* unit_source = nullptr;    //唯一引用源
	void* ghost_source = nullptr;    //幽灵引用（备忘unit_source)
	vector<void*> all_sources; //所有引用源
	void* target; 
	bool deleted = false;
	bool isDeleted = false;
	RefMgr* conflictRefMgr = NULL;//有冲突的RefMgr
	string target_id;
	uint64_t incid = 0; //guard时的incid
	std::function<void(void*)> deleter = nullptr;//自定义删除函数

	RefMgr();
	RefMgr(void* _target);
	//设置强引用
	void set_unit_source(void* obj);

	void ref(void* source);
	//从all_sources删除第一个source
	void remove_first_matched_source_from_all_sources(void* source);

	//释放指针
	virtual void delete_target();

	void setDeleter(std::function<void(void*)> deleter);
};


//设置全局的source.
//为了支持lambda.lambda引用 local时，会丢失source. 所以设置好global_source,有global_source时，Ref默认使用global_source
//设置完Lambda后，就置空global_source
URGC_DLLAPI void Ref_set_global_source(GcObj* source);

URGC_DLLAPI GcObj* Ref_get_global_source();

template <typename T>
class Ref;

//引用事件项
class  URGC_DLLAPI RefEventItem {
public:
	char op_type=-1;//0:ref, 1:deref,2:ctor_guard,3:ctor_guard_cancel， 4:set_deleter
	void* source = NULL;
	void* target = NULL;
	std::function<void(void*)> deleter = nullptr;
	string label;
	bool is_del = false;
	bool in_del_record = false;
	//算法核心要保证对同一个对象的引用解引用有序。特别是初始的引用和CtorGuard的引用。中间的引用和解引用对的顺序其实无所谓。
	//64位系统下，读写是原子的，不会出现中间值。
	//不同线程读取可能有误差。
	//因为算法核心主要需要保证对一个对象的唯一所有权的引用顺序。 中间使用时， 引用/解引用对顺序偏差一些，并没有关系。
	//反应到多线程下，可能a线程ref/deref比b线程ref/deref早，但是incid顺序相反，这样也没有关系。
	//初始强引用特别重要。但是对象刚创建时，并不会多线程共享，所以不会有多线程incid可能乱序的问题。
	uint64_t incid = 0; 
	//uint64_t threadid = 0;
};
//效果没有vector好?
class URGC_DLLAPI  RefEventItemList {
public:
	RefEventItemList(int initCap) {
		cap = initCap;
		data = new RefEventItem[initCap];
	}
	inline void push_back(const RefEventItem&& item);
	inline void expandCap();
	int size(){
		return length;
	}
	RefEventItem& at(int i) {
		return data[i];
	}
	void clear();
	RefEventItem* data = 0;
	int cap = 0;
	int length = 0;
};

class RefRecord {
public:
	char op_type = -1;
	void *source;
	int incid;
};
class TargetRefRecords {
public:
	void *target = NULL;
	vector<RefRecord> events;
};

/*唯一强引用gc*/
class URGC_DLLAPI  Urgc {
public:
	//int inited = 329048032;
	Urgc();
	~Urgc();
	int delete_cnt = 0;//删除数量
	vector<string> delete_classnames;//删除的类名
	std::recursive_mutex _mutex;
	//回收线程定时交换collecting和processing,然后对processing逐一处理,处理完后，再次交换然后处理
	std::recursive_mutex swap_collecting_mutex;//交换队列的锁
	//__SpinLock swap_collecting_mutex;//交换队列的锁
	//__SpinLock closure_mutex;//交换队列的锁

	//收集事件列表
	vector<RefEventItem>* collecting = new vector<RefEventItem>(2000);
	//回收处理中列表
	vector<RefEventItem>* processing = new vector<RefEventItem>(2000);
	//没有更快
	//RefEventItemList *collecting = new RefEventItemList(200000);
	//RefEventItemList *processing = new RefEventItemList(200000);

	//延迟删除的队列
	vector<RefMgr*> defer_will_deletes;

	/*RefEventItem *tmplist = new RefEventItem[10]{}; //临时测试
	int tmplistindex = 0;*/

	//入引用管理:记录被引用(target)->所有入引用管理器(记录了引用target的所有source)
	unordered_map<void*, RefMgr> target_in_ref_mgr;
	//出引用管理列表:source=> RefMgr list of targets
	unordered_map<void*, vector<RefMgr*>> out_ref_mgrs_map;
	unordered_map<void*, bool> deleted_records;
	unordered_map<void*, vector<RefEventItem>> target_event_list_db; //记录指针的所有事件，便于调试

	//记录指定target的所有引用事件
	unordered_map<void*, TargetRefRecords> target_ref_records_map;

	TargetRefRecords* get_target_ref_records(void* target);
	bool save_target_ref_records(void* target);
	void record_target_ref_event(RefEventItem& item);

	int refCount = 0;
	int derefCount = 0;
	int guardCount = 0;
	int deguardCount = 0;
	int setDeleterCount = 0;

	//通过被引用者查找入引用管理
	RefMgr* get_ref_mgr_by_target(void* target);
	//不存在就创建 入引用
	RefMgr* goc_ref_mgr_by_target(void* target, std::function<void(void*)> deleter=nullptr);
	//source-target构成Key. 用来唯一引用一个RefMgr
	string fmt_key(void* source, void* target);

	template<typename T>
	void ref(Ref<T> source, void* target, std::function<void(void*)> deleter=nullptr) {
		ref(source.get(), target);// , deleter, typeid(T).name());
	}
	//记录引用
	void ref(void* source, void* target, std::function<void(void*)> deleter=nullptr, string label="");
	void do_ref(void* source, void* target, std::function<void(void*)> deleter=nullptr, string label="");

	//记录出 引用管理器
	void add_out_ref_mgr(void* p, RefMgr* mgr);
	//移除出 引用管理器
	void remove_out_ref_mgr(void* p, RefMgr* mgr);
	/*
	 解引用:从target的被引用列表(all_sources)中删除，删除source->target的出引用记录
	 */
	void deref(void* source, void* target, string label="");
	void do_deref(void* source, void* target);

	/*在线程中处理*/
	void process_on_thread();
	void start_process_thread();
	void stop_process_thread();
	bool process_thread_running = true;
	std::thread *process_thread=NULL;

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
	void delete_will_deletes(vector<RefMgr*>& will_deletes);

	//子树出路寻找完毕后，有些待删除节点，可以回归. 此时的节点，unit_source=null, ghost_source=原强引用。
	void recover_will_deletes(vector<RefMgr*>& will_deletes);
	//子树恢复
	void recover_node(RefMgr* mgr, void* source);
	//子树寻找新的出路
	void children_find_new_chance(void* parent,
		vector<RefMgr*>& will_deletes);
	void child_find_new_chance(void* parent, RefMgr* mgr,
		vector<RefMgr*>& will_deletes);

	template<typename T>
	void set_pointer(Ref<T> source, void** ptr, void* target) {
		*ptr = target;
		ref(source.target, target);
	}

	//设置指针。
	void set_pointer(void* source, void** ptr, void* target);
	//判断是不是循环引用
	//进行环识别：唯一强引用构成树，所以，构成唯一强引用环的唯一可能，是新的强引用来自子树
	//所以，通过上溯父，到根，如果不会找到自己，就说明该引用来自子树外。所以可用。
	bool is_cycle_ref(void* source, void* target);
	//向上判断引用是否可用：非环，也不会到unit_source==nullptr(无效的引用)的情况
	bool check_ref(void* source, void* target);
	//解引用。返回是否需要释放
	bool _deref_then_check_need_delete(RefMgr* mgr, void* source);
	//报告
	void report(std::string title = "");
	//打印所有源
	void report_sources_of(void* target);
	//打印所有源
	void report_source_chain(void* target);

	//报告各类型数量
	void report_type_cnts();
};

//对象构建函数中使用。先把this的强引用占据了，防止被内部的对象占据走，导致this指针被内部强引用，构造函数完成后，就提前释放了this指针
//同时推荐，字段声明处的代码，不要用对this的引用。如: Ref<xx> a{CLOSURE([](){}, this), this}; 中closure引用了this就是不好的。
//如果成员变量初始化，需要引用this,那么也可以：

//正确：
//Ref<Drag> drag{(xx*)CtorGuard(this).obj, this};
//Ref<Drag> drag{CtorGuard(this), this};
//错误,有循环引用问题:
//Ref<Drag> drag{this, this};
class URGC_DLLAPI CtorGuard {
public:
	bool guarding = false;//是否正在保护。 考虑Guard嵌套的问题，内部的Guard不处理
	void* obj = NULL;
	CtorGuard(void *obj);
	~CtorGuard();
	template <typename T>
	operator T*() {
		return (T*)obj;
	}
};

//注意全部变量初始化顺序，随机的问题。 
URGC_DLLAPI extern Urgc& urgc;


//局部变量引用指针


// template<class T>
// class Ref ;
// class RefCopy {
// public:
// 	Ref *from;
// 	Ref *to;
// }
//特别注意： 析构函数一定要是虚函数
template<class T>
class Ref
{
	//static_assert(!std::is_same<T, GcObj>::value, "泛型必须 继承 GcObj\n");
public:
	// static bool in_global_source_transaction = false;
	// std::vector<RefCopy> delay_locals;

	///为了构建 closure,不需要指明类型
	// static start_global_source(){
	// 	in_global_source_transaction = true;
	// }
	// static commit_global_source(){
	// 	in_global_source_transaction = false;
	// 	//应用ref/deref

	// 	for (auto &copy: delay_locals){
	// 		copy.to->deleter = copy.from->deleter;
	// 		copy.to->set_target_and_source(copy.from->target, copy.from->source);
	// 	}
	// 	delay_locals.clear();
	// }

	Ref() {}
	Ref(T* p/*, std::function<void(void*)> deleter = nullptr*/) {
		//static_assert(!std::is_same<T, GcObj>::value, "泛型必须 继承 GcObj\n");
		//this->deleter = deleter;

		// printf("初值构造:%p %s\n", p, typeid(p).name());
#ifdef NO_URGC_REF
		this->target = p;
#else
		set_target(p);
#endif
	}
	Ref(const Ref& from) {
		void* ori_source = source;

		// if (in_global_source_transaction){ //收集复制构造的信息
		// 	RefCopy copy;
		// 	copy.from = from;
		// 	copy.to = this;
		// 	delay_locals.push_back(copy);
		// 	return;
		// }

		//复制构造。当lambda捕获时
		if (source == (GcObj*)ROOT_REF && Ref_get_global_source() != nullptr)
			source = Ref_get_global_source();

		//this->deleter = from.deleter;
		// printf("\tRef复制构造:self:%p(g:%p)=>%p from: %p=>%p\n", ori_source, source, target, from.source, from.target);
#ifdef NO_URGC_REF
		this->target = from.target;
#else
		set_target(from.target);
#endif
	}
	Ref(T* p, void* source/*, std::function<void(void*)> deleter = nullptr*/) {
		//        ASSERT(source, "source不能设为null");
		//        ASSERT(this->source == (GcObj*)ROOT_REF, "Ref.source不能多次设置");

		// printf("初值构造(指定source):%p=>%p %s\n", source, p, typeid(p).name());
		//this->deleter = deleter;
		this->source = source;

#ifdef NO_URGC_REF
		this->target = p;
#else
		set_target(p);
#endif
	}

	~Ref() {
		// printf("Ref释放:%p=>%p\n", source, target);
#ifdef NO_URGC_REF
		target = nullptr;
#else
		deref();
#endif
		// printf("\tRef释放完成:\n");
	}
	inline void set_target(T* target) {
		if (this->target == target) return;

		deref();
		this->target = target;
		ref();
	}
	//void set_target_and_source(T* target, void* source) {
	//	// printf("设置target和source:旧:%p=>%p 新:%p=>%p\n", this->source, this->target, source, target);
	//	deref();
	//	this->source = source;
	//	this->target = target;
	//	ref();
	//}

	inline void deref() {
		if (target) {
			urgc.deref(source, (GcObj*)target);// , typeid(T).name());
			// printf("Ref.deref:%p=>%p\n", source, target);
			target = nullptr;
		}
	}
	inline void ref() {
		if (target) {
			// printf("ref %p %s\n", target, typeid((T*)target).name());
			//if (deleter == nullptr) {
			//	//std function也有可能有动态内存分配？。 Ref与urgc.ref/deref 性能差距有点多 差了2倍？
			//	deleter = [](void* target) {
			//		// printf("Ref.deleter默认删除器,执行删除:%p %s\n", target, typeid((T*)target).name());
			//		//为了调用虚构函数
			//		auto is_void = std::is_same<T, void>::value;
			//		if (is_void) {
			//			auto gcobj = (GcObj*)target;
			//			delete gcobj;
			//		}
			//		else {
			//			auto gcobj = (T*)target;
			//			delete gcobj; //如果用T,就不能支持Ref<void>的情况
			//		}
			//	};
			//}
			//使用typeid(T).name() 会要求T有定义。 如果T只有声明， 如 class Window; 那么编译 Ref<Window> 时，就会失败
			//不要吵了。 urgc内部report时，使用使用typeid(*(GcObj*)target)取得信息，这里根本就不用取
			urgc.ref(source, (GcObj*)target, nullptr);// typeid(target).name());// , deleter, typeid(T).name());
		}
	}
	inline T* get() const {
		return target;
	}
	inline T* operator->() const {
		return target;
	}
	//inline operator T*() const {
	//	return target;
	//}
	inline T operator *() const {
		return *target;
	}
	T** operator&()
	{
		return &target;
	}
	inline operator T* () {
		return target;
	}
	//operator bool() const {
	//	return target != nullptr;
	//}
	/*bool operator==(const Ref<T>& v) const
	{
		return target == v.get();
	}*/
	inline bool operator==(const std::nullptr_t& v) const
	{
		return target == v;
	}
	inline Ref<T>& operator=(const Ref<T>& from)
	{

#ifdef NO_URGC_REF
		target = from.target;
#else
		// printf("\tRef 赋值:%p=>%p\n", source, from.target);
		deref();
		// printf("\tRef 赋值先解引用:%p=>%p\n", source, from.target);
		target = from.target;
		ref();
		// printf("\tRef 赋值引用:%p=>%p\n", source, from.target);
#endif
		return *this;
	}
	inline Ref<T>& operator=(T* from)
	{
#ifdef NO_URGC_REF
		target = from;
#else
		// printf("\tRef 赋值:%p=>%p\n", source, from.target);
		deref();

		// printf("\tRef 赋值先解引用:%p=>%p\n", source, from.target);
		target = from;
		ref();
		// printf("\tRef 赋值引用:%p=>%p\n", source, from.target);
#endif
		return *this;
	}
	template <typename E>
	inline E dy_cast() const {
		return dynamic_cast<E>(target);
	}


public:
	T* target = nullptr; // 被引用的内存
	void* source = (void*)ROOT_REF; // 上级
	//std::function<void(void*)> deleter = nullptr;
};

template <typename _Res, typename... _ArgTypes>
class  Closure;

template<typename F, typename Ret, typename ...Args>
Closure<Ret(Args ...)> helper(Ret(F::*)(Args...));

template<typename F, typename Ret, typename ...Args>
Closure<Ret(Args ...)> helper(Ret(F::*)(Args...) const);

template<typename F, typename Ret, typename ...Args>
URGC_DLLAPI std::function<Ret(Args ...)> helper2(Ret(F::*)(Args...));

template<typename F, typename Ret, typename ...Args>
URGC_DLLAPI std::function<Ret(Args ...)> helper2(Ret(F::*)(Args...) const);

/*
封装lambda.
lambda捕获Ref型局部变量时，没法指定local.source. 会导致引用关系丢失。
所以先new Closure, 提前设置好global_source, 然后
*/
template <typename _Res, typename... _ArgTypes>
class  Closure;

template <typename _Res, typename... _ArgTypes>
class  Closure<_Res(_ArgTypes...)> : public GcObj
{
public:
	Closure()
	{
		Ref_set_global_source(this);
	}
	virtual ~Closure()
	{
		//printf("free closure:%s\n", name.c_str());
	}
	Ref<Closure<_Res(_ArgTypes...)>> _wrap_deprecated(std::function<_Res(_ArgTypes...)> fn)
	{
		assert(this->call == nullptr && "closure不能wrap多次\n");
		assert(Ref_get_global_source() != nullptr && "Closure.wrap要与 create_closure配对使用\n");

		this->call = fn;
		Ref_set_global_source(nullptr);
		//		return this;
		return Ref<Closure<_Res(_ArgTypes...)>>(this);
	}
	/*self:对this的引用。closure里常常需要引用this. 直接引用this,不能让this受urgc管理,有可能出现this已释放的情况
	*/
	template<typename F>
	auto wrap(F f, void* self=nullptr)
	{
		assert(this->call == nullptr && "closure不能wrap多次\n");
		assert(Ref_get_global_source() != nullptr && "Closure.wrap要与 create_closure配对使用\n");


		typedef decltype(helper(&F::operator())) Type;
		typedef decltype(helper2(&F::operator())) Type2;
		//Type* c = new Type();
		//Type2 fn = f;

		auto c = (Type*)this; //类型强转,会不会导致内存空间不同啊:测试不会。 std::function占用固定的空间：64. lambda就会占用不同的空间
		c->self = self;
		//Ref<Type> local_c = c;
		//this->call = fn;
		c->call = f;
		//memcpy(&c->call, &fn, sizeof(fn));
		Ref_set_global_source(nullptr);


#ifndef NO_URGC_REF
		urgc.swap_collecting_mutex.unlock();
#endif
		//urgc.closure_mutex.unlock();
		//		return this;
		return Ref<Type>(c);
	}
	//不用担心回调函数内部把本closure给释放了
	_Res invoke(_ArgTypes ...args) {
		//出现过在ontap回调函数中，触发了页面重建，把ontap回调修改了，导致当前正在执行的ontap函数被释放
		auto tmp = Ref(this); //防止调用回调函数时，回调函数被释放了
		return tmp->call(args...);
	}

	/*const std::function<_Res(_ArgTypes...)>& get_fn() {
		return call;
	}*/
	Ref<void> self{ nullptr, this }; // 对this的引用。 lambda中常会使用this引用。要么外部手动声明Ref<T> that = this;
	//不要设置call函数，容易丢失引用
	//不要直接调用call函数，请用invoke,防止在回调函数释放了本closure



	std::function<_Res(_ArgTypes...)> call = nullptr;
	std::string name;
};


/*创建closure. 你也可以使用: (new Closure<void()>)->wrap([](){});
但是使用此函数，可以少一对括号:
create_closure<void()>()->wrap([](){
});
为什么不能直接在new Closure将lambda传入呢。 因为这样就变成lambda先捕获局部变量，再set_global_source,
导致lambda对局部变量的引用关系失调，可能会导致循环引用，导致内存无法及时释放.
例:

Ref<User> id = new User();
auto closure0 = create_closure<void()>()->wrap([=]() {
		printf("closure hi :%p\n", id.source);
	});
auto closure = create_closure<void()>()->wrap([=]() {
	printf("closure hi :%p\n", id.source);
});
*/
//template <typename T>
URGC_DLLAPI Closure<void()>* closure_of(std::string name);
//{
//	Closure<void()>* closure = new Closure<void()>;
//	closure->name = name;
//	return closure;
//}

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
//#define KEY_LINE (__FILE__ ":" TOSTRING(__LINE__) "\n")
//#define KEY_LINE (__FUNCTION__ ":" TOSTRING(__LINE__))
//因为LineKeep的代码，同一个ctx都是在同一个函数，所以__LINE__足够区分了。 
//如果是跨函数，通常需要添加key来防止函数被多次调用，导致Key冲突。 所以__LINE__就足够了
#define KEY_LINE TOSTRING(__LINE__)

//用法：CLOSURE([=](){})
//注释 对于Ref要使用'='捕获
#define CLOSURE closure_of(KEY_LINE)->wrap
//#define CLOSURE(fn) closure(KEY_LINE)->wrap(fn)



//可以访问到自己函数。用来在回调函数中调用自身
class  URGC_DLLAPI CalleeVoidCallback :public GcObj {
public:
	CalleeVoidCallback(Ref<Closure<void(Ref<CalleeVoidCallback>)>> cb) {
		CtorGuard _(this);
		this->cb = cb;
	}
	void invoke() {
		cb->invoke(this);
	}
	Ref<Closure<void(Ref<CalleeVoidCallback>)>> cb = { 0, this };
};