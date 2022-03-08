#include <math.h>
#include <cmath>

using namespace std;

class Point3D{

private:

	double x,y,z;

public:

	double X(){return this->x;}
	double Y(){return this->y;}
	double Z(){return this->z;}

	Point3D(){
		this->x = nan("");
		this->y = nan("");
		this->z = nan("");
	}

	Point3D(double x, double y, double z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Point3D operator + (const Point3D & p) const {
		return Point3D(this->x + p.x, this->y + p.y, this->z + p.z);
	}

	Point3D operator += (const Point3D & p) const {
		return (*this + p);
	}

	Point3D operator - (const Point3D & p) const {
		return Point3D(this->x - p.x, this->y - p.y, this->z - p.z);
	}

	Point3D operator -= (const Point3D & p) const {
		return (*this - p);
	}


	Point3D operator * (const double & fac) const {
		return Point3D(this->x * fac, this->y * fac, this->z * fac);
	}

	Point3D transform(
		double m11, double m12, double m13,
		double m21, double m22, double m23,
		double m31, double m32, double m33
	){
		return Point3D(
			m11 * x + m12 * y + m13 * z,
			m21 * x + m22 * y + m23 * z,
			m31 * x + m32 * y + m33 * z
		);
	}

	Point3D rotate(double x, double y, double z){
		return transform(
			cos(y) * cos(z), sin(x) * sin(y) * cos(z) - cos(x) * sin(z), cos(x) * sin(y) * cos(z) + sin(x) * sin(z),
			cos(y) * sin(z), sin(x) * sin(y) * sin(z) + cos(x) * cos(z), cos(x) * sin(y) * sin(z) - sin(x) * cos(z),
			-sin(y), sin(x) * cos(y), cos(x) * cos(y)	
		);
	}

};
