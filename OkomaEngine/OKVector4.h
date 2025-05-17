#ifndef OKVECTER4_H
#define OKVECTOR4_H

#include "HeaderManager.h"

template<class T>
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









};

#define OKVECTOR4_ZERO {0.f, 0.f}
#define OKVECTOR4_ONE {1.f, 1.f}
#define OKVECTOR4_UP {0.f, 1.f}
#define OKVECTOR4_DOWN { 0.f, -1.f}
#define OKVECTOR4_RIGHT { 1.f, 0.f}
#define OKVECTOR4_LEFT { -1.f, 0.f}

#endif