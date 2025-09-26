
#include "FileChooser_orc.h" 

#include <stdio.h>
#include "../Sui/View/EditText_orc.h"
#include "../Sui/View/TextView_orc.h"
#include "../Sui/View/ImageView_orc.h"
#include "../Sui/View/Button_orc.h"
#include "../Sui/View/ScrollArea_orc.h"
#include "../Sui/View/HoverViewEffect_orc.h"
#include "../Sui/Core/Focus_orc.h"
#include "../Sui/Core/App_orc.h"
#include "../Sui/Core/Event_orc.h"
#include "../Sui/Core/MouseEvent_orc.h"
#include "../Sui/Core/Window_orc.h"
#include "../Sui/Core/View_orc.h"
#include "../Sui/Layout/LayoutLinear_orc.h"
#include "../Sui/Layout/RowWrap_orc.h"
#include "../Sui/Dialog/Toast_orc.h"
#include "../Orc/String_orc.h"
#include "../Orc/List_orc.h"
#include "../Orc/Map_orc.h"
#include "../Orc/Path_orc.h"


// static struct 
typedef struct tagSuiDesigner$__Block_80_16 SuiDesigner$__Block_80_16;

typedef struct tagSuiDesigner$__Block_110_61 SuiDesigner$__Block_110_61;

typedef struct tagSuiDesigner$__Closure_42_24 SuiDesigner$__Closure_42_24;

typedef struct tagSuiDesigner$__Closure_91_39 SuiDesigner$__Closure_91_39;

typedef struct tagSuiDesigner$__Closure_121_42 SuiDesigner$__Closure_121_42;



struct tagSuiDesigner$__Block_80_16 {
	SuiDesigner$FileChooser*  self ;
};





struct tagSuiDesigner$__Block_110_61 {
	Orc$String*  path ;
};





struct tagSuiDesigner$__Closure_42_24 {
	bool  (*invoke)(SuiDesigner$__Closure_42_24 *  self, Orc$String *  path);
	Vtable_Object *  vtable ;
};





struct tagSuiDesigner$__Closure_91_39 {
	void  (*invoke)(SuiDesigner$__Closure_91_39 *  self, SuiView$EditText *  et);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_80_16*  __var___Block_80_16 ;
};





struct tagSuiDesigner$__Closure_121_42 {
	void  (*invoke)(SuiDesigner$__Closure_121_42 *  self, SuiCore$Event *  e);
	Vtable_Object *  vtable ;
	SuiDesigner$__Block_80_16*  __var___Block_80_16 ;
	SuiDesigner$__Block_110_61*  __var___Block_110_61 ;
};





// static function declaration
static void  __finiBlock___Block_80_16(SuiDesigner$__Block_80_16 *  self);
static void  __finiBlock___Block_110_61(SuiDesigner$__Block_110_61 *  self);
static bool  __fn___Closure_42_24(SuiDesigner$__Closure_42_24 *  self, Orc$String *  path);
static void  __fini___Closure_42_24(SuiDesigner$__Closure_42_24 *  self);
static SuiDesigner$__Closure_42_24*  __make___Closure_42_24(SuiDesigner$__Closure_42_24 **  __outRef__);
static void  __fn___Closure_91_39(SuiDesigner$__Closure_91_39 *  self, SuiView$EditText *  et);
static void  __fini___Closure_91_39(SuiDesigner$__Closure_91_39 *  self);
static SuiDesigner$__Closure_91_39*  __make___Closure_91_39(SuiDesigner$__Closure_91_39 **  __outRef__, SuiDesigner$__Block_80_16 *  __var___Block_80_16);
static void  __fn___Closure_121_42(SuiDesigner$__Closure_121_42 *  self, SuiCore$Event *  e);
static void  __fini___Closure_121_42(SuiDesigner$__Closure_121_42 *  self);
static SuiDesigner$__Closure_121_42*  __make___Closure_121_42(SuiDesigner$__Closure_121_42 **  __outRef__, SuiDesigner$__Block_80_16 *  __var___Block_80_16, SuiDesigner$__Block_110_61 *  __var___Block_110_61);



//vtable instance
Vtable_SuiDesigner$FileChooser _vtable_SuiDesigner$FileChooser;

// init meta

