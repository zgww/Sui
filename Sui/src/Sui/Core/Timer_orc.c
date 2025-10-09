
#include "Timer_orc.h" 

#include <stdint.h>
#include <stdio.h>
#include "../../../UrgcDll/urgc_api.h"
#include "../../Orc/List_orc.h"
#include "../../Orc/Time_orc.h"
#include "../../Orc/Math_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Thread_orc.h"
#include "../../Orc/Mutex_orc.h"


// static struct 
typedef struct tagSuiCore$__Block_169_26 SuiCore$__Block_169_26;

typedef struct tagSuiCore$__Block_185_33 SuiCore$__Block_185_33;

typedef struct tagSuiCore$__Block_366_17 SuiCore$__Block_366_17;

typedef struct tagSuiCore$__Block_401_4 SuiCore$__Block_401_4;

typedef struct tagSuiCore$__Closure_172_20 SuiCore$__Closure_172_20;

typedef struct tagSuiCore$__Closure_188_20 SuiCore$__Closure_188_20;

typedef struct tagSuiCore$__Closure_375_30 SuiCore$__Closure_375_30;

typedef struct tagSuiCore$__Closure_397_30 SuiCore$__Closure_397_30;

typedef struct tagSuiCore$__Closure_403_35 SuiCore$__Closure_403_35;



struct tagSuiCore$__Block_169_26 {
	SuiCore$TimerMgr*  self ;
};





struct tagSuiCore$__Block_185_33 {
	SuiCore$TimerMgr*  self ;
};





struct tagSuiCore$__Block_366_17 {
	SuiCore$AnimStep*  self ;
};





struct tagSuiCore$__Block_401_4 {
	SuiCore$TimerTestEnt*  ent ;
	SuiCore$Timer*  t ;
};





struct tagSuiCore$__Closure_172_20 {
	void  (*invoke)(SuiCore$__Closure_172_20 *  self);
	Vtable_Object *  vtable ;
	SuiCore$__Block_169_26*  __var___Block_169_26 ;
};





struct tagSuiCore$__Closure_188_20 {
	void  (*invoke)(SuiCore$__Closure_188_20 *  self);
	Vtable_Object *  vtable ;
	SuiCore$__Block_185_33*  __var___Block_185_33 ;
};





struct tagSuiCore$__Closure_375_30 {
	bool  (*invoke)(SuiCore$__Closure_375_30 *  self);
	Vtable_Object *  vtable ;
	SuiCore$__Block_366_17*  __var___Block_366_17 ;
};





struct tagSuiCore$__Closure_397_30 {
	void  (*invoke)(SuiCore$__Closure_397_30 *  self);
	Vtable_Object *  vtable ;
};





struct tagSuiCore$__Closure_403_35 {
	void  (*invoke)(SuiCore$__Closure_403_35 *  self);
	Vtable_Object *  vtable ;
	SuiCore$__Block_401_4*  __var___Block_401_4 ;
};





// static function declaration
static void  __finiBlock___Block_169_26(SuiCore$__Block_169_26 *  self);
static void  __finiBlock___Block_185_33(SuiCore$__Block_185_33 *  self);
static void  __finiBlock___Block_366_17(SuiCore$__Block_366_17 *  self);
static void  __finiBlock___Block_401_4(SuiCore$__Block_401_4 *  self);
static void  __fn___Closure_172_20(SuiCore$__Closure_172_20 *  self);
static void  __fini___Closure_172_20(SuiCore$__Closure_172_20 *  self);
static SuiCore$__Closure_172_20*  __make___Closure_172_20(SuiCore$__Closure_172_20 **  __outRef__, SuiCore$__Block_169_26 *  __var___Block_169_26);
static void  __fn___Closure_188_20(SuiCore$__Closure_188_20 *  self);
static void  __fini___Closure_188_20(SuiCore$__Closure_188_20 *  self);
static SuiCore$__Closure_188_20*  __make___Closure_188_20(SuiCore$__Closure_188_20 **  __outRef__, SuiCore$__Block_185_33 *  __var___Block_185_33);
static bool  __fn___Closure_375_30(SuiCore$__Closure_375_30 *  self);
static void  __fini___Closure_375_30(SuiCore$__Closure_375_30 *  self);
static SuiCore$__Closure_375_30*  __make___Closure_375_30(SuiCore$__Closure_375_30 **  __outRef__, SuiCore$__Block_366_17 *  __var___Block_366_17);
static void  __fn___Closure_397_30(SuiCore$__Closure_397_30 *  self);
static void  __fini___Closure_397_30(SuiCore$__Closure_397_30 *  self);
static SuiCore$__Closure_397_30*  __make___Closure_397_30(SuiCore$__Closure_397_30 **  __outRef__);
static void  __fn___Closure_403_35(SuiCore$__Closure_403_35 *  self);
static void  __fini___Closure_403_35(SuiCore$__Closure_403_35 *  self);
static SuiCore$__Closure_403_35*  __make___Closure_403_35(SuiCore$__Closure_403_35 **  __outRef__, SuiCore$__Block_401_4 *  __var___Block_401_4);



