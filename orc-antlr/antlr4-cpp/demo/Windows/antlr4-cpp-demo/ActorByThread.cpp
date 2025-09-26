#include "ActorByThread.h"
#include <format>


void log(std::string s);

std::mutex ActorByThread::actorHubMutex;
std::unordered_map<std::string, std::shared_ptr<ActorByThread>> ActorByThread::actorHub;

std::shared_ptr<ActorByThread> ActorByThread::findActorById(std::string id) {
	if (!id.empty()) {
		std::lock_guard<std::mutex> g(actorHubMutex);
		if (actorHub.contains(id)) {
			auto actor = actorHub[id];
			return actor;
		}
	}
	return nullptr;
}

void ActorByThread::send(std::shared_ptr<ActorMail> mail) {
	auto actor = findActorById(mail->receiverId);
	if (actor) {
		actor->pushMail(mail);
	}
	else {
		log(std::format("send mail error. actor not found by id={}\n", mail->receiverId));
	}
}

ActorByThread::ActorByThread()
	: ActorByThread(generateId())
{

}

static int nextIntId() {
	static int gid = 0;
	gid++;
	return gid;
}
std::string ActorByThread::generateId() {
	static std::mutex _mutex;
	static int gid = 0;
	std::lock_guard<std::mutex> g(_mutex);
	gid++;
	auto id = std::format("actor{}", gid);
	return id;
}

ActorByThread::ActorByThread(std::string id) {
	this->id = id;
}
ActorByThread::~ActorByThread() {
}

void ActorByThread::runOnThisActor(std::function<void()> fn)
{
	auto mail = std::make_shared<ActorMail>();
	mail->cbHandle = [=](ActorMail* mail, ActorByThread* actor) {
		fn();
	};
	this->pushNotification(mail);
}

void ActorByThread::route(std::shared_ptr<ActorMail>& mail) {
	if (mail->isResponse()) {
		log(std::format("\trecv response:{} {}\n", mail->reqId, mail->method));
		mail->host = this;
		mail->onResponse(mail.get());
		return;
	}
	if (1) {
		mail->host = this;
		mail->handle(this->shared_from_this());
		return;
	}

	auto id = std::this_thread::get_id();

	if (mail->isNotification()) {
		log(std::format("on notification threadid:{}, reqId:{}, method:{} {}=>{}\n"
			, *(unsigned int*)&id
			, mail->reqId
			, mail->method
			, mail->senderId
			, mail->receiverId
		));
		return;
	}
	log(std::format("handle threadid:{}, reqId:{}, method:{} {}=>{}\n"
		, *(unsigned int*)&id
		, mail->reqId
		, mail->method
		, mail->senderId 
		, mail->receiverId
	));
	if (mail->isRqeuest()) {
		auto resp = ActorMail_mkResponseByRequestMail<ActorMail>(mail.get());
		ActorByThread::send(resp);
	}
}

void ActorByThread::runLoop() {
	log(std::format("ActorByThread[{}] start working\n", id));
	//在线程内持有引用，防止self被释放
	auto self = this->shared_from_this();
	try {
		this->onStart();

		while (this->running) {
			this->doRun();
		}
	}
	catch (std::exception ex) {
		log(std::format("runLoop exception:{}\n", ex.what()));
	}
	catch (std::string msg) {
		log(std::format("runLoop exception msg:{}\n", msg));
	}
	catch (...) {
		log(std::format("runLoop exception\n"));
	}

	//移除， 
	{
		std::lock_guard<std::mutex> g(actorHubMutex);
		if (actorHub.contains(id)) {
			actorHub.erase(actorHub.find(id));
		}
	}
}

