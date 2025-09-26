package SuiCore

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//import * from "./Vec2.orc"



/// 矩形
class Radius {
	float tl = 0.f
	float tr = 0.f
	float bl = 0.f
	float br = 0.f
	void dtor(){
		printf("释放Radius:%f,%f,%f,%f\n", self.tl, self.tr, self.bl, self.br)
	}

    void setAll(float r){
		self.tl = r
		self.tr = r
		self.bl = r
		self.br = r
	}
}

void testRadius(){
	Radius@ a = new Radius()
	a.setAll(10.0f)
	printf("Radius: %f,%f,%f,%f\n",
		a.tl,
		a.tr,
		a.bl,
		a.br,
	)
}