//vtable instance
Vtable_SuiCore$Timer _vtable_SuiCore$Timer;

// init meta

void SuiCore$Timer_initMeta(Vtable_SuiCore$Timer *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "alive", OrcMetaType_bool, offsetof(SuiCore$Timer, alive), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "isInterval", OrcMetaType_bool, offsetof(SuiCore$Timer, isInterval), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "intervalMs", OrcMetaType_int, offsetof(SuiCore$Timer, intervalMs), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "remainMs", OrcMetaType_int, offsetof(SuiCore$Timer, remainMs), 0, 0, 0, 0);//int
	orc_metaField_class(&pNext, "name", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiCore$Timer, name), true, false, 1);

	orc_metaField_method(&pNext, "restart", offsetof(SuiCore$Timer, restart));
	orc_metaField_method(&pNext, "start", offsetof(SuiCore$Timer, start));
	orc_metaField_method(&pNext, "cancel", offsetof(SuiCore$Timer, cancel));
	orc_metaField_method(&pNext, "fire", offsetof(SuiCore$Timer, fire));
	orc_metaField_method(&pNext, "onTick", offsetof(SuiCore$Timer, onTick));
}


// vtable init


Vtable_SuiCore$Timer* Vtable_SuiCore$Timer_init(Vtable_SuiCore$Timer* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$Timer;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$Timer_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$Timer";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$Timer_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$Timer_fini(SuiCore$Timer *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$Timer*)self)->name);

}

// init fields function


void SuiCore$Timer_init_fields(SuiCore$Timer *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$Timer_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiCore$Timer*)self)->runFunc, NULL);
	((SuiCore$Timer*)self)->alive = false;
	((SuiCore$Timer*)self)->isInterval = false;
	((SuiCore$Timer*)self)->intervalMs = 0;
	((SuiCore$Timer*)self)->remainMs = 0;
	urgc_set_field_class(self, (void**)&((SuiCore$Timer*)self)->name, NULL);
    }
	((Object*)self)->dtor = (void*)SuiCore$Timer$dtor;
	((SuiCore$Timer*)self)->restart = (void*)SuiCore$Timer$restart;
	((SuiCore$Timer*)self)->start = (void*)SuiCore$Timer$start;
	((SuiCore$Timer*)self)->cancel = (void*)SuiCore$Timer$cancel;
	((SuiCore$Timer*)self)->fire = (void*)SuiCore$Timer$fire;
	((SuiCore$Timer*)self)->onTick = (void*)SuiCore$Timer$onTick;
}

// init function

void SuiCore$Timer_init(SuiCore$Timer *self, void *pOwner){
    Vtable_SuiCore$Timer_init(&_vtable_SuiCore$Timer);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$Timer;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$Timer_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$Timer * SuiCore$Timer_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$Timer *self = calloc(1, sizeof(SuiCore$Timer));
	
    SuiCore$Timer_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$Timer$dtor(SuiCore$Timer *  self){
	
}


void  SuiCore$Timer$restart(SuiCore$Timer *  self){
	self->cancel(self) ;
	self->start(self) ;
}


void  SuiCore$Timer$start(SuiCore$Timer *  self){
	if (self->alive) {
		return ; 
	}
	self->remainMs = self->intervalMs;
	self->alive = true;
	URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  mgr = SuiCore$insTimerMgr((mgr = NULL,&mgr)) ;
	mgr->addItemOnce(mgr, self) ;
}


void  SuiCore$Timer$cancel(SuiCore$Timer *  self){
	self->alive = false;
}


void  SuiCore$Timer$fire(SuiCore$Timer *  self){
	if (self->remainMs <= 0) {
		if (self->alive) {
			if (self->runFunc != NULL) {
				(*(self->runFunc))((void * )(self->runFunc)) ;
			}
		}
		if (self->isInterval) {
			self->remainMs = self->intervalMs;
		}
		else {
			self->alive = false;
		}
	}
}


bool  SuiCore$Timer$onTick(SuiCore$Timer *  self, int  dtMs){
	if (self->remainMs < 0) {
		return false; 
	}
	self->remainMs = self->remainMs - dtMs;
	return self->remainMs < 0; 
}




//vtable instance
Vtable_SuiCore$TimerMgr _vtable_SuiCore$TimerMgr;

// init meta

void SuiCore$TimerMgr_initMeta(Vtable_SuiCore$TimerMgr *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "items", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$TimerMgr, items), true, false, 1);
	orc_metaField_class(&pNext, "itemsMutex", ((Vtable_Object*)Vtable_Orc$Mutex_init(0)), offsetof(SuiCore$TimerMgr, itemsMutex), true, false, 1);
	orc_metaField_class(&pNext, "fireings", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiCore$TimerMgr, fireings), true, false, 1);
	orc_metaField_class(&pNext, "fireingsMutex", ((Vtable_Object*)Vtable_Orc$Mutex_init(0)), offsetof(SuiCore$TimerMgr, fireingsMutex), true, false, 1);

	orc_metaField_method(&pNext, "addItemOnce", offsetof(SuiCore$TimerMgr, addItemOnce));
	orc_metaField_method(&pNext, "addItem", offsetof(SuiCore$TimerMgr, addItem));
	orc_metaField_method(&pNext, "fire", offsetof(SuiCore$TimerMgr, fire));
	orc_metaField_method(&pNext, "tick", offsetof(SuiCore$TimerMgr, tick));
	orc_metaField_method(&pNext, "clearDeadTimers", offsetof(SuiCore$TimerMgr, clearDeadTimers));
	orc_metaField_method(&pNext, "startThreadTick", offsetof(SuiCore$TimerMgr, startThreadTick));
	orc_metaField_method(&pNext, "startThreadTickAndFire", offsetof(SuiCore$TimerMgr, startThreadTickAndFire));
}


