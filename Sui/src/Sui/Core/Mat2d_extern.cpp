
#include "./Mat2d_orc.h"
#include "../../nanovg/nanovg.h"


//使用nanovg,只处理二维
SuiCore$Mat2d SuiCore$mkMat2d() {
	SuiCore$Mat2d m;
	nvgTransformIdentity(m.data);
	return m;
}
//void SuiCore$Mat2d$ctor(SuiCore$Mat2d* self) {
//	nvgTransformIdentity(self->data);
//}
//void SuiCore$Mat2d$dtor(SuiCore$Mat2d* self) {
//	printf("释放矩阵\n");
//}
void SuiCore$Mat2d$identity(SuiCore$Mat2d* self) {
	nvgTransformIdentity(self->data);
}

void SuiCore$Mat2d$translate(SuiCore$Mat2d* self, float x, float y, float z) {
	float tmp[16] = { 0 };
	nvgTransformTranslate(tmp, x, y);
	nvgTransformPremultiply(self->data, tmp);
}
void SuiCore$Mat2d$scale(SuiCore$Mat2d* self, float x, float y, float z) {
	float tmp[16] = { 0 };
	nvgTransformScale(tmp, x, y);
	nvgTransformPremultiply(self->data, tmp);
}
void SuiCore$Mat2d$rotate(SuiCore$Mat2d* self, float x, float y, float z) {
	float tmp[16] = { 0 };
	nvgTransformRotate(tmp, z);
	nvgTransformPremultiply(self->data, tmp);
}
void SuiCore$Mat2d$multiply(SuiCore$Mat2d* self, SuiCore$Mat2d* b) {
	nvgTransformMultiply(self->data, b->data);
}
void SuiCore$Mat2d$premultiply(SuiCore$Mat2d* self, SuiCore$Mat2d* b) {
	nvgTransformPremultiply(self->data, b->data);
}
void SuiCore$Mat2d$inverse(SuiCore$Mat2d* self) {
	float data[16];
	nvgTransformInverse(data, self->data);
	memcpy(self->data, data, sizeof(*self));
}
SuiCore$Vec3 SuiCore$Mat2d$transformPoint(SuiCore$Mat2d* self, float x, float y, float z) {
	float dstx = 0.f;
	float dsty = 0.f;
	nvgTransformPoint(&dstx, &dsty, self->data, x, y);
	SuiCore$Vec3 p = SuiCore$mkVec3(dstx, dsty, 0.f);
	return p;
}



//SuiCore$Mat2d* SuiCore$Mat2d$copy(SuiCore$Mat2d** __outRef__, SuiCore$Mat2d* self) {
//	URGC_VAR_CLEANUP SuiCore$Mat2d* newins = (SuiCore$Mat2d*)urgc_init_var((void**) & newins, SuiCore$Mat2d_new());
//	memcpy(newins->data, self->data, sizeof(self->data));
//	 
//	return (SuiCore$Mat2d*)urgc_set_var_for_return((void**)__outRef__, newins);
//}
//extern "C" void testMat2d() {
//	URGC_VAR_CLEANUP SuiCore$Mat2d* m = (SuiCore$Mat2d*)urgc_init_var((void**)&m, SuiCore$Mat2d_new());
//	SuiCore$Mat2dPoint p = m->transformPoint(m, 10.f, 10.f, 0.f);
//	printf("应用变换:%f, %f\n", p.x, p.y);
//	m->translate(m, 10.f, 1.f, 0.f);
//	p = m->transformPoint(m, 10.f, 10.f, 0.f);
//	printf("应用变换:%f, %f\n", p.x, p.y);
//
//	m->scale(m, 3.f, 3.f, 1.f);
//	p = m->transformPoint(m, 10.f, 10.f, 0.f);
//	printf("应用变换:%f, %f\n", p.x, p.y);
//}