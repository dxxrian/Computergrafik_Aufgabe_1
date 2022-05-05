#include "pch.h"
#include "Vector3.h"

Vector3::Vector3() {
	for (int i = 0; i < DIM; i++) {
		vek[i] = 0;
	}
	vek[DIM - 1] = 1;
}

Vector3::Vector3(double x, double y, double z) {
	vek[0] = x;
	vek[1] = y;
	vek[2] = z;
	vek[3] = 1;
}

void Vector3::setX(double x) {
	vek[0] = x;
}
void Vector3::setY(double x) {
	vek[1] = x;
}
void Vector3::setZ(double x) {
	vek[2] = x;
}

double Vector3::getX() {
	return vek[0];
}
double Vector3::getY() {
	return vek[1];
}
double Vector3::getZ() {
	return vek[2];
}

int Vector3::toPointX() {
	return 0;
}
int Vector3::toPointY() {
	return 0;
}

Vector3::~Vector3() {

}

Matrix3::Matrix3() {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			if (i == j) {
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}

}

Vector3 Matrix3::operator *(const Vector3& v) {
	Vector3 temp;
	for (int i = 0; i < DIM; i++) {
		temp.vek[i] = 0;
		for (int j = 0; j < DIM; j++) {
			temp.vek[i] += mat[i][j] * v.vek[j];
		}
	}
	return temp;
}

Matrix3::~Matrix3() {
}

void Matrix3::setTrans(double x, double y)
{
	mat[0][2] = x;
	mat[1][2] = y;
}