// vtable init


Vtable_SuiCore$TimerMgr* Vtable_SuiCore$TimerMgr_init(Vtable_SuiCore$TimerMgr* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TimerMgr;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TimerMgr_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TimerMgr";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TimerMgr_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$TimerMgr_fini(SuiCore$TimerMgr *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	urgc_fini_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->items);
	urgc_fini_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->itemsMutex);
	urgc_fini_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->fireings);
	urgc_fini_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->fireingsMutex);

}

// init fields function


void SuiCore$TimerMgr_init_fields(SuiCore$TimerMgr *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$TimerMgr_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->items, Orc$List_new(&tmpNewOwner_1) );
	URGC_VAR_CLEANUP_CLASS Orc$Mutex*  tmpNewOwner_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->itemsMutex, Orc$Mutex_new(&tmpNewOwner_2) );
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->fireings, Orc$List_new(&tmpNewOwner_3) );
	URGC_VAR_CLEANUP_CLASS Orc$Mutex*  tmpNewOwner_4 = NULL;
	urgc_set_field_class(self, (void**)&((SuiCore$TimerMgr*)self)->fireingsMutex, Orc$Mutex_new(&tmpNewOwner_4) );
    }
	((Object*)self)->dtor = (void*)SuiCore$TimerMgr$dtor;
	((SuiCore$TimerMgr*)self)->addItemOnce = (void*)SuiCore$TimerMgr$addItemOnce;
	((SuiCore$TimerMgr*)self)->addItem = (void*)SuiCore$TimerMgr$addItem;
	((SuiCore$TimerMgr*)self)->fire = (void*)SuiCore$TimerMgr$fire;
	((SuiCore$TimerMgr*)self)->tick = (void*)SuiCore$TimerMgr$tick;
	((SuiCore$TimerMgr*)self)->clearDeadTimers = (void*)SuiCore$TimerMgr$clearDeadTimers;
	((SuiCore$TimerMgr*)self)->startThreadTick = (void*)SuiCore$TimerMgr$startThreadTick;
	((SuiCore$TimerMgr*)self)->startThreadTickAndFire = (void*)SuiCore$TimerMgr$startThreadTickAndFire;
}

// init function

