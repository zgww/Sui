// filesense.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>

#include <functional>

class FsWatchEvent {
public:
	std::string action;
	std::string path;
	std::string oldPath;//for rename
};
class FsWatch{
public:
	std::string watchDir = "./";
	std::function<void(std::shared_ptr<FsWatchEvent>)> onEvent;
	virtual int start() = 0;
	virtual ~FsWatch() {};

	static std::shared_ptr<FsWatch> createInstance();
};
class FsWatchWin32 : public FsWatch{
public:


	DWORD read_buffer[2048]; // hmmmm.
	HANDLE     directory;
	OVERLAPPED overlapped;

	std::string unicodeToUtf8(WCHAR* wstr) {
		int l = wcslen(wstr);
		int utf8_len = WideCharToMultiByte(CP_UTF8,       // CodePage
			0,             // dwFlags
			wstr,  // lpWideCharStr
			l, // cchWideChar
			nullptr,       // lpMultiByteStr
			0,             // cbMultiByte
			nullptr,       // lpDefaultChar
			nullptr);     // lpUsedDefaultChar

		char* res = (char*)calloc(utf8_len + 1, 1);


		WideCharToMultiByte(CP_UTF8,       // CodePage
			0,             // dwFlags
			wstr,  // lpWideCharStr
			l, // cchWideChar
			res,     // lpMultiByteStr
			utf8_len,      // cbMultiByte
			nullptr,       // lpDefaultChar
			nullptr);     // lpUsedDefaultChar
		std::string ret(res);
		free(res);

		return ret;
	}


	~FsWatchWin32(){
		CloseHandle(directory);
	}
	//void stop();

	virtual int start() {
		directory = ::CreateFileA(watchDir.c_str(),
			FILE_LIST_DIRECTORY,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL, // security descriptor
			OPEN_EXISTING, // how to create
			FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, // file attributes
			NULL); // file with attributes to copy

		do {
			::ZeroMemory(&overlapped, sizeof(overlapped));
			BOOL success = ::ReadDirectoryChangesW(directory,
				read_buffer,
				sizeof(read_buffer),
				TRUE,
				//watcher->recursive ? TRUE : FALSE,
				FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME,
				0x0,
				&overlapped,
				0x0);
			if (!success) {
				printf("watch failed\n");
				return -1;
			}

			DWORD bytes;
			BOOL res = ::GetOverlappedResult(directory,
				&overlapped,
				&bytes,
				true);
			if (res != TRUE)
				return 0;

			std::string move_src;

			FILE_NOTIFY_INFORMATION* e = (FILE_NOTIFY_INFORMATION*)read_buffer;
			do {
				switch (e->Action) {
				case FILE_ACTION_ADDED:
				{
					auto src = unicodeToUtf8(e->FileName);
					auto ev = std::make_shared<FsWatchEvent>();
					ev->action = "add";
					ev->path = src;
					onEvent(ev);
					printf("added:%s\n", src.c_str());
					//FS_MAKE_CALLBACK( FSWATCHER_EVENT_CREATE, src, 0x0 );
					//fswatcher_free( watcher->allocator, src );
				}
				break;
				case FILE_ACTION_REMOVED:
				{
					auto src = unicodeToUtf8(e->FileName);
					auto ev = std::make_shared<FsWatchEvent>();
					ev->action = "remove";
					ev->path = src;
					onEvent(ev);
					printf("removed:%s\n", src.c_str());
					//char* src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
					//FS_MAKE_CALLBACK( FSWATCHER_EVENT_REMOVE, src, 0x0 );
					//fswatcher_free( watcher->allocator, src );
				}
				break;
				case FILE_ACTION_MODIFIED:
				{
					auto src = unicodeToUtf8(e->FileName);
					auto ev = std::make_shared<FsWatchEvent>();
					ev->action = "modify";
					ev->path = src;
					onEvent(ev);
					printf("modified:%s\n", src.c_str());
					//char* src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
					//FS_MAKE_CALLBACK( FSWATCHER_EVENT_MODIFY, src, 0x0 );
					//fswatcher_free( watcher->allocator, src );
				}
				break;
				case FILE_ACTION_RENAMED_OLD_NAME:
				{
					move_src = unicodeToUtf8(e->FileName);
					printf("move old name:%s\n", move_src.c_str());
					//move_src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
				}
				break;
				case FILE_ACTION_RENAMED_NEW_NAME:
				{
					auto dst_src = unicodeToUtf8(e->FileName);
					printf("move new name:%s\n", dst_src.c_str());

					auto ev = std::make_shared<FsWatchEvent>();
					ev->action = "rename";
					ev->path = dst_src;
					ev->oldPath = move_src;
					move_src = "";
					onEvent(ev);
					//char* dst = fswatcher_build_full_path( watcher, watcher->allocator, ev );
					//FS_MAKE_CALLBACK( FSWATCHER_EVENT_MOVE, move_src, dst );
					//fswatcher_free( watcher->allocator, move_src );
					//fswatcher_free( watcher->allocator, dst );
					//move_src = 0x0;
				}
				break;
				default:
					printf("unhandled action %d\n", e->Action);
				}

				if (e->NextEntryOffset == 0)
					break;
				e = (FILE_NOTIFY_INFORMATION*)((char*)e + e->NextEntryOffset);
			} while (true);

		} while (true);
	}
};

