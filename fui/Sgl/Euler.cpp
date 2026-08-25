
module Sgl;



Euler* Euler::setFromQuaternion(Quaternion& q, const char* order) {
	Mat _matrix;

	_matrix.makeRotationFromQuaternion(q);

	return this->setFromRotationMatrix(_matrix, order);

}



Euler* Euler::reorder(const char* newOrder) {
	// WARNING: this discards revolution information -bhouston
	Quaternion q;
	q.setFromEuler(*this);
	return this->setFromQuaternion(q, newOrder);
}
