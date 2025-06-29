#ifndef OKVECTOR4_H
#define OKVECTOR4_H

#include "HeaderManager.h"
#include <limits>

template<typename T>
class OKVector4
{
public: // PUBLIC VARIABLE(s)

	T x, y, z, w;

	OKVector4(T x = 0.f, T y = 0.f, T z = 0.f, T w = 0.f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	OKVector4(const OKVector4& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
	}

	OKVector4 zero()
	{
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
		this->w = 0.f;
	}

	OKVector4 one()
	{
		this->x = 1.f;
		this->y = 1.f;
		this->z = 1.f;
		this->w = 1.f;
	}

	OKVector4 inf()
	{
		this->x = std::numeric_limits<T>::infinity;
		this->y = std::numeric_limits<T>::infinity;
		this->z = std::numeric_limits<T>::infinity;
		this->w = std::numeric_limits<T>::infinity;
	}

public: // MATH FUNCTION(s)

	T dot(const OKVector4& value)
	{
		return T(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
	}

	OKVector4 normalise()
	{
		T t_Length = this->magnitude();
		return OKVector4(this->x / t_Length, this->y / t_Length, this->z / t_Length, this->w / t_Length);
	}

	T magnitude()
	{
		return T(sqrt(
		(this->x * this->x) +
		(this->y * this->y) +
		(this->z * this->z) + 
		(this->w * this->w)
		));
	}

	OKVector4 negate()
	{
		return OKVector4(1.f / this->x, 1.f / this->y, 1.f / this->z, 1.f / this->w);
	}

	OKVector4 pow(T value)
	{
		return OKVector4(powf(this->x, value), powf(this->y, value), powf(this->z, value), powf(this->w, value));
	}

	float* asArray()
	{
		return &this->x;
	}

	Vector4 ConvertToVec4()
	{
		Vector2 t_VecTemp{x, y, z, w};
		return t_VecTemp;
	}

public: // OPERATOR OVERLOAD FUNCTION(s)

	OKVector4 operator ++()
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}

	OKVector4 operator --()
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}

	OKVector4 operator -()
	{
		-x;
		-y;
		-z;
		-w;
		return *this;
	}

	OKVector4 operator =(const OKVector4& value)
	{
		this->x = value.x;
		this->y = value.y;
		this->z = value.z;
		this->w = value.w;
		return *this;
	}

	bool operator ==(const OKVector4& value)
	{
		bool s_CheckX = this->x == value.x ? true : false;
		bool s_CheckY = this->y == value.y ? true : false;
		bool s_CheckZ = this->z == value.z ? true : false;
		bool s_CheckW = this->w == value.w ? true : false;

		return (s_CheckX && s_CheckY && s_CheckZ && s_CheckW);
	}

	bool operator !=(const OKVector4& value)
	{
		bool s_CheckX = this->x != value.x ? true : false;
		bool s_CheckY = this->y != value.y ? true : false;
		bool s_CheckZ = this->z != value.z ? true : false;
		bool s_CheckW = this->w != value.w ? true : false;

		return (s_CheckX && s_CheckY && s_CheckZ && s_CheckW);
	}

	OKVector4 operator +(const OKVector4& value)
	{
		return OKVector4(this->x + value.x, this->y + value.y, this->z + value.z, this->w + value.w);
	}

	friend OKVector4 operator +(const T value, OKVector4<T> rhs)
	{
		return rhs + value;
	}

	OKVector4 operator -(const OKVector4& value)
	{
		return OKVector4(this->x - value.x, this->y - value.y, this->z - value.z, this->w - value.w);
	}

	friend OKVector4 operator -(const T value, OKVector4<T> rhs)
	{
		return rhs - value;
	}

	OKVector4 operator +=(const OKVector4& value)
	{
		return OKVector4(this->x += value.x, this->y += value.y, this->z += value.z, this->w += value.w);
	}

	OKVector4 operator -=(const OKVector4& value)
	{
		return OKVector4(this->x -= value.y, this->y -= value.y, this->z -= value.z, this->w -= value.w);
	}

	OKVector4 operator *(const OKVector4& value)
	{
		return OKVector4(this->x * value.x, this->y * value.y, this->z * value.z, this->w * value.w);
	}

