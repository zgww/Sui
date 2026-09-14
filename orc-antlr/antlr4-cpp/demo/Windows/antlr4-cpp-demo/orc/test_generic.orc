package SuiCore

class Vtable_Object {
	Object@ create() { return null; }
}

T@ mkObj<T>(Vtable_Object<T>* vt) {
	T@ obj = vt.create();
	return obj;
}

extern T@ mkObjExtern<T>(Vtable_Object<T>* vt);
