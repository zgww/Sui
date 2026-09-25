#include "../User_orc.h"

#include "./httplib.h"


extern "C" {
	Orc$String* _httpGet(Orc$String** __outRef__, const char* host, int port, const char *path, int *status) {
		NEW_CLASS_VAR(Orc$String, ret);

		httplib::Client cli(host, port);
		auto r = cli.Get(path);
		Orc$String$set(ret, r->body.c_str());
		if (status != NULL) {
			*status = r->status;
		}

		return URGC_RETURN_CLASS(ret);
	}
}