void SuiCore$TimerMgr_init(SuiCore$TimerMgr *self, void *pOwner){
    Vtable_SuiCore$TimerMgr_init(&_vtable_SuiCore$TimerMgr);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TimerMgr;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TimerMgr_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TimerMgr * SuiCore$TimerMgr_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TimerMgr *self = calloc(1, sizeof(SuiCore$TimerMgr));
	
    SuiCore$TimerMgr_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$TimerMgr$dtor(SuiCore$TimerMgr *  self){
	printf("free TimerMgr:%p\n", self) ;
}


void  SuiCore$TimerMgr$addItemOnce(SuiCore$TimerMgr *  self, SuiCore$Timer *  timer){
	self->itemsMutex->lock(self->itemsMutex) ;
	if (!self->items->has(self->items, timer) ) {
		self->items->add(self->items, timer) ;
	}
	self->itemsMutex->unlock(self->itemsMutex) ;
}


void  SuiCore$TimerMgr$addItem(SuiCore$TimerMgr *  self, SuiCore$Timer *  timer){
	self->itemsMutex->lock(self->itemsMutex) ;
	self->items->add(self->items, timer) ;
	self->itemsMutex->unlock(self->itemsMutex) ;
}


void  SuiCore$TimerMgr$fire(SuiCore$TimerMgr *  self){
	if (self->fireings->size(self->fireings)  > 0) {
		self->fireingsMutex->lock(self->fireingsMutex) ;
		int  l = self->fireings->size(self->fireings) ;
		for (int  i = 0; i < l; i++) {
			SuiCore$Timer *  timer = (SuiCore$Timer * )self->fireings->get(self->fireings, i) ;
			timer->fire(timer) ;
		}
		self->fireings->clear(self->fireings) ;
		self->fireingsMutex->unlock(self->fireingsMutex) ;
	}
}


void  SuiCore$TimerMgr$tick(SuiCore$TimerMgr *  self, int  dtMs){
	self->itemsMutex->lock(self->itemsMutex) ;
	int  l = self->items->size(self->items) ;
	for (int  i = 0; i < l; i++) {
		SuiCore$Timer *  timer = (SuiCore$Timer * )self->items->get(self->items, i) ;
		if (timer != NULL && timer->alive) {
			bool  fireing = timer->onTick(timer, dtMs) ;
			if (fireing) {
				self->fireingsMutex->lock(self->fireingsMutex) ;
				self->fireings->add(self->fireings, timer) ;
				self->fireingsMutex->unlock(self->fireingsMutex) ;
			}
		}
	}
	self->clearDeadTimers(self) ;
	self->itemsMutex->unlock(self->itemsMutex) ;
}


void  SuiCore$TimerMgr$clearDeadTimers(SuiCore$TimerMgr *  self){
	for (int  i = self->items->size(self->items)  - 1; i >= 0; i--) {
		SuiCore$Timer *  timer = (SuiCore$Timer * )self->items->get(self->items, i) ;
		if (!timer->alive) {
			self->items->removeAt(self->items, i) ;
		}
	}
}


void  SuiCore$TimerMgr$startThreadTick(SuiCore$TimerMgr *  self){
	URGC_VAR_CLEANUP SuiCore$__Block_169_26*  __var___Block_169_26 = (__var___Block_169_26=NULL,urgc_init_var((void**)&__var___Block_169_26, orc_alloc_and_set_deleter(sizeof(SuiCore$__Block_169_26) , __finiBlock___Block_169_26) ));
	urgc_set_field_class(__var___Block_169_26, (void * )offsetof(SuiCore$__Block_169_26, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$Thread*  t = (t=NULL,urgc_init_var_class((void**)&t, Orc$Thread_new(&t) ));
	URGC_VAR_CLEANUP SuiCore$__Closure_172_20*  tmpReturn_1 = NULL;
	urgc_set_field(t, (void * )offsetof(Orc$Thread, runFunc) , __make___Closure_172_20(&tmpReturn_1, __var___Block_169_26) ) ;
	t->start(t) ;
}


void  SuiCore$TimerMgr$startThreadTickAndFire(SuiCore$TimerMgr *  self){
	URGC_VAR_CLEANUP SuiCore$__Block_185_33*  __var___Block_185_33 = (__var___Block_185_33=NULL,urgc_init_var((void**)&__var___Block_185_33, orc_alloc_and_set_deleter(sizeof(SuiCore$__Block_185_33) , __finiBlock___Block_185_33) ));
	urgc_set_field_class(__var___Block_185_33, (void * )offsetof(SuiCore$__Block_185_33, self) , self) ;
	URGC_VAR_CLEANUP_CLASS Orc$Thread*  t = (t=NULL,urgc_init_var_class((void**)&t, Orc$Thread_new(&t) ));
	URGC_VAR_CLEANUP SuiCore$__Closure_188_20*  tmpReturn_1 = NULL;
	urgc_set_field(t, (void * )offsetof(Orc$Thread, runFunc) , __make___Closure_188_20(&tmpReturn_1, __var___Block_185_33) ) ;
	t->start(t) ;
}



SuiCore$TimerMgr*  SuiCore$insTimerMgr(SuiCore$TimerMgr **  __outRef__){
	static URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  mgr = NULL;
	if (mgr == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&mgr, SuiCore$TimerMgr_new(&tmpNewOwner_1) ) ;
		printf("==========实例化TimerMgr:%p\n", mgr) ;
	}
	return urgc_set_var_for_return_class((void ** )__outRef__, mgr) ; 
}

SuiCore$Timer*  SuiCore$mkTimerTimeout(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond){
	URGC_REF_ARG_WITH_CLEANUP(fn);

	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  t = (t=NULL,urgc_init_var_class((void**)&t, SuiCore$Timer_new(&t) ));
	urgc_set_field(t, (void * )offsetof(SuiCore$Timer, runFunc) , fn) ;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	t->start(t) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, t) ; 
}

SuiCore$Timer*  SuiCore$mkTimerInterval(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond){
	URGC_REF_ARG_WITH_CLEANUP(fn);

	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  t = (t=NULL,urgc_init_var_class((void**)&t, SuiCore$Timer_new(&t) ));
	t->isInterval = true;
	urgc_set_field(t, (void * )offsetof(SuiCore$Timer, runFunc) , fn) ;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	t->start(t) ;
	return urgc_set_var_for_return_class((void ** )__outRef__, t) ; 
}

SuiCore$Timer*  SuiCore$mkTimerInterval_noStart(SuiCore$Timer **  __outRef__, void  (**fn)(void *  self), int  milliSecond){
	URGC_REF_ARG_WITH_CLEANUP(fn);

	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  t = (t=NULL,urgc_init_var_class((void**)&t, SuiCore$Timer_new(&t) ));
	t->isInterval = true;
	urgc_set_field(t, (void * )offsetof(SuiCore$Timer, runFunc) , fn) ;
	t->intervalMs = milliSecond;
	t->remainMs = milliSecond;
	return urgc_set_var_for_return_class((void ** )__outRef__, t) ; 
}

Orc$List *  SuiCore$gocAnimationFrameList(){
	static URGC_VAR_CLEANUP_CLASS Orc$List*  animationFrameList = NULL;
	if (animationFrameList == NULL) {
		URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&animationFrameList, Orc$List_new(&tmpNewOwner_1) ) ;
	}
	return animationFrameList; 
}