	OKVector4 operator *(const T& value)
	{
		return OKVector4(this->x * value, this->y * value, this->z * value, this->w * value);
	}

	friend OKVector4 operator *(const T value, OKVector4<T> rhs)
	{
		return rhs * value;
	}

	OKVector4 operator /(const OKVector4& value)
	{
		return OKVector4(this->x / value.x, this->y / value.y, this->z / value.z, this->w / value.w);
	}

	OKVector4 operator /(const T& value)
	{
		return OKVector4(this->x / value, this->y / value, this->z / value, this->w / value);
	}

	friend OKVector4 operator /(const T value, OKVector4<T> rhs)
	{
		return rhs * value;
	}

	bool operator >(const OKVector4& value)
	{
		bool GreaterX = this->x > value.x ? true : false;
		bool GreaterY = this->y > value.y ? true : false;
		bool GreaterZ = this->z > value.z ? true : false;
		bool GreaterW = this->w > value.w ? true : false;

		return (GreaterX && GreaterY && GreaterZ && GreaterW);
	}

	bool operator >(const T& value)
	{
		bool GreaterX = this->x > value ? true : false;
		bool GreaterY = this->y > value ? true : false;
		bool GreaterZ = this->z > value ? true : false;
		bool GreaterW = this->w > value ? true : false;

		return (GreaterX && GreaterY && GreaterZ && GreaterW);
	}

	friend bool operator >(const T value, OKVector4<T> rhs)
	{
		bool GreaterX = rhs.x > value ? true : false;
		bool GreaterY = rhs.y > value ? true : false;
		bool GreaterZ = rhs.z > value ? true : false;
		bool GreaterW = rhs.w > value ? true : false;

		return (GreaterX && GreaterY && GreaterZ && GreaterW);
	}

	bool operator <(const OKVector4& value)
	{
		bool LessorX = this->x < value.x ? true : false;
		bool LessorY = this->y < value.y ? true : false;
		bool LessorZ = this->z < value.z ? true : false;
		bool LessorW = this->w < value.w ? true : false;

		return (LessorX && LessorY && LessorZ);
	}

	bool operator <(const T& value)
	{
		bool LessorX = this->x < value ? true : false;
		bool LessorY = this->y < value ? true : false;
		bool LessorZ = this->z < value ? true : false;
		bool LessorW = this->w < value ? true : false;

		return (LessorX && LessorY && LessorZ && LessorW);
	}

	friend bool operator <(const T value, OKVector4<T> rhs)
	{
		bool LessorX = rhs.x < value ? true : false;
		bool LessorY = rhs.y < value ? true : false;
		bool LessorZ = rhs.z < value ? true : false;
		bool LessorW = rhs.w < value ? true : false;

		return (LessorX && LessorY && LessorZ && LessorW);
	}

	bool operator >=(const OKVector4& value)
	{
		bool GreaterEqualX = this->x >= value.x ? true : false;
		bool GreaterEqualY = this->y >= value.y ? true : false;
		bool GreaterEqualZ = this->z >= value.z ? true : false;
		bool GreaterEqualW = this->w >= value.w ? true : false;

		return (GreaterEqualX && GreaterEqualY && GreaterEqualZ && GreaterEqualW);
	}

	bool operator <=(const OKVector4& value)
	{
		bool LessorEqualX = this->x <= value.x ? true : false;
		bool LessorEqualY = this->y <= value.y ? true : false;
		bool LessorEqualZ = this->z <= value.z ? true : false;
		bool LessorEqualW = this->z <= value.z ? true : false;

		return (LessorEqualX && LessorEqualY && LessorEqualZ && LessorEqualW);
	}

};

#define OKVECTOR4_ZERO {0.f, 0.f, 0.f, 0.f}
#define OKVECTOR4_ONE {1.f, 1.f, 1.f, 1.f}
#define OKVECTOR4_UP {0.f, 1.f, 0.f, 0.f}
#define OKVECTOR4_DOWN { 0.f, -1.f, 0.f, 0.f}
#define OKVECTOR4_RIGHT { 1.f, 0.f, 0.f, 0.f}
#define OKVECTOR4_LEFT { -1.f, 0.f, 0.f, 0.f}

#endif