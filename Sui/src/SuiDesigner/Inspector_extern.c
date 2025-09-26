

#include "./Inspector_orc.h"


// void SuiDesigner$Inspector$callCustom_onInspect(
//     SuiDesigner$Inspector * self
//     //, SuiCore$Node * parent
// )
// {
//     OrcMetaField *mf = orc_getMetaFieldByObject(self->obj, "onInspect");
//     if (mf){
//         int addr = OrcMetaField_getAddress(mf);
//         void (**onInspect)(Object *self, SuiDesigner$Inspector *parent) = (void*)  (((char*)self->obj) + addr);

//         (*onInspect)(self->obj, self);
//     }
// }