void  SuiCore$requestAnimationFrame(bool  (**fn)(void *  self)){
	URGC_REF_ARG_WITH_CLEANUP(fn);

	Orc$List *  lst = SuiCore$gocAnimationFrameList() ;
	lst->add(lst, (Object * )fn) ;
}

void  SuiCore$tickAnimationFrames(){
	Orc$List *  lst = SuiCore$gocAnimationFrameList() ;
	int  l = lst->size(lst) ;
	if (l > 0) {
		for (int  i = l - 1; i >= 0; i--) {
			URGC_VAR_CLEANUP bool  (**fn)(void *  self) = urgc_init_var((void**)&fn, (bool  (**)(void *  self))lst->get(lst, i) );
			bool  end = (*(fn))((void * )(fn)) ;
			if (end) {
				lst->removeAt(lst, i) ;
			}
		}
	}
}


//vtable instance
Vtable_SuiCore$AnimStep _vtable_SuiCore$AnimStep;

// init meta

void SuiCore$AnimStep_initMeta(Vtable_SuiCore$AnimStep *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "running", OrcMetaType_bool, offsetof(SuiCore$AnimStep, running), 0, 0, 0, 0);//bool
	orc_metaField_primitive(&pNext, "runningCnt", OrcMetaType_int, offsetof(SuiCore$AnimStep, runningCnt), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "elapsedMs", OrcMetaType_long_long, offsetof(SuiCore$AnimStep, elapsedMs), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "prevElapsedMs", OrcMetaType_long_long, offsetof(SuiCore$AnimStep, prevElapsedMs), 0, 0, 0, 0);//longlong
	orc_metaField_primitive(&pNext, "prevMs", OrcMetaType_long_long, offsetof(SuiCore$AnimStep, prevMs), 0, 0, 0, 0);//longlong

	orc_metaField_method(&pNext, "start", offsetof(SuiCore$AnimStep, start));
	orc_metaField_method(&pNext, "nextByMs", offsetof(SuiCore$AnimStep, nextByMs));
	orc_metaField_method(&pNext, "next", offsetof(SuiCore$AnimStep, next));
	orc_metaField_method(&pNext, "tick", offsetof(SuiCore$AnimStep, tick));
	orc_metaField_method(&pNext, "_start", offsetof(SuiCore$AnimStep, _start));
	orc_metaField_method(&pNext, "cancel", offsetof(SuiCore$AnimStep, cancel));
}


// vtable init