void ActorByThread::doRun() {
	std::shared_ptr<ActorMail> mail = shiftMail();
	if (mail) {
		this->route(mail);
	}
	else {
		//目前没有消息
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

std::shared_ptr<ActorMail> ActorByThread::shiftMail() {
	std::lock_guard<std::mutex> g(mutex_);
	//取出邮件
	if (mailbox.empty()) {
		return nullptr;
	}

	auto mail = mailbox.front();
	mailbox.pop();
	return mail;
}

void ActorByThread::pushMail(std::shared_ptr<ActorMail> mail) {
	if (this->running) {
		if (mail->receiverId.empty()) {
			mail->receiverId = this->id;
		}
		std::lock_guard<std::mutex> g(mutex_);
		mailbox.push(mail);
	}
}

void ActorByThread::startThread() {
	auto self = this->shared_from_this();
	std::lock_guard<std::mutex> g(actorHubMutex);
	actorHub[this->id] = self;

	std::thread t([&]() {
		this->runLoop();
		}
	);
	t.detach();
}

void ActorByThread::stopThread() {
	this->running = false;
}

void ActorMail::initAsResponseByRequestMail(ActorMail* reqMail) {
	this->reqId = reqMail->reqId;
	this->senderId = reqMail->receiverId;
	this->receiverId = reqMail->senderId;
	this->method = reqMail->method;
	this->bResponse = true;
}

void test_ActorByThread() {
	auto a = std::make_shared<ActorByThread>();
	auto b = std::make_shared<ActorByThread>();
	auto c = std::make_shared<ActorByThread>();
	auto timer = std::make_shared<ActorTimer>();
	a->startThread();
	b->startThread();
	c->startThread();
	timer->startThread();
	{
		long long prevSec = Time::nowMs();
		timer->setTimeout(2000, [=]() {
			long long nowSec = Time::nowMs();
			printf("do timeout cost:%lld\n", nowSec - prevSec);
			});
	}
	{
		timer->setInterval(2000, -1, [=]() {
			long long nowSec = Time::nowSec();
			printf("do interval %lld\n", nowSec);
			return true;
		});
	}

	for (int i = 0; i < 10; i++) {
		auto receiver = a;
		if (i % 3 == 1) {
			receiver = b;
		}
		if (i % 3 == 2) {
			receiver = c;
		}

		auto mail = std::make_shared<ActorMail>();
		mail->method = std::format("greet {}", i);
		mail->receiverId = receiver->id;
		mail->reqId = nextIntId();
		mail->senderId = a->id;
		receiver->pushMail(mail);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	printf("done\n");
}



void ActorMailTimeout::handle(std::shared_ptr<ActorByThread> actor) {
	auto timer = std::dynamic_pointer_cast<ActorTimer>(actor);

	if (timer == nullptr) {
		log("handle Timeout mail error\n. actor is not ActorTimer");
		return;
	}

	long long nowMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	this->_timeoutAtUnixMs = nowMs + this->timeoutMillisSeconds;

	//加入tickList
	timer->tickingList.push_back(
		std::dynamic_pointer_cast<ActorMailTimeout>
		(this->shared_from_this())
	);
}
void ActorTimer::doRun() {
	long long nowMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	//tick
	for (int i = tickingList.size() - 1; i >= 0; i--) {
		auto& t = tickingList[i];
		if (nowMs >= t->_timeoutAtUnixMs) {//到时了
			//发送响应回去
			//auto resp = ActorMail_mkResponseByRequestMail<ActorMailTimeout>(t.get());
			t->convertToResponseInplace();
			if (t->receiverId.empty()) {//没有接收者， 直接就地callback
				t->onResponse(t.get());
			} else {
				ActorByThread::send(t);
			}

			tickingList.erase(tickingList.begin() + i);
		}
	}
	ActorByThread::doRun();
}
void ActorMail::convertToResponseInplace() {
	auto bkSenderId = this->senderId;
	//对调sender/receiver
	this->senderId = this->receiverId;
	this->receiverId = bkSenderId;
	//标记为response
	this->bResponse = true;
}
void ActorByThread::sendRequest(std::shared_ptr<ActorMail> mail, ActorByThread* receiver) {
	if (receiver == NULL) {
		throw std::format("no receiver");
	}

	if (mail->reqId == 0) {
		mail->reqId = nextIntId();
	}

	if (mail->senderId.empty()) {
		mail->senderId = this->id;
	}
	if (mail->receiverId.empty()) {
		mail->receiverId = receiver->id;
	}

	ActorByThread::send(mail);
}
void ActorByThread::pushNotification(std::shared_ptr<ActorMail> mail)
{
	if (mail->receiverId.empty()) {
		mail->receiverId = this->id;
	}

	this->pushMail(mail);
}
void ActorTimer::setTimeout(int timeoutMillisSeconds, std::function<void()> onTimeout, ActorByThread* sender) {
	auto timeout = std::make_shared<ActorMailTimeout>();
	timeout->reqId = nextIntId();
	timeout->timeoutMillisSeconds = timeoutMillisSeconds;
	if (sender) {
		timeout->senderId = sender->id;
	}
	timeout->onResponse = [onTimeout](ActorMail *m) {
		//log(std::format("on timeout\n"));
		onTimeout();
	};
	this->pushMail(timeout);
}
class _Interval {
public:
	int times;
};
void ActorTimer::setInterval(int timeoutMillisSeconds, int times, std::function<bool()> onTimeout, ActorByThread* sender)
{
	auto timer = std::dynamic_pointer_cast<ActorTimer>(this->shared_from_this());
	setTimeout(timeoutMillisSeconds, [=]() {
		//printf("set timeout...\n");
		try {
			if (onTimeout()) {
				return;
			}
		}
		catch (...) {
			log("setInterval.onTimeout exception\n");
		}
		auto _t = times;
		if (_t > 0) {
			_t--;
		}
		if (_t != 0) {
			timer->setInterval(timeoutMillisSeconds, _t, onTimeout);
		}
	}, sender);
}

long long Time::nowMs()
{
	long long nowMs =
		std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	return nowMs;
}

long long Time::nowSec()
{
	long long sec =
		std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()).count();
	return sec;
}

void Time::sleepMs(int ms)
{
	//目前没有消息
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
