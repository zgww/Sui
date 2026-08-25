module;
#include <stdio.h>


export module ViewAbout;

export class User {
public:
	int age = 10;

	void say() {
		printf("age:%d\n", age);
	}
};