Vtable_SuiCore$AnimStep* Vtable_SuiCore$AnimStep_init(Vtable_SuiCore$AnimStep* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$AnimStep;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$AnimStep_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$AnimStep";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$AnimStep_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiCore$AnimStep_fini(SuiCore$AnimStep *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$AnimStep_init_fields(SuiCore$AnimStep *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$AnimStep_fini;
	//fields
    {
	urgc_set_field(self, (void**)&((SuiCore$AnimStep*)self)->update, NULL);
	((SuiCore$AnimStep*)self)->running = false;
	((SuiCore$AnimStep*)self)->runningCnt = 0;
	((SuiCore$AnimStep*)self)->elapsedMs = 0;
	((SuiCore$AnimStep*)self)->prevElapsedMs = 0;
	((SuiCore$AnimStep*)self)->prevMs = 0;
    }
	((SuiCore$AnimStep*)self)->start = (void*)SuiCore$AnimStep$start;
	((SuiCore$AnimStep*)self)->nextByMs = (void*)SuiCore$AnimStep$nextByMs;
	((SuiCore$AnimStep*)self)->next = (void*)SuiCore$AnimStep$next;
	((SuiCore$AnimStep*)self)->tick = (void*)SuiCore$AnimStep$tick;
	((SuiCore$AnimStep*)self)->_start = (void*)SuiCore$AnimStep$_start;
	((SuiCore$AnimStep*)self)->cancel = (void*)SuiCore$AnimStep$cancel;
}

// init function

