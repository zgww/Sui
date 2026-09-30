
#include <stdio.h>
#include "./UrgcDll/urgc_api.h"


class User {
	int age = 30
	void say(){
		printf("age=%d\n", self.age)
	}
	void dtor(){
		printf("User.dtor age=%d\n", self.age)
	}
}


int main(){
	urgc_start_process_thread();

	{
		User@ u = new User()
		u.age = 3999;
		u.say();
		printf("hi\n")
	}
	getchar();
	return 0;
}