void SuiDesigner$FileChooser_initMeta(Vtable_SuiDesigner$FileChooser *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_class(&pNext, "paths", ((Vtable_Object*)Vtable_Orc$List_init(0)), offsetof(SuiDesigner$FileChooser, paths), true, false, 1);
	orc_metaField_class(&pNext, "dir", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$FileChooser, dir), true, false, 1);
	orc_metaField_class(&pNext, "search", ((Vtable_Object*)Vtable_Orc$String_init(0)), offsetof(SuiDesigner$FileChooser, search), true, false, 1);
	orc_metaField_class(&pNext, "win", ((Vtable_Object*)Vtable_Sui$Window_init(0)), offsetof(SuiDesigner$FileChooser, win), true, false, 1);

	orc_metaField_method(&pNext, "fire_onChoose", offsetof(SuiDesigner$FileChooser, fire_onChoose));
	orc_metaField_method(&pNext, "use_filterImage", offsetof(SuiDesigner$FileChooser, use_filterImage));
	orc_metaField_method(&pNext, "loadPaths", offsetof(SuiDesigner$FileChooser, loadPaths));
	orc_metaField_method(&pNext, "doSearch", offsetof(SuiDesigner$FileChooser, doSearch));
	orc_metaField_method(&pNext, "matchSearch", offsetof(SuiDesigner$FileChooser, matchSearch));
	orc_metaField_method(&pNext, "react", offsetof(SuiDesigner$FileChooser, react));
	orc_metaField_method(&pNext, "showWindow", offsetof(SuiDesigner$FileChooser, showWindow));
}


// vtable init


Vtable_SuiDesigner$FileChooser* Vtable_SuiDesigner$FileChooser_init(Vtable_SuiDesigner$FileChooser* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$FileChooser;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$FileChooser_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$FileChooser";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$FileChooser_initMeta;

    ((Vtable_Object*)pvt)->refc = 0;

    return pvt;
}


// fini function

void SuiDesigner$FileChooser_fini(SuiDesigner$FileChooser *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$FileChooser_init_fields(SuiDesigner$FileChooser *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$FileChooser_fini;
	//fields
    {
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmpNewOwner_1 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileChooser*)self)->paths, Orc$List_new(&tmpNewOwner_1) );
	urgc_set_field(self, (void**)&((SuiDesigner$FileChooser*)self)->cbFilter, NULL);
	urgc_set_field(self, (void**)&((SuiDesigner$FileChooser*)self)->onChoose, NULL);
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_2 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileChooser*)self)->dir, Orc$str(&tmpReturn_2, ".") );
	URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileChooser*)self)->search, Orc$str(&tmpReturn_3, "") );
	urgc_set_field_class(self, (void**)&((SuiDesigner$FileChooser*)self)->win, NULL);
    }
	((SuiDesigner$FileChooser*)self)->fire_onChoose = (void*)SuiDesigner$FileChooser$fire_onChoose;
	((SuiDesigner$FileChooser*)self)->use_filterImage = (void*)SuiDesigner$FileChooser$use_filterImage;
	((SuiDesigner$FileChooser*)self)->loadPaths = (void*)SuiDesigner$FileChooser$loadPaths;
	((SuiDesigner$FileChooser*)self)->doSearch = (void*)SuiDesigner$FileChooser$doSearch;
	((SuiDesigner$FileChooser*)self)->matchSearch = (void*)SuiDesigner$FileChooser$matchSearch;
	((SuiDesigner$FileChooser*)self)->react = (void*)SuiDesigner$FileChooser$react;
	((SuiDesigner$FileChooser*)self)->showWindow = (void*)SuiDesigner$FileChooser$showWindow;
}

// init function

void SuiDesigner$FileChooser_init(SuiDesigner$FileChooser *self, void *pOwner){
    Vtable_SuiDesigner$FileChooser_init(&_vtable_SuiDesigner$FileChooser);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$FileChooser;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$FileChooser_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$FileChooser * SuiDesigner$FileChooser_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$FileChooser *self = calloc(1, sizeof(SuiDesigner$FileChooser));
	
    SuiDesigner$FileChooser_init(self, pOwner);
    return self;
}


// class members
void  SuiDesigner$FileChooser$fire_onChoose(SuiDesigner$FileChooser *  self, Orc$String*  path){
	URGC_REF_ARG_WITH_CLEANUP_CLASS(path);

	printf("FileChooser. onChoose:%s\n", path->str) ;
	if (self->onChoose) {
		(*(self->onChoose))((void * )(self->onChoose), path) ;
	}
}


