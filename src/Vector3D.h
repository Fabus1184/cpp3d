#pragma once

#include <cmath>
#include <sstream>

class Vector3D
{
public:
	float x{}, y{}, z{};

	Vector3D();

	[[maybe_unused]] Vector3D(float x, float y, float z);

	[[maybe_unused]] [[nodiscard]] std::string toString() const;

	Vector3D operator+(const Vector3D &p) const;

	Vector3D operator+=(const Vector3D &p) const;

	Vector3D operator-(const Vector3D &p) const;

	Vector3D operator-=(const Vector3D &p) const;

	float operator*(const Vector3D &v) const;

	Vector3D operator*(const float &fac) const;

	Vector3D operator/(const float &fac) const;

	[[nodiscard]] Vector3D transform(
		float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33
	) const;

	[[nodiscard]] Vector3D cross(const Vector3D &v) const;

	[[nodiscard]] float angle(const Vector3D &v) const;

	[[nodiscard]] Vector3D rotate(float xx, float yy, float zz) const;

	[[nodiscard]] float length() const;

	[[maybe_unused]] [[nodiscard]] float dist(Vector3D v) const;

	[[maybe_unused]] [[nodiscard]] Vector3D unit() const;
};

std::ostream &operator<<(std::ostream &ss, const Vector3D &v);