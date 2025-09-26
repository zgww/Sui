
#include "TestMath_orc.h" 

#include <stdio.h>
#include "./Vec2_orc.h"
#include "./Vec3_orc.h"
#include "../../Orc/String_orc.h"
#include "../../Orc/Math_orc.h"
#include "./Mat3_orc.h"
#include "../../Sgl/Mat_orc.h"


// static struct 


// static function declaration


void  SuiCore$testMath(){
	SuiCore$testVec2() ;
	SuiCore$Vec2 tmpStructThis1;
	Orc$testOk(Orc$eqFloat(SuiCore$Vec2$length((tmpStructThis1 = SuiCore$mkVec2(3, 4) ,&tmpStructThis1)) , 5) , "length 3, 4 == 5") ;
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$setX(&t, 10) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.setX") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$setY(&t, 10) ;
		Orc$testOk(Orc$eqFloat(t.y, 10) , "Vec2.setY") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$setComponent(&t, 1, 11) ;
		Orc$testOk(Orc$eqFloat(t.y, 11) , "Vec2.setComponent") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 11) , "Vec2.getComponent") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$setComponent(&t, 0, 11) ;
		Orc$testOk(Orc$eqFloat(t.x, 11) , "Vec2.setComponent") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 0) , 11) , "Vec2.getComponent") ;
	}
	{
		SuiCore$Vec2 tmpStructThis2;
		SuiCore$Vec2 t = SuiCore$Vec2$clone((tmpStructThis2 = SuiCore$mkVec2(1, 2) ,&tmpStructThis2)) ;
		Orc$testOk(Orc$eqFloat(t.x, 1) , "Vec2.clone") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 2) , "Vec2.clone") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$addLocal(&t, SuiCore$mkVec2(10, 10) ) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.addLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 10) , "Vec2.addLocal") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$addScalarLocal(&t, 20) ;
		Orc$testOk(Orc$eqFloat(t.x, 20) , "Vec2.addScalarLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 20) , "Vec2.addScalarLocal") ;
	}
	{
		SuiCore$Mat3 m3;
		SuiCore$Mat3$translateLocal(SuiCore$Mat3$identity(&m3) , 10, 10) ;
		SuiCore$Vec2 t = SuiCore$mkVec2(0, 0) ;
		SuiCore$Vec2$applyMatrix3Local(&t, m3) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.applyMatrix3Local") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 10) , "Vec2.applyMatrix3Local") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(100, 200) ;
		SuiCore$Vec2$minLocal(&t, SuiCore$mkVec2(10, 150) ) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.minLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 150) , "Vec2.minLocal") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(10.123, -1.3) ;
		SuiCore$Vec2$floorLocal(&t) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.floorLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , -2) , "Vec2.floorLocal y") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(10.123, -1.3) ;
		SuiCore$Vec2$ceilLocal(&t) ;
		Orc$testOk(Orc$eqFloat(t.x, 11) , "Vec2.ceilLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , -1) , "Vec2.ceilLocal y") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(10.123, -1.6) ;
		SuiCore$Vec2$roundLocal(&t) ;
		Orc$testOk(Orc$eqFloat(t.x, 10) , "Vec2.roundLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , -2) , "Vec2.roundLocal y") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(10, -1) ;
		SuiCore$Vec2$negateLocal(&t) ;
		Orc$testOk(Orc$eqFloat(t.x, -10) , "Vec2.negateLocal") ;
		Orc$testOk(Orc$eqFloat(SuiCore$Vec2$getComponent(&t, 1) , 1) , "Vec2.negateLocal y") ;
	}
	{
		SuiCore$Vec2 t = SuiCore$mkVec2(1, 1) ;
		float  v = SuiCore$Vec2$angle(&t) ;
		Orc$testOk(Orc$eqFloat(v, 45 / 180.0 * Orc$PI) , "Vec2.angle") ;
	}
	{
		SuiCore$Vec2 tmpStructThis3;
		float  v = SuiCore$Vec2$distanceTo((tmpStructThis3 = SuiCore$mkVec2(1, 1) ,&tmpStructThis3), SuiCore$mkVec2(4, 5) ) ;
		Orc$testOk(Orc$eqFloat(v, 5) , "Vec2.distanceTo") ;
	}
	{
		SuiCore$Vec3 target = SuiCore$mkVec3(-500, -500, 0) ;
		SuiCore$Vec3 up = SuiCore$mkVec3(0, 1, 0) ;
		SuiCore$Vec3 eye = SuiCore$mkVec3(0, 0, 0) ;
		Sgl$Mat m;
		Sgl$Mat$lookAtFake(&m, eye, target, up) ;
		Sgl$Mat m2;
		Sgl$Mat$lookAtLocal(&m2, eye, target, up) ;
		printf("m") ;
	}
	Orc$PrintStyle tmpStructThis4;
	{
		Orc$PrintStyle *  o = Orc$PrintStyle$blue((tmpStructThis4 = Orc$mkPrintStyle() ,&tmpStructThis4)) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_120_4 = o->__exit__(o);
	
		printf("hi blue") ;
	}
	Orc$PrintStyle tmpStructThis5;
	{
		Orc$PrintStyle *  o = Orc$PrintStyle$bgwhite(Orc$PrintStyle$red((tmpStructThis5 = Orc$mkPrintStyle() ,&tmpStructThis5)) ) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_123_4 = o->__exit__(o);
	
		printf("hi red") ;
	}
	Orc$PrintStyle tmpStructThis6;
	{
		Orc$PrintStyle *  o = Orc$PrintStyle$green((tmpStructThis6 = Orc$mkPrintStyle() ,&tmpStructThis6)) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_126_4 = o->__exit__(o);
	
		printf("hi this is green") ;
	}
	Orc$PrintStyle tmpStructThis7;
	{
		Orc$PrintStyle *  o = Orc$PrintStyle$cyan((tmpStructThis7 = Orc$mkPrintStyle() ,&tmpStructThis7)) ;
		UNUSED DEFER(Orc_scopeExit) Orc$ScopeData __scopeObj_129_4 = o->__exit__(o);
	
		printf("hi this is cyan") ;
	}
	printf("reset color\n") ;
}