void  SuiDesigner$FileChooser$use_filterImage(SuiDesigner$FileChooser *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_42_24*  tmpReturn_1 = NULL;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$FileChooser, cbFilter) , __make___Closure_42_24(&tmpReturn_1) ) ;
}


void  SuiDesigner$FileChooser$loadPaths(SuiDesigner$FileChooser *  self){
	URGC_VAR_CLEANUP_CLASS Orc$List*  tmp = (tmp=NULL,urgc_init_var_class((void**)&tmp, Orc$List_new(&tmp) ));
	Orc$Path_listSubtree_toList(self->dir->str, tmp) ;
	self->paths->clear(self->paths) ;
	for (int  i = 0; i < tmp->size(tmp) ; i++) {
		Orc$String *  path = (Orc$String * )tmp->get(tmp, i) ;
		printf("\tfilter path:%s\n", path->str) ;
		if (self->cbFilter) {
			if (!(*(self->cbFilter))((void * )(self->cbFilter), path) ) {
				continue;
			}
		}
		self->paths->add(self->paths, path) ;
	}
	printf("total path count:%d\n", self->paths->size(self->paths) ) ;
}


void  SuiDesigner$FileChooser$doSearch(SuiDesigner$FileChooser *  self){
	self->react(self) ;
}


bool  SuiDesigner$FileChooser$matchSearch(SuiDesigner$FileChooser *  self, Orc$String *  path){
	if (Orc$String$indexByteOf(path, self->search->str)  != -1) {
		return true; 
	}
	return false; 
}


