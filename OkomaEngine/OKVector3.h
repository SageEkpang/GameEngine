#ifndef OKVECTOR3_H
#define OKVECTOR3_H

#include "HeaderManager.h"

template<class T>
class OKVector3
{
public: // PUBLIC VARIABLE(s)

	T x, y, z;

	OKVector3 zero()
	{
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
		return *this;
	}

	OKVector3 one()
	{
		this->x = 1.f;
		this->y = 1.f;
		this->z = 1.f;
		return *this;
	}

	OKVector3 inf()
	{
		this->x = std::numeric_limits<T>::infinity;
		this->y = std::numeric_limits<T>::infinity;
		this->z = std::numeric_limits<T>::infinity;
		return *this;
	}

public: // MATH FUNCTION(s)

    T dot(const OKVector3& value)
    {
        return T(this->x * value.x + this->y * value.y + this->z * value.z);
    }

    OKVector3 normalise()
    {
        T t_Length = this->magnitude();
        return OKVector3(this->x / t_Length, this->y / t_Length, this->z / t_Length);
    }

    T magnitude()
    {
        return T(sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z)));
    }

    OKVector3 negate()
    {
        return OKVector3(1.f / this->x, 1.f / this->y, 1.f / this->z);
    }

    OKVector3 pow(T value)
    {
        return OKVector3(powf(this->x, value), powf(this->y, value), powf(this->z, value));
    }

    float* asArray()
    {
        return &this->x;
    }

    Vector3 ConvertToVec3()
    {
        Vector3 t_VecTemp{ x, y, z };
        return t_VecTemp;
    }

public: // OPERATOR OVERLOAD FUNCTION(s)

    OKVector3(T x = 0.f, T y = 0.f, T z = 0.f)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    OKVector3 operator ++()
    {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    OKVector3 operator --()
    {
        --x;
        --y;
        --z;
        return *this;
    }

    OKVector3 operator -()
    {
        -x;
        -y;
        -z;
        return *this;
    }

    OKVector3 operator =(const OKVector3& value)
    {
        this->x = value.x;
        this->y = value.y;
        this->z = value.z;
        return *this;
    }

    OKVector3 operator ==(const OKVector3& value)
    {
        bool s_CheckX = this->x == value.x ? true : false;
        bool s_CheckY = this->y == value.y ? true : false;
        bool s_CheckZ = this->y == value.z ? true : false;

        return (s_CheckX && s_CheckY && s_CheckZ);
    }

    OKVector3 operator !=(const OKVector3& value)
    {
        bool s_CheckX = this->x != value.x ? true : false;
        bool s_CheckY = this->y != value.y ? true : false;
        bool s_CheckZ = this->y != value.z ? true : false;

        return (s_CheckX && s_CheckY && s_CheckZ);
    }

    OKVector3 operator +(const OKVector3& value)
    {
        return OKVector3(this->x + value.x, this->y + value.y, this->z + value.z);
    }

    OKVector3 operator -(const OKVector3& value)
    {
        return OKVector3(this->x - value.x, this->y - value.y, this->z - value.z);
    }

    friend OKVector3 operator -(const T value, OKVector3<T> rhs)
    {
        return rhs - value;
    }

    OKVector3 operator +=(const OKVector3& value)
    {
        return OKVector3(this->x += value.x, this->y += value.y, this->z += value.z);
    }

    OKVector3 operator -=(const OKVector3& value)
    {
        return OKVector3(this->x -= value.y, this->y -= value.y, this->z -= value.z);
    }

    OKVector3 operator *(const OKVector3& value)
    {
        return OKVector3(this->x * value.x, this->y * value.y, this->z * value.z);
    }

    OKVector3 operator *(const T& value)
    {
        return OKVector3(this->x * value, this->y * value, this->z * value);
    }

    friend OKVector3 operator *(const T value, OKVector3<T> rhs)
    {
        return rhs * value;
    }

    OKVector3 operator /(const OKVector3& value)
    {
        return OKVector3(this->x / value.x, this->y / value.y, this->z / value.z);
    }

    OKVector3 operator /(const T& value)
    {
        return OKVector3(this->x / value, this->y / value, this->z / value);
    }

    friend OKVector3 operator /(const T value, OKVector3<T> rhs)
    {
        return rhs * value;
    }

    bool operator >(const OKVector3& value)
    {
        bool GreaterX = this->x > value.x ? true : false;
        bool GreaterY = this->y > value.y ? true : false;
        bool GreaterZ = this->z > value.z ? true : false;
        return (GreaterX && GreaterY && GreaterZ);
    }

    bool operator >(const T& value)
    {
        bool GreaterX = this->x > value ? true : false;
        bool GreaterY = this->y > value ? true : false;
        bool GreaterZ = this->z > value ? true : false;
        return (GreaterX && GreaterY && GreaterZ);
    }

    friend bool operator >(const T value, OKVector3<T> rhs)
    {
        bool GreaterX = rhs.x > value ? true : false;
        bool GreaterY = rhs.y > value ? true : false;
        bool GreaterZ = rhs.z > value ? true : false;
        return (GreaterX && GreaterY && GreaterZ);
    }

    bool operator <(const OKVector3& value)
    {
        bool LessorX = this->x < value.x ? true : false;
        bool LessorY = this->y < value.y ? true : false;
        bool LessorZ = this->z < value.z ? true : false;
        return (LessorX && LessorY && LessorZ);
    }

    bool operator <(const T& value)
    {
        bool LessorX = this->x < value ? true : false;
        bool LessorY = this->y < value ? true : false;
        bool LessorZ = this->z < value ? true : false;
        return (LessorX && LessorY && LessorZ);
    }

    friend bool operator <(const T value, OKVector3<T> rhs)
    {
        bool LessorX = rhs.x < value ? true : false;
        bool LessorY = rhs.y < value ? true : false;
        bool LessorZ = rhs.z < value ? true : false;
        return (LessorX && LessorY && LessorZ);
    }

    bool operator >=(const OKVector3& value)
    {
        bool GreaterEqualX = this->x >= value.x ? true : false;
        bool GreaterEqualY = this->y >= value.y ? true : false;
        bool GreaterEqualZ = this->z >= value.z ? true : false;

        return (GreaterEqualX && GreaterEqualY && GreaterEqualZ);
    }

    bool operator <=(const OKVector3& value)
    {
        bool LessorEqualX = this->x <= value.x ? true : false;
        bool LessorEqualY = this->y <= value.y ? true : false;
        bool LessorEqualZ = this->z <= value.z ? true : false;

        return (LessorEqualX && LessorEqualY && LessorEqualZ);
    }

};

#define OKVECTOR3_ZERO {0.f, 0.f, 0.f}
#define OKVECTOR3_ONE {1.f, 1.f, 1.f}
#define OKVECTOR3_UP {0.f, -1.f, 0.f}
#define OKVECTOR3_DOWN {0.f, 1.f, 0.f}
#define OKVECTOR3_RIGHT {1.f, 0.f, 0.f}
#define OKVECTOR3_LEFT {-1.f, 0.f, 0.f}

#endif