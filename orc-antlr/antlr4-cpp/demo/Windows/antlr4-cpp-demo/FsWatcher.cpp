#include "FsWatcher.h"

#ifdef _WIN32



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
#else // !_WIN32 : Linux下基于inotify实现递归监听

#include <sys/inotify.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <map>

class FsWatchLinux : public FsWatch {
public:
	int fd = -1;
	//watch descriptor -> 被监听目录的绝对路径
	std::map<int, std::string> wd2dir;
	//cookie -> 旧的相对路径. 用于把IN_MOVED_FROM/IN_MOVED_TO配对成rename事件
	std::map<uint32_t, std::string> moveFroms;

	~FsWatchLinux() {
		if (fd >= 0) {
			close(fd);
		}
	}

	static bool isDir(const std::string& path) {
		struct stat st;
		if (stat(path.c_str(), &st) != 0) {
			return false;
		}
		return S_ISDIR(st.st_mode);
	}

	std::string relativeToWatchDir(const std::string& dirAbs, const std::string& name) {
		//事件路径与Win32版本保持一致: 相对于watchDir
		std::string rel;
		if (dirAbs.size() > watchDir.size()) {
			rel = dirAbs.substr(watchDir.size());
			//去掉开头的分隔符
			if (!rel.empty() && rel[0] == '/') {
				rel = rel.substr(1);
			}
			if (!rel.empty()) {
				rel += "/";
			}
		}
		return rel + name;
	}

	void addWatchTree(const std::string& dirAbs) {
		//递归为目录及其子目录添加监听(Win32的ReadDirectoryChangesW是递归的)
		int wd = inotify_add_watch(fd, dirAbs.c_str(),
			IN_CREATE | IN_DELETE | IN_MODIFY | IN_MOVED_FROM | IN_MOVED_TO);
		if (wd >= 0) {
			wd2dir[wd] = dirAbs;
		}

		DIR* d = opendir(dirAbs.c_str());
		if (d == NULL) {
			return;
		}
		struct dirent* ent;
		while ((ent = readdir(d)) != NULL) {
			if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
				continue;
			}
			std::string kid = dirAbs + "/" + ent->d_name;
			if (isDir(kid)) {
				addWatchTree(kid);
			}
		}
		closedir(d);
	}

	void emit(std::string action, std::string relPath, std::string oldPath = "") {
		auto ev = std::make_shared<FsWatchEvent>();
		ev->action = action;
		ev->path = relPath;
		ev->oldPath = oldPath;
		onEvent(ev);
	}

	virtual int start() {
		char cwdbuf[4096];
		if (getcwd(cwdbuf, sizeof(cwdbuf)) == NULL) {
			cwdbuf[0] = 0;
		}
		printf("监听文件变化:%s; cwd:%s\n", watchDir.c_str(), cwdbuf);

		fd = inotify_init();
		if (fd < 0) {
			printf("watch failed. inotify_init errno:%d\n", errno);
			return -1;
		}

		addWatchTree(watchDir);

		char buf[64 * 1024] __attribute__((aligned(__alignof__(struct inotify_event))));
		while (true) {
			ssize_t n = read(fd, buf, sizeof(buf));
			if (n <= 0) {
				if (n < 0 && errno == EINTR) {
					continue;
				}
				return 0;
			}

			for (char* p = buf; p < buf + n; ) {
				struct inotify_event* e = (struct inotify_event*)p;
				p += sizeof(struct inotify_event) + e->len;

				auto it = wd2dir.find(e->wd);
				if (it == wd2dir.end()) {
					continue;
				}
				std::string dirAbs = it->second;
				std::string name = e->len > 0 ? e->name : "";
				if (name.empty()) {
					continue;
				}
				std::string kidAbs = dirAbs + "/" + name;
				std::string rel = relativeToWatchDir(dirAbs, name);

				if (e->mask & IN_CREATE) {
					if (e->mask & IN_ISDIR) {
						//新目录要递归加监听
						addWatchTree(kidAbs);
					}
					emit("add", rel);
					printf("added:%s\n", rel.c_str());
				}
				if (e->mask & IN_MOVED_FROM) {
					//先记下, 等配对的IN_MOVED_TO
					moveFroms[e->cookie] = rel;
					printf("move old name:%s\n", rel.c_str());
				}
				if (e->mask & IN_MOVED_TO) {
					if (e->mask & IN_ISDIR) {
						addWatchTree(kidAbs);
					}
					auto mf = moveFroms.find(e->cookie);
					if (mf != moveFroms.end()) {
						//监听树内部的移动/改名
						auto oldRel = mf->second;
						moveFroms.erase(mf);
						emit("rename", rel, oldRel);
						printf("move new name:%s\n", rel.c_str());
					}
					else {
						//从监听树外部移入, 等价于新增
						emit("add", rel);
						printf("added:%s\n", rel.c_str());
					}
				}
				if (e->mask & IN_DELETE) {
					emit("remove", rel);
					printf("removed:%s\n", rel.c_str());
				}
				if (e->mask & IN_MODIFY) {
					if (e->mask & IN_ISDIR) {
						continue;//目录自身元数据变化, 忽略
					}
					emit("modify", rel);
				}
			}
		}
	}
};



std::shared_ptr<FsWatch> FsWatch::createInstance() {
	return std::make_shared<FsWatchLinux>();
}

#endif
