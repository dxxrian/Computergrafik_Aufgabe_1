#pragma once
#define DIM 4
class Vector3
{
public:
	double vek[DIM];
	Vector3();
	Vector3(double x, double y, double z);
	~Vector3();
	int toPointX();
	int toPointY();
	void setX(double);
	void setZ(double);
	void setY(double);
	double getX();
	double getY();
	double getZ();
};

class Matrix3
{
	double mat[DIM][DIM];
public:
	Matrix3();
	Vector3 operator *(const Vector3& v);
	~Matrix3();
	void setTrans(double x, double y);
};