void SuiCore$AnimStep_init(SuiCore$AnimStep *self, void *pOwner){
    Vtable_SuiCore$AnimStep_init(&_vtable_SuiCore$AnimStep);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$AnimStep;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$AnimStep_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$AnimStep * SuiCore$AnimStep_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$AnimStep *self = calloc(1, sizeof(SuiCore$AnimStep));
	
    SuiCore$AnimStep_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$AnimStep$start(SuiCore$AnimStep *  self, void  (**fn)(void *  self)){
	URGC_REF_ARG_WITH_CLEANUP(fn);

	urgc_set_field(self, (void * )offsetof(SuiCore$AnimStep, update) , fn) ;
	self->_start(self) ;
}


float  SuiCore$AnimStep$nextByMs(SuiCore$AnimStep *  self, float  x, float  to, float  ms){
	if (Orc$absFloat(x - to)  <= 0.0001) {
		return to; 
	}
	float  ratio = self->prevElapsedMs / ms;
	if (ratio >= 1.0) {
		return to; 
	}
	float  f = (x - to * ratio) / (1 - ratio);
	float  nowRatio = Orc$minFloat(1.0, self->elapsedMs / ms) ;
	float  nv = Orc$lerpFloat(f, to, nowRatio) ;
	if (nowRatio < 1.0) {
		self->runningCnt = self->runningCnt + 1;
	}
	return nv; 
}


float  SuiCore$AnimStep$next(SuiCore$AnimStep *  self, float  x, float  to, float  absStep){
	if (x == to) {
		return to; 
	}
	float  step = absStep * (to - x > 0 ? 1 : -1);
	float  nv = x + step;
	float  d0 = nv - to;
	float  d1 = to - x;
	float  m = d0 * d1;
	bool  isEnd = m >= 0;
	printf("\nx:%f, to:%f, step:%f, nv:%f, d0:%f, d1:%f, m:%f, isEnd:%d\n\n", x, to, step, nv, d0, d1, m, isEnd) ;
	if (isEnd) {
		nv = to;
	}
	else {
		self->runningCnt = self->runningCnt + 1;
	}
	return nv; 
}


void  SuiCore$AnimStep$tick(SuiCore$AnimStep *  self){
	long long  nowMs = Orc$Time_unixMs() ;
	long long  dMs = nowMs - self->prevMs;
	self->elapsedMs = self->prevElapsedMs + dMs;
	self->runningCnt = 0;
	if (self->update != NULL) {
		(*(self->update))((void * )(self->update)) ;
	}
	self->running = self->runningCnt > 0;
	self->prevElapsedMs = self->elapsedMs;
	self->prevMs = nowMs;
}


void  SuiCore$AnimStep$_start(SuiCore$AnimStep *  self){
	URGC_VAR_CLEANUP SuiCore$__Block_366_17*  __var___Block_366_17 = (__var___Block_366_17=NULL,urgc_init_var((void**)&__var___Block_366_17, orc_alloc_and_set_deleter(sizeof(SuiCore$__Block_366_17) , __finiBlock___Block_366_17) ));
	urgc_set_field_class(__var___Block_366_17, (void * )offsetof(SuiCore$__Block_366_17, self) , self) ;
	if (self->running) {
		return ; 
	}
	self->running = true;
	self->elapsedMs = 0;
	self->prevElapsedMs = 0;
	self->prevMs = Orc$Time_unixMs() ;
	URGC_VAR_CLEANUP SuiCore$__Closure_375_30*  tmpReturn_1 = NULL;
	SuiCore$requestAnimationFrame(__make___Closure_375_30(&tmpReturn_1, __var___Block_366_17) ) ;
}


void  SuiCore$AnimStep$cancel(SuiCore$AnimStep *  self){
	self->running = false;
}




//vtable instance
Vtable_SuiCore$TimerTestEnt _vtable_SuiCore$TimerTestEnt;

// init meta

void SuiCore$TimerTestEnt_initMeta(Vtable_SuiCore$TimerTestEnt *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "i", OrcMetaType_int, offsetof(SuiCore$TimerTestEnt, i), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiCore$TimerTestEnt* Vtable_SuiCore$TimerTestEnt_init(Vtable_SuiCore$TimerTestEnt* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiCore$TimerTestEnt;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiCore$TimerTestEnt_new;
    ((Vtable_Object*)pvt)->className = "SuiCore$TimerTestEnt";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiCore$TimerTestEnt_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiCore$TimerTestEnt_fini(SuiCore$TimerTestEnt *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放
	

}

// init fields function


void SuiCore$TimerTestEnt_init_fields(SuiCore$TimerTestEnt *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiCore$TimerTestEnt_fini;
	//fields
    {
	((SuiCore$TimerTestEnt*)self)->i = 1000;
    }
	((Object*)self)->dtor = (void*)SuiCore$TimerTestEnt$dtor;
}

// init function

void SuiCore$TimerTestEnt_init(SuiCore$TimerTestEnt *self, void *pOwner){
    Vtable_SuiCore$TimerTestEnt_init(&_vtable_SuiCore$TimerTestEnt);

    ((Object*)self)->vtable = (void*)&_vtable_SuiCore$TimerTestEnt;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiCore$TimerTestEnt_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiCore$TimerTestEnt * SuiCore$TimerTestEnt_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiCore$TimerTestEnt *self = calloc(1, sizeof(SuiCore$TimerTestEnt));
	
    SuiCore$TimerTestEnt_init(self, pOwner);
    return self;
}


// class members
void  SuiCore$TimerTestEnt$dtor(SuiCore$TimerTestEnt *  self){
	printf("释放TestEnt\n") ;
}



void  SuiCore$testTimer(){
	URGC_VAR_CLEANUP_CLASS SuiCore$TimerMgr*  mgr = SuiCore$insTimerMgr((mgr = NULL,&mgr)) ;
	mgr->startThreadTickAndFire(mgr) ;
	URGC_VAR_CLEANUP SuiCore$__Closure_397_30*  tmpReturn_1 = NULL;
	URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  t = SuiCore$mkTimerTimeout((t = NULL,&t), __make___Closure_397_30(&tmpReturn_1) , 5000) ;
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(t, (void * )offsetof(SuiCore$Timer, name) , Orc$str(&tmpReturn_2, "测试") ) ;
	{
		URGC_VAR_CLEANUP SuiCore$__Block_401_4*  __var___Block_401_4 = (__var___Block_401_4=NULL,urgc_init_var((void**)&__var___Block_401_4, orc_alloc_and_set_deleter(sizeof(SuiCore$__Block_401_4) , __finiBlock___Block_401_4) ));
		URGC_VAR_CLEANUP_CLASS SuiCore$TimerTestEnt*  tmpNewOwner_3 = NULL;
		urgc_set_field_class(__var___Block_401_4, (void * )offsetof(SuiCore$__Block_401_4, ent) , SuiCore$TimerTestEnt_new(&tmpNewOwner_3) ) ;
		URGC_VAR_CLEANUP_CLASS SuiCore$Timer*  tmpReturn_4 = NULL;
		URGC_VAR_CLEANUP SuiCore$__Closure_403_35*  tmpReturn_5 = NULL;
		urgc_set_field_class(__var___Block_401_4, (void * )offsetof(SuiCore$__Block_401_4, t) , SuiCore$mkTimerInterval(&tmpReturn_4, __make___Closure_403_35(&tmpReturn_5, __var___Block_401_4) , 1000) ) ;
	}
}

static void  __finiBlock___Block_169_26(SuiCore$__Block_169_26 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_169_26, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_185_33(SuiCore$__Block_185_33 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_185_33, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_366_17(SuiCore$__Block_366_17 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_366_17, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_401_4(SuiCore$__Block_401_4 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_401_4, ent) , NULL) ;
	urgc_set_field_class(self, (void * )offsetof(SuiCore$__Block_401_4, t) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __fn___Closure_172_20(SuiCore$__Closure_172_20 *  self){
	long long  prevMs = Orc$Time_unixMs() ;
	while (true) {
		Orc$Time_sleepMs(60) ;
		long long  nowMs = Orc$Time_unixMs() ;
		long long  elapsedMs = nowMs - prevMs;
		prevMs = nowMs;
		self->__var___Block_169_26->self->tick(self->__var___Block_169_26->self, (int )elapsedMs) ;
	}
}

static void  __fini___Closure_172_20(SuiCore$__Closure_172_20 *  self){
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_172_20, __var___Block_169_26) , NULL) ;
	urgc_free_later(self) ;
}

static SuiCore$__Closure_172_20*  __make___Closure_172_20(SuiCore$__Closure_172_20 **  __outRef__, SuiCore$__Block_169_26 *  __var___Block_169_26){
	URGC_VAR_CLEANUP SuiCore$__Closure_172_20*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_172_20) , __fini___Closure_172_20) ));
	self->invoke = __fn___Closure_172_20;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_172_20, __var___Block_169_26) , __var___Block_169_26) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_188_20(SuiCore$__Closure_188_20 *  self){
	long long  prevMs = Orc$Time_unixMs() ;
	while (true) {
		Orc$Time_sleepMs(16) ;
		long long  nowMs = Orc$Time_unixMs() ;
		long long  elapsedMs = nowMs - prevMs;
		prevMs = nowMs;
		self->__var___Block_185_33->self->tick(self->__var___Block_185_33->self, (int )elapsedMs) ;
		self->__var___Block_185_33->self->fire(self->__var___Block_185_33->self) ;
	}
}