void  SuiDesigner$FileChooser$react(SuiDesigner$FileChooser *  self){
	URGC_VAR_CLEANUP SuiDesigner$__Block_80_16*  __var___Block_80_16 = (__var___Block_80_16=NULL,urgc_init_var((void**)&__var___Block_80_16, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_80_16) , __finiBlock___Block_80_16) ));
	urgc_set_field_class(__var___Block_80_16, (void * )offsetof(SuiDesigner$__Block_80_16, self) , self) ;
	{
		SuiCore$ViewBase*  o = self->win->rootView;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_81_8 = ((SuiCore$Node*)o)->__exit__((void*)o);
	
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_1 = NULL;
		{
			SuiLayout$LayoutLinear*  __scopeVar_82_12 = SuiLayout$layoutLinear(&tmpReturn_1, o, 0) , *o = __scopeVar_82_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_82_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			SuiCore$Inset$setVer(&((SuiCore$View * )o)->margin, 6) ;
			URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_2 = NULL;
			{
				SuiView$TextView*  __scopeVar_84_16 = SuiView$mkTextView(&tmpReturn_2, o, 0) , *o = __scopeVar_84_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_84_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				URGC_VAR_CLEANUP_CLASS Orc$String*  tmpReturn_3 = NULL;
				o->setText(o, Orc$str(&tmpReturn_3, "文件选择器") ) ;
			}
			URGC_VAR_CLEANUP_CLASS SuiView$EditText*  tmpReturn_4 = NULL;
			{
				SuiView$EditText*  __scopeVar_87_16 = SuiView$mkEditText(&tmpReturn_4, o, 0) , *o = __scopeVar_87_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_87_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				SuiCore$Focus *  tmpThis_1 = NULL;
				if (!(tmpThis_1 = SuiCore$insFocus() )->isFocus(tmpThis_1, o) ) {
					o->setValue(o, self->search) ;
				}
				URGC_VAR_CLEANUP SuiDesigner$__Closure_91_39*  tmpReturn_5 = NULL;
				urgc_set_field(o, (void * )offsetof(SuiView$EditText, onValueChanged) , __make___Closure_91_39(&tmpReturn_5, __var___Block_80_16) ) ;
				URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_6 = NULL;
				SuiLayout$layoutLinearCell(&tmpReturn_6, o, 0) ;
			}
		}
		URGC_VAR_CLEANUP_CLASS SuiView$ScrollArea*  tmpReturn_7 = NULL;
		{
			SuiView$ScrollArea*  __scopeVar_100_12 = SuiView$mkScrollArea(&tmpReturn_7, o, 0) , *o = __scopeVar_100_12;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_100_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			o->useMaxWidthConstraint = true;
			o->useMinWidthConstraint = true;
			URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinearCell*  tmpReturn_8 = NULL;
			SuiLayout$layoutLinearCell(&tmpReturn_8, o, 0) ;
			URGC_VAR_CLEANUP_CLASS SuiLayout$RowWrap*  tmpReturn_9 = NULL;
			{
				SuiLayout$RowWrap*  __scopeVar_105_16 = SuiLayout$mkRowWrap(&tmpReturn_9, o, 0) , *o = __scopeVar_105_16;
				UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_105_16 = ((SuiCore$Node*)o)->__exit__((void*)o);
			
				o->rowGap = 10;
				o->colGap = 10;
				for (int  i = 0; i < self->paths->size(self->paths) ; i++) {
					URGC_VAR_CLEANUP SuiDesigner$__Block_110_61*  __var___Block_110_61 = (__var___Block_110_61=NULL,urgc_init_var((void**)&__var___Block_110_61, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Block_110_61) , __finiBlock___Block_110_61) ));
					urgc_set_field_class(__var___Block_110_61, (void * )offsetof(SuiDesigner$__Block_110_61, path) , (Orc$String* )self->paths->get(self->paths, i) ) ;
					if (!self->matchSearch(self, __var___Block_110_61->path) ) {
						continue;
					}
					URGC_VAR_CLEANUP_CLASS Orc$String*  filename = Orc$Path_basename((filename = NULL,&filename), __var___Block_110_61->path->str) ;
					URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpReturn_10 = NULL;
					{
						SuiLayout$LayoutLinear*  __scopeVar_117_24 = SuiLayout$layoutLinear(&tmpReturn_10, o, 100000 + i) , *o = __scopeVar_117_24;
						UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_117_24 = ((SuiCore$Node*)o)->__exit__((void*)o);
					
						Orc$String$set(o->direction, "column") ;
						Orc$String$set(o->alignItems, "stretch") ;
						URGC_VAR_CLEANUP SuiDesigner$__Closure_121_42*  tmpReturn_11 = NULL;
						urgc_set_field(o, (void * )offsetof(SuiCore$Emitter, cbOnEvent) , __make___Closure_121_42(&tmpReturn_11, __var___Block_80_16, __var___Block_110_61) ) ;
						URGC_VAR_CLEANUP_CLASS SuiView$ImageView*  tmpReturn_12 = NULL;
						{
							SuiView$ImageView*  __scopeVar_131_28 = SuiView$mkImageView(&tmpReturn_12, o, 10000000 + i) , *o = __scopeVar_131_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_131_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							((SuiCore$View * )o)->width = 60;
							((SuiCore$View * )o)->height = 60;
							o->setImageMode(o, SuiView$Fill) ;
							o->setSrc(o, __var___Block_110_61->path) ;
							Orc$String$set(((SuiCore$ViewBase * )o)->cursor, "pointer") ;
							URGC_VAR_CLEANUP_CLASS SuiView$HoverViewEffect*  tmpReturn_13 = NULL;
							{
								SuiView$HoverViewEffect*  __scopeVar_143_32 = SuiView$mkHoverViewEffect(&tmpReturn_13, o, 0) , *o = __scopeVar_143_32;
								UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_143_32 = ((SuiCore$Node*)o)->__exit__((void*)o);
							
								o->hoverBackgroundColor = 0x2200ffff;
								o->backgroundColor = 0x1100ffff;
							}
						}
						URGC_VAR_CLEANUP_CLASS SuiView$TextView*  tmpReturn_14 = NULL;
						{
							SuiView$TextView*  __scopeVar_148_28 = SuiView$mkTextView(&tmpReturn_14, o, 0) , *o = __scopeVar_148_28;
							UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_148_28 = ((SuiCore$Node*)o)->__exit__((void*)o);
						
							o->setFont_size(o, 10) ;
							o->setText(o, filename) ;
						}
					}
				}
			}
		}
	}
}


void  SuiDesigner$FileChooser$showWindow(SuiDesigner$FileChooser *  self){
	URGC_VAR_CLEANUP_CLASS Sui$Window*  tmpNewOwner_1 = NULL;
	{
		Sui$Window*  o = Sui$Window_new(&tmpNewOwner_1) ;
		
	
		Sui$Window *  win = o;
		urgc_set_field_class(self, (void * )offsetof(SuiDesigner$FileChooser, win) , o) ;
		URGC_VAR_CLEANUP_CLASS SuiLayout$LayoutLinear*  tmpNewOwner_2 = NULL;
		{
			SuiLayout$LayoutLinear*  o = SuiLayout$LayoutLinear_new(&tmpNewOwner_2) ;
			UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_165_12 = ((SuiCore$Node*)o)->__exit__((void*)o);
		
			Orc$String$set(o->direction, "column") ;
			Orc$String$set(o->alignItems, "stretch") ;
			SuiCore$Inset$setAll(&((SuiCore$View * )o)->padding, 8) ;
			win->setRootView(win, o) ;
		}
		self->react(self) ;
		o->setTitle(o, "文件选择") ;
		o->setSize(o, 300, 300) ;
		o->moveToCenter(o) ;
		o->show(o) ;
	}
}



