
#include "Theme_orc.h" 



// static struct 


// static function declaration



//vtable instance
Vtable_SuiDesigner$Theme _vtable_SuiDesigner$Theme;

// init meta

void SuiDesigner$Theme_initMeta(Vtable_SuiDesigner$Theme *pvt){
    OrcMetaField **pNext = &((Vtable_Object*)pvt)->headMetaField;//without super fields
	
	orc_metaField_primitive(&pNext, "colorLabel", OrcMetaType_int, offsetof(SuiDesigner$Theme, colorLabel), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "colorDesc", OrcMetaType_int, offsetof(SuiDesigner$Theme, colorDesc), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "c_main", OrcMetaType_int, offsetof(SuiDesigner$Theme, c_main), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "bg1", OrcMetaType_int, offsetof(SuiDesigner$Theme, bg1), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "bg2", OrcMetaType_int, offsetof(SuiDesigner$Theme, bg2), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "menubar_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, menubar_bg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "toolbar_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, toolbar_bg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "toolbar_menubutton_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, toolbar_menubutton_bg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "toolbar_menubutton_bg_hover", OrcMetaType_int, offsetof(SuiDesigner$Theme, toolbar_menubutton_bg_hover), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "splitLine_c1", OrcMetaType_int, offsetof(SuiDesigner$Theme, splitLine_c1), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "splitLine_c2", OrcMetaType_int, offsetof(SuiDesigner$Theme, splitLine_c2), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "fs1", OrcMetaType_int, offsetof(SuiDesigner$Theme, fs1), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "fs2", OrcMetaType_int, offsetof(SuiDesigner$Theme, fs2), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "fs3", OrcMetaType_int, offsetof(SuiDesigner$Theme, fs3), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "fs_h1", OrcMetaType_int, offsetof(SuiDesigner$Theme, fs_h1), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "fs_h2", OrcMetaType_int, offsetof(SuiDesigner$Theme, fs_h2), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dock_head_c", OrcMetaType_int, offsetof(SuiDesigner$Theme, dock_head_c), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dock_headbar_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, dock_headbar_bg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dock_head_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, dock_head_bg), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dock_head_bg_active", OrcMetaType_int, offsetof(SuiDesigner$Theme, dock_head_bg_active), 0, 0, 0, 0);//int
	orc_metaField_primitive(&pNext, "dock_content_bg", OrcMetaType_int, offsetof(SuiDesigner$Theme, dock_content_bg), 0, 0, 0, 0);//int

	
}


// vtable init


Vtable_SuiDesigner$Theme* Vtable_SuiDesigner$Theme_init(Vtable_SuiDesigner$Theme* pvt){
    if (pvt == NULL){
        pvt = &_vtable_SuiDesigner$Theme;
    }
    if (((Vtable_Object*)pvt)->inited){
        return pvt;
    }
	// init super vtable
    Vtable_Object_init(&_vtable_Object);

	// init by super vtable init function
    Vtable_Object_init((void*)pvt);

    ((Vtable_Object*)pvt)->super = (void*)&_vtable_Object;
    ((Vtable_Object*)pvt)->make = (void*)&SuiDesigner$Theme_new;
    ((Vtable_Object*)pvt)->className = "SuiDesigner$Theme";

    ((Vtable_Object*)pvt)->initMeta = (void*)SuiDesigner$Theme_initMeta;

    ((Vtable_Object*)pvt)->refc = 1;

    return pvt;
}


// fini function

void SuiDesigner$Theme_fini(SuiDesigner$Theme *self){
	//super fini
    Object_fini((Object *)self);

    //字段释放


}

// init fields function


void SuiDesigner$Theme_init_fields(SuiDesigner$Theme *self){
	//super class
    Object_init_fields((Object*)self);

    ((Object*)self)->fini = (void*)SuiDesigner$Theme_fini;
	//fields
    {
	((SuiDesigner$Theme*)self)->colorLabel = 0xff333333;
	((SuiDesigner$Theme*)self)->colorDesc = 0xff666666;
	((SuiDesigner$Theme*)self)->c_main = 0xff007aff;
	((SuiDesigner$Theme*)self)->bg1 = 0xffe5e5e5;
	((SuiDesigner$Theme*)self)->bg2 = 0xfff2f2f2;
	((SuiDesigner$Theme*)self)->menubar_bg = 0xff2c2c2e;
	((SuiDesigner$Theme*)self)->toolbar_bg = 0xffe5e5ea;
	((SuiDesigner$Theme*)self)->toolbar_menubutton_bg = 0x00000000;
	((SuiDesigner$Theme*)self)->toolbar_menubutton_bg_hover = 0x339c9c9c;
	((SuiDesigner$Theme*)self)->splitLine_c1 = 0xffd8d8d8;
	((SuiDesigner$Theme*)self)->splitLine_c2 = 0xffe5e5e5;
	((SuiDesigner$Theme*)self)->fs1 = 10;
	((SuiDesigner$Theme*)self)->fs2 = 12;
	((SuiDesigner$Theme*)self)->fs3 = 14;
	((SuiDesigner$Theme*)self)->fs_h1 = 16;
	((SuiDesigner$Theme*)self)->fs_h2 = 18;
	((SuiDesigner$Theme*)self)->dock_head_c = 0xff666666;
	((SuiDesigner$Theme*)self)->dock_headbar_bg = 0xffd1d1d6;
	((SuiDesigner$Theme*)self)->dock_head_bg = 0x00000030;
	((SuiDesigner$Theme*)self)->dock_head_bg_active = 0x99fafafa;
	((SuiDesigner$Theme*)self)->dock_content_bg = 0xe5e5e5;
    }
	
}

// init function

void SuiDesigner$Theme_init(SuiDesigner$Theme *self, void *pOwner){
    Vtable_SuiDesigner$Theme_init(&_vtable_SuiDesigner$Theme);

    ((Object*)self)->vtable = (void*)&_vtable_SuiDesigner$Theme;
	
	//has old object
	if (*((void**)pOwner) != NULL) urgc_deref_class(pOwner, *((void**)pOwner));
	*((void**)pOwner) = self;
	urgc_ref_class(pOwner, self, (void*)orc_delete);

    //urgc_guard(self, (void*)orc_delete);

    SuiDesigner$Theme_init_fields(self);

    if (((Object*)self)->ctor){
        ((Object*)self)->ctor((void*)self);
    }

    //urgc_deguard(self);
}

// new function
SuiDesigner$Theme * SuiDesigner$Theme_new(void *pOwner){
	if (pOwner == NULL){ return NULL;}
    SuiDesigner$Theme *self = calloc(1, sizeof(SuiDesigner$Theme));
	
    SuiDesigner$Theme_init(self, pOwner);
    return self;
}


// class members

static URGC_VAR_CLEANUP_CLASS SuiDesigner$Theme*  theme = NULL;
SuiDesigner$Theme *  SuiDesigner$themeIns(){
	if (theme == NULL) {
		URGC_VAR_CLEANUP_CLASS SuiDesigner$Theme*  tmpNewOwner_1 = NULL;
		urgc_set_var_class(&theme, SuiDesigner$Theme_new(&tmpNewOwner_1) ) ;
	}
	return theme; 
}



