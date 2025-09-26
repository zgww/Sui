#pragma once
#include <string>
#include <vector>
#include <format>
#include <memory>
#include <mutex>
#include <functional>
#include <queue>
#include <unordered_map>



/*
lsp组织

主线程读取输入
router Actor用来处理lsp的请求
diagnostics Actor用来ast,生成符号表和诊断信息
代码完成需要其他文件的符号信息，所以也有一个加载工程符号的 Actor
TimerActor定时器Actor,用来实现定时器。 如果有定时需求，就发消息给TimerActor, TimerActor
会在时间到后，发送到时消息给指定的Actor


router 不在主线程，是为了让输出都统一走一个线程。 其他Actor想输出时，就发个消息给routerActor, 则不是自己就printf输出了。
如果在自己线程printf输出，可能会导致消息错乱


didOpen和didChange时，通过diagnosticsActor 生成ast,符号表和诊断信息,可能要做debounce,
debounce可由timer实现

documentSymbol时， 如果有现成的符号表就发回去，没有就先拉倒。 后面有问题(如未及时更新)再说


hover时，有现成的ast和符号表，就识别，没有就跳过

gotoDefinition时，有现成的ast和符号表，就处理，没有就跳过

codeAction时，有现成的ast和符号表，就处理，没有就跳过
executeCommand时，能处理处理，不能处理就showNotification 提示下

completion时，completion会伴随didChange, 所以等待ast和符号表更新后，计算?
其实因为代码的改变是小部分修改，所以用上一版本的ast和符号表也没问题的吧。

识别语句时，可以以expr或者statement来快速识别边界


性能优化
ast、符号表计算和表达式的符号解析比较耗时， 所以能缓存就缓存。
开发过程中,代码的改变是以行为单位的，而且是小部分修改。
可以在didChange中拿到增量修改的内容，然后识别到哪些函数或者类有修改。
更新指定的函数或者类就可以了？ 
先不优化。

*/



//线程组织成actor
//通过消息实现通信


class ActorByThread;

class ActorMail: public std::enable_shared_from_this<ActorMail>{
public:
	int reqId = 0;//请求id
	std::string senderId; //发送者id
	std::string receiverId; //接收者id

	std::string method; //方法,由于是在cpp内部传递的，对象是有类型信息的，所以method其实不用写
	bool bResponse = false;

	ActorByThread* host = NULL;//当前处理此邮件的actor

	//回调处理
	std::function<void(ActorMail* mail)> onResponse;
	std::function<void(ActorMail* self, ActorByThread*actor)> cbHandle;

	bool isRqeuest() {
		return reqId > 0 && !bResponse;
	}
	bool isResponse() {
		return bResponse;
		//return reqId > 0 && method.empty();
	}
	bool isNotification() {
		return reqId == 0;
	}
	virtual void handle(std::shared_ptr<ActorByThread> actor) {
		if (cbHandle != nullptr) {
			extern void log(std::string msg);
			try {
				cbHandle(this, actor.get());
			}
			catch (std::string msg) {
				log(std::format("Actor cbHandle error. msg:{}", msg));
			}
			catch (...) {
				log(std::format("Actor cbHandle error"));
			}
		}
	};

	//就地转为response类型的消息
	void convertToResponseInplace();
	void initAsResponseByRequestMail(ActorMail* reqMail);
};

template <typename T>
std::shared_ptr<T> ActorMail_mkResponseByRequestMail(ActorMail* reqMail) {
	std::shared_ptr<T> resp = std::make_shared<T>();
	resp->initAsResponseByRequestMail(reqMail);
	return resp;
}

class ActorByThread: public std::enable_shared_from_this<ActorByThread> {
public:
	static std::unordered_map<std::string, std::shared_ptr<ActorByThread>> actorHub;
	static std::mutex actorHubMutex;
	static std::shared_ptr<ActorByThread> findActorById(std::string id);
	static void send(std::shared_ptr<ActorMail> mail);

	//会补上reqId, senderId, receiverId
	//发送请求， self=> receiver
	void sendRequest(std::shared_ptr<ActorMail> mail, ActorByThread* receiver);

	//发送通知给自己
	void pushNotification(std::shared_ptr<ActorMail> mail);
	//发送邮件给自己
	void pushMail(std::shared_ptr<ActorMail> mail);

	static std::string generateId();

	ActorByThread(std::string id);
	ActorByThread();
	~ActorByThread();

	void runOnThisActor(std::function<void()> fn);

	std::string id;
	std::queue<std::shared_ptr<ActorMail>> mailbox;
	std::mutex mutex_;
	bool running = true;

	virtual void route(std::shared_ptr<ActorMail> &msg);
	void runLoop();
	virtual void doRun();

	std::shared_ptr<ActorMail> shiftMail();

	virtual void onStart() {};

	void startThread();
	void stopThread();
};

//定时器邮件
class ActorMailTimeout : public ActorMail{
public:
	//多久到时
	int timeoutMillisSeconds = 0;

	//在哪个unix millsSeconds到时
	long long _timeoutAtUnixMs = 0L;
	virtual void handle(std::shared_ptr<ActorByThread> actor) override;
};

class ActorTimer : public ActorByThread{
public:
	std::vector<std::shared_ptr<ActorMailTimeout>> tickingList;
	
	virtual void doRun() override;

	//如果有指定sender,就会在到时间后，发回sender处理
	void setTimeout(int timeoutMillisSeconds, std::function<void()> onTimeout, ActorByThread *sender=nullptr);
	//如果有指定sender,就会在到时间后，发回sender处理
	//[times] -1表示 无限
	void setInterval(int timeoutMillisSeconds, int times, std::function<bool()> onTimeout, ActorByThread* sender = nullptr);
};
class Time {
public:
	static long long nowMs();
	static long long nowSec();
	static void sleepMs(int ms);
};

void test_ActorByThread();