static void  __finiBlock___Block_80_16(SuiDesigner$__Block_80_16 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_80_16, self) , NULL) ;
	return urgc_free_later(self) ; 
}

static void  __finiBlock___Block_110_61(SuiDesigner$__Block_110_61 *  self){
	urgc_set_field_class(self, (void * )offsetof(SuiDesigner$__Block_110_61, path) , NULL) ;
	return urgc_free_later(self) ; 
}

static bool  __fn___Closure_42_24(SuiDesigner$__Closure_42_24 *  self, Orc$String *  path){
	if (Orc$Path_isUsualImage(path->str) ) {
		return true; 
	}
	return false; 
}

static void  __fini___Closure_42_24(SuiDesigner$__Closure_42_24 *  self){
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_42_24*  __make___Closure_42_24(SuiDesigner$__Closure_42_24 **  __outRef__){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_42_24*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_42_24) , __fini___Closure_42_24) ));
	self->invoke = __fn___Closure_42_24;
	self->vtable = orc_Vtable_Closure_init() ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_91_39(SuiDesigner$__Closure_91_39 *  self, SuiView$EditText *  et){
	urgc_set_field_class(self->__var___Block_80_16->self, (void * )offsetof(SuiDesigner$FileChooser, search) , et->getValue(et) ) ;
	printf("on CHanged:%s\n", self->__var___Block_80_16->self->search->str) ;
	self->__var___Block_80_16->self->doSearch(self->__var___Block_80_16->self) ;
}

static void  __fini___Closure_91_39(SuiDesigner$__Closure_91_39 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_91_39, __var___Block_80_16) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_91_39*  __make___Closure_91_39(SuiDesigner$__Closure_91_39 **  __outRef__, SuiDesigner$__Block_80_16 *  __var___Block_80_16){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_91_39*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_91_39) , __fini___Closure_91_39) ));
	self->invoke = __fn___Closure_91_39;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_91_39, __var___Block_80_16) , __var___Block_80_16) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}

static void  __fn___Closure_121_42(SuiDesigner$__Closure_121_42 *  self, SuiCore$Event *  e){
	if (Orc_instanceof((Object*)e, (Vtable_Object*)Vtable_SuiCore$MouseEvent_init(NULL))) {
		SuiCore$MouseEvent *  me = (SuiCore$MouseEvent * )e;
		if (me->button == 1 && me->isClickInBubble(me) ) {
			self->__var___Block_80_16->self->fire_onChoose(self->__var___Block_80_16->self, self->__var___Block_110_61->path) ;
		}
	}
}

static void  __fini___Closure_121_42(SuiDesigner$__Closure_121_42 *  self){
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_121_42, __var___Block_80_16) , NULL) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_121_42, __var___Block_110_61) , NULL) ;
	urgc_free_later(self) ;
}

static SuiDesigner$__Closure_121_42*  __make___Closure_121_42(SuiDesigner$__Closure_121_42 **  __outRef__, SuiDesigner$__Block_80_16 *  __var___Block_80_16, SuiDesigner$__Block_110_61 *  __var___Block_110_61){
	URGC_VAR_CLEANUP SuiDesigner$__Closure_121_42*  self = (self=NULL,urgc_init_var((void**)&self, orc_alloc_and_set_deleter(sizeof(SuiDesigner$__Closure_121_42) , __fini___Closure_121_42) ));
	self->invoke = __fn___Closure_121_42;
	self->vtable = orc_Vtable_Closure_init() ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_121_42, __var___Block_80_16) , __var___Block_80_16) ;
	urgc_set_field(self, (void * )offsetof(SuiDesigner$__Closure_121_42, __var___Block_110_61) , __var___Block_110_61) ;
	return urgc_set_var_for_return((void ** )__outRef__, self) ; 
}