static void  __fini___Closure_188_20(SuiCore$__Closure_188_20 *  self){
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_188_20, __var___Block_185_33) , NULL) ;
	urgc_free_later(self) ;
}

static SuiCore$__Closure_188_20*  __make___Closure_188_20(SuiCore$__Closure_188_20 **  __outRef__, SuiCore$__Block_185_33 *  __var___Block_185_33){
	URGC_VAR_CLEANUP SuiCore$__Closure_188_20*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_188_20) , __fini___Closure_188_20) ));
	self->invoke = __fn___Closure_188_20;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_188_20, __var___Block_185_33) , __var___Block_185_33) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static bool  __fn___Closure_375_30(SuiCore$__Closure_375_30 *  self){
	self->__var___Block_366_17->self->tick(self->__var___Block_366_17->self) ;
	return !self->__var___Block_366_17->self->running; 
}

static void  __fini___Closure_375_30(SuiCore$__Closure_375_30 *  self){
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_375_30, __var___Block_366_17) , NULL) ;
	urgc_free_later(self) ;
}

static SuiCore$__Closure_375_30*  __make___Closure_375_30(SuiCore$__Closure_375_30 **  __outRef__, SuiCore$__Block_366_17 *  __var___Block_366_17){
	URGC_VAR_CLEANUP SuiCore$__Closure_375_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_375_30) , __fini___Closure_375_30) ));
	self->invoke = __fn___Closure_375_30;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_375_30, __var___Block_366_17) , __var___Block_366_17) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_397_30(SuiCore$__Closure_397_30 *  self){
	printf("timeout after 5s\n") ;
}

static void  __fini___Closure_397_30(SuiCore$__Closure_397_30 *  self){
	urgc_free_later(self) ;
}

static SuiCore$__Closure_397_30*  __make___Closure_397_30(SuiCore$__Closure_397_30 **  __outRef__){
	URGC_VAR_CLEANUP SuiCore$__Closure_397_30*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_397_30) , __fini___Closure_397_30) ));
	self->invoke = __fn___Closure_397_30;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_403_35(SuiCore$__Closure_403_35 *  self){
	printf("interval i:%d, sec:%lld\n", self->__var___Block_401_4->ent->i, Orc$Time_unixSec() ) ;
	self->__var___Block_401_4->ent->i = self->__var___Block_401_4->ent->i + 1;
	if (self->__var___Block_401_4->ent->i > 1010) {
		self->__var___Block_401_4->t->cancel(self->__var___Block_401_4->t) ;
	}
}

static void  __fini___Closure_403_35(SuiCore$__Closure_403_35 *  self){
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_403_35, __var___Block_401_4) , NULL) ;
	urgc_free_later(self) ;
}

static SuiCore$__Closure_403_35*  __make___Closure_403_35(SuiCore$__Closure_403_35 **  __outRef__, SuiCore$__Block_401_4 *  __var___Block_401_4){
	URGC_VAR_CLEANUP SuiCore$__Closure_403_35*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiCore$__Closure_403_35) , __fini___Closure_403_35) ));
	self->invoke = __fn___Closure_403_35;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiCore$__Closure_403_35, __var___Block_401_4) , __var___Block_401_4) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