std::shared_ptr<FsWatch> FsWatch::createInstance() {
	return std::make_shared<FsWatchWin32>();
}




static std::string build_path(FILE_NOTIFY_INFORMATION* ev) {
	size_t path_len = (size_t)(ev->FileNameLength / 2);

	int utf8_len = WideCharToMultiByte(CP_UTF8,       // CodePage
		0,             // dwFlags
		ev->FileName,  // lpWideCharStr
		(int)path_len, // cchWideChar
		nullptr,       // lpMultiByteStr
		0,             // cbMultiByte
		nullptr,       // lpDefaultChar
		nullptr);     // lpUsedDefaultChar

	char* res = (char*)calloc(utf8_len + 1, 1);


	WideCharToMultiByte(CP_UTF8,       // CodePage
		0,             // dwFlags
		ev->FileName,  // lpWideCharStr
		(int)path_len, // cchWideChar
		res,     // lpMultiByteStr
		utf8_len,      // cbMultiByte
		nullptr,       // lpDefaultChar
		nullptr);     // lpUsedDefaultChar
	std::string ret(res);
	free(res);

	return ret;
}
int main() {
	SetConsoleOutputCP(65001);

	std::cout << "Hello World!\n";
	auto watch = FsWatch::createInstance();

	const char* watch_dir = "C:\\ws\\oms-ts\\orc-antlr\\antlr4-cpp\\fssense\\tmp";
	watch->watchDir = watch_dir;
	watch->onEvent = [](std::shared_ptr<FsWatchEvent> ev) {
		printf("action:%s, %s %s\n", ev->action.c_str(), ev->path.c_str(), ev->oldPath.c_str());
	};
	watch->start();
}
int main2() {
	SetConsoleOutputCP(65001);

	std::cout << "Hello World!\n";
	DWORD read_buffer[2048]; // hmmmm.


	const char* watch_dir = "C:\\ws\\oms-ts\\orc-antlr\\antlr4-cpp\\fssense\\tmp";
	HANDLE     directory;
	OVERLAPPED overlapped;
	directory = ::CreateFileA(watch_dir,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL, // security descriptor
		OPEN_EXISTING, // how to create
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, // file attributes
		NULL); // file with attributes to copy


	do {
		::ZeroMemory(&overlapped, sizeof(overlapped));

		BOOL success = ::ReadDirectoryChangesW(directory,
			read_buffer,
			sizeof(read_buffer),
			TRUE,
			//watcher->recursive ? TRUE : FALSE,
			FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME,
			0x0,
			&overlapped,
			0x0);
		if (!success) {
			printf("watch failed\n");
			return -1;
		}



		DWORD bytes;
		BOOL res = ::GetOverlappedResult(directory,
			&overlapped,
			&bytes,
			true);
		if (res != TRUE)
			return 0;

		char* move_src = 0x0;

		FILE_NOTIFY_INFORMATION* ev = (FILE_NOTIFY_INFORMATION*)read_buffer;
		do {
			switch (ev->Action) {
			case FILE_ACTION_ADDED:
			{
				auto src = build_path(ev);
				printf("added:%s\n", src.c_str());
				//FS_MAKE_CALLBACK( FSWATCHER_EVENT_CREATE, src, 0x0 );
				//fswatcher_free( watcher->allocator, src );
			}
			break;
			case FILE_ACTION_REMOVED:
			{
				auto src = build_path(ev);
				printf("removed:%s\n", src.c_str());
				//char* src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
				//FS_MAKE_CALLBACK( FSWATCHER_EVENT_REMOVE, src, 0x0 );
				//fswatcher_free( watcher->allocator, src );
			}
			break;
			case FILE_ACTION_MODIFIED:
			{
				auto src = build_path(ev);
				printf("modified:%s\n", src.c_str());
				//char* src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
				//FS_MAKE_CALLBACK( FSWATCHER_EVENT_MODIFY, src, 0x0 );
				//fswatcher_free( watcher->allocator, src );
			}
			break;
			case FILE_ACTION_RENAMED_OLD_NAME:
			{
				auto move_src = build_path(ev);
				printf("move old name:%s\n", move_src.c_str());
				//move_src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
			}
			break;
			case FILE_ACTION_RENAMED_NEW_NAME:
			{
				auto dst_src = build_path(ev);
				printf("move new name:%s\n", dst_src.c_str());
				//char* dst = fswatcher_build_full_path( watcher, watcher->allocator, ev );
				//FS_MAKE_CALLBACK( FSWATCHER_EVENT_MOVE, move_src, dst );
				//fswatcher_free( watcher->allocator, move_src );
				//fswatcher_free( watcher->allocator, dst );
				//move_src = 0x0;
			}
			break;
			default:
				printf("unhandled action %d\n", ev->Action);
			}

			if (ev->NextEntryOffset == 0)
				break;
			ev = (FILE_NOTIFY_INFORMATION*)((char*)ev + ev->NextEntryOffset);
		} while (true);
	} while (true);
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
