#include "Vector3D.h"

using namespace std;

Vector3D::Vector3D() = default;

[[maybe_unused]] Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

[[maybe_unused]] [[nodiscard]] string Vector3D::toString() const
{
	stringstream k("");
	k << "(" << this->x << ", " << this->y << ", " << this->z << ")" << endl;
	return k.str();
}

Vector3D Vector3D::operator+(const Vector3D &p) const
{
	return {this->x + p.x, this->y + p.y, this->z + p.z};
}

Vector3D Vector3D::operator+=(const Vector3D &p) const
{
	return (*this + p);
}

Vector3D Vector3D::operator-(const Vector3D &p) const
{
	return {this->x - p.x, this->y - p.y, this->z - p.z};
}

Vector3D Vector3D::operator-=(const Vector3D &p) const
{
	return (*this - p);
}

float Vector3D::operator*(const Vector3D &v) const
{
	return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3D Vector3D::operator*(const float &fac) const
{
	return {this->x * fac, this->y * fac, this->z * fac};
}

Vector3D Vector3D::operator/(const float &fac) const
{
	return {this->x / fac, this->y / fac, this->z / fac};
}

[[nodiscard]] Vector3D Vector3D::cross(const Vector3D &v) const
{
	return this->transform(
		0, -v.z, v.y,
		v.z, 0, -v.x,
		-v.y, v.x, 0
	) * -1;
}

[[nodiscard]] float Vector3D::angle(const Vector3D &v) const
{
	return acos(*this * v / (v.length() * length()));
}

[[nodiscard]] Vector3D Vector3D::transform(
	float m11, float m12, float m13,
	float m21, float m22, float m23,
	float m31, float m32, float m33
) const
{
	return {
		m11 * x + m12 * y + m13 * z,
		m21 * x + m22 * y + m23 * z,
		m31 * x + m32 * y + m33 * z
	};
}

[[nodiscard]] Vector3D Vector3D::rotate(float xx, float yy, float zz) const
{
	return transform(
		cos(yy) * cos(zz), sin(xx) * sin(yy) * cos(zz) - cos(xx) * sin(zz), cos(xx) * sin(yy) * cos(zz) + sin(xx) * sin(zz),
		cos(yy) * sin(zz), sin(xx) * sin(yy) * sin(zz) + cos(xx) * cos(zz), cos(xx) * sin(yy) * sin(zz) - sin(xx) * cos(zz),
		-sin(yy), sin(xx) * cos(yy), cos(xx) * cos(yy)
	);
}

[[nodiscard]] float Vector3D::length() const
{
	return (float) sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

[[maybe_unused]] [[nodiscard]] float Vector3D::dist(Vector3D v) const
{
	return (*this - v).length();
}

[[maybe_unused]] [[nodiscard]] Vector3D Vector3D::unit() const
{
	return *this / this->length();
}

ostream &operator<<(ostream &ss, const Vector3D &v)
{
	ss << "( " << v.x << ", " << v.y << ", " << v.z << ")";
	return ss;
}