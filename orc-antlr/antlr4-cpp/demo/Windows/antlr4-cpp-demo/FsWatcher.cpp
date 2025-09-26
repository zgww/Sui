#include "FsWatcher.h"



class FsWatchWin32 : public FsWatch {
public:


	DWORD read_buffer[2048]; // hmmmm.
	HANDLE     directory;
	OVERLAPPED overlapped;

	std::string unicodeToUtf8(WCHAR* wstr, int l) {
		//int l = wcslen(wstr);
		int utf8_len = WideCharToMultiByte(CP_UTF8,       // CodePage
			0,             // dwFlags
			wstr,  // lpWideCharStr
			l / 2, // cchWideChar
			nullptr,       // lpMultiByteStr
			0,             // cbMultiByte
			nullptr,       // lpDefaultChar
			nullptr);     // lpUsedDefaultChar

		char* res = (char*)calloc(utf8_len + 1, 1);


		WideCharToMultiByte(CP_UTF8,       // CodePage
			0,             // dwFlags
			wstr,  // lpWideCharStr
			l / 2, // cchWideChar
			res,     // lpMultiByteStr
			utf8_len,      // cbMultiByte
			nullptr,       // lpDefaultChar
			nullptr);     // lpUsedDefaultChar
		std::string ret(res);
		free(res);

		return ret;
	}


	~FsWatchWin32() {
		CloseHandle(directory);
	}
	//void stop();

	virtual int start() {
		char buf[1024];
		GetCurrentDirectoryA(sizeof(buf), buf);
		printf("监听文件变化:%s; cwd:%s\n", watchDir.c_str(), buf);
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
					auto src = unicodeToUtf8(e->FileName, e->FileNameLength);
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
					auto src = unicodeToUtf8(e->FileName, e->FileNameLength);
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
					auto src = unicodeToUtf8(e->FileName, e->FileNameLength);
					auto ev = std::make_shared<FsWatchEvent>();
					ev->action = "modify";
					ev->path = src;
					onEvent(ev);
					//printf("FILE_ACTION_MODIFIED:%s\n", src.c_str());
					//char* src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
					//FS_MAKE_CALLBACK( FSWATCHER_EVENT_MODIFY, src, 0x0 );
					//fswatcher_free( watcher->allocator, src );
				}
				break;
				case FILE_ACTION_RENAMED_OLD_NAME:
				{
					move_src = unicodeToUtf8(e->FileName, e->FileNameLength);
					printf("move old name:%s\n", move_src.c_str());
					//move_src = fswatcher_build_full_path( watcher, watcher->allocator, ev );
				}
				break;
				case FILE_ACTION_RENAMED_NEW_NAME:
				{
					auto dst_src = unicodeToUtf8(e->FileName, e->FileNameLength);
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