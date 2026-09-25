
#include "SuiDesignerMain_orc.h" 

#include <stdio.h>
#include "./Orc/Orc.h"
#include "../UrgcDll/urgc_api.h"
#include "../UrgcDll/Urgc.h"



void testCppRef(){
	printf("testCppRef\n");
	OrcRef<User> user;
	auto tmp = &user;
	// User* u = mkUser(&user);
	User* u = User_new(&user);
	printf("Ref.target:%p, u:%p", user.target, u);
	user->age = 999;
	user->say(user.get());
}