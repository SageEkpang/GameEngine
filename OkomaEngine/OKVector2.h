#ifndef OKVECTOR2_H
#define OKVECTOR2_H

#include "HeaderManager.h"

template<class T>
class OKVector2
{
public: // PUBLIC VARIABLE(s)

    T x, y;

    OKVector2 zero()
    {
        this->x = 0;
        this->y = 0;
        return *this;
    }

    OKVector2 one()
    {
        this->x = 1;
        this->y = 1;
        return *this;
    }

    OKVector2 inf()
    {
        this->x = std::numeric_limits<T>::infinity;
        this->y = std::numeric_limits<T>::infinity;
        return *this;
    }

public: // MATH FUNCTION(s)

    T dot(const OKVector2& value)
    {
        return T(this->x * value.x + this->y * value.y);
    }

    OKVector2 normalise()
    {
        T t_Length = this->magnitude();
        return OKVector2(this->x / t_Length, this->y / t_Length);
    }

    T magnitude()
    {
        return T(sqrt((this->x * this->x) + (this->y * this->y)));
    }

    OKVector2 negate()
    {
        return OKVector2(-this->x, -this->y);
    }

    OKVector2 pow(T value)
    {
        return OKVector2(powf(this->x, value), powf(this->y, value));
    }

    float* asArray()
    {
        return &this->x;
    }

    Vector2 ConvertToVec2()
    {
        Vector2 t_VecTemp{ x, y };
        return t_VecTemp;
    }

public: // OPERATOR OVERLOAD FUNCTION(s)

    // BASE CONSTRUCTOR
    OKVector2(T x = 0.f, T y = 0.f)
    {
        this->x = x;
        this->y = y;
    }

    // OPERATOR OVERLOAD(s) (Arithmetic)
    OKVector2 operator ++()
    {
        ++x;
        ++y;
        return *this;
    }

    OKVector2 operator --()
    {
        --x;
        --y;
        return *this;
    }

    OKVector2 operator -()
    {
        -x;
        -y;
        return *this;
    }

    OKVector2 operator =(const OKVector2& value)
    {
        this->x = value.x;
        this->y = value.y;
        return *this;
    }

    bool operator ==(const OKVector2& value)
    {
        bool s_CheckX = this->x == value.x ? true : false;
        bool s_CheckY = this->y == value.y ? true : false;

        return (s_CheckX && s_CheckY);
    }

    OKVector2 operator +(const OKVector2& value)
    {
        return OKVector2(this->x + value.x, this->y + value.y);
    }

    OKVector2 operator -(const OKVector2& value)
    {
        return OKVector2(this->x - value.x, this->y - value.y);
    }

    friend OKVector2 operator -(const T value, OKVector2<T> rhs)
    {
        return rhs - value;
    }

    OKVector2 operator +=(const OKVector2& value)
    {
        return OKVector2(this->x += value.x, this->y += value.y);
    }

    OKVector2 operator -=(const OKVector2& value)
    {
        return OKVector2(this->x -= value.y, this->y -= value.y);
    }

    OKVector2 operator *(const OKVector2& value)
    {
        return OKVector2(this->x * value.x, this->y * value.y);
    }

    OKVector2 operator *(const T& value)
    {
        return OKVector2(this->x * value, this->y * value);
    }

    friend OKVector2 operator *(const T value, OKVector2<T> rhs)
    {
        return rhs * value;
    }

    OKVector2 operator /(const OKVector2& value)
    {
        return OKVector2(this->x / value.x, this->y / value.y);
    }

    OKVector2 operator /(const T& value)
    {

        return OKVector2(this->x / value, this->y / value);
    }

    friend OKVector2 operator /(const T value, OKVector2<T> rhs)
    {
        return rhs * value;
    }

    bool operator >(const OKVector2& value)
    {
        bool GreaterX = this->x > value.x ? true : false;
        bool GreaterY = this->y > value.y ? true : false;
        return (GreaterX && GreaterY);
    }

    bool operator >(const T& value)
    {
        bool GreaterX = this->x > value ? true : false;
        bool GreaterY = this->y > value ? true : false;
        return (GreaterX && GreaterY);
    }

    friend bool operator >(const T value, OKVector2<T> rhs)
    {
        bool GreaterX = rhs.x > value ? true : false;
        bool GreaterY = rhs.y > value ? true : false;
        return (GreaterX && GreaterY);
    }

    bool operator <(const OKVector2& value)
    {
        bool LessorX = this->x < value.x ? true : false;
        bool LessorY = this->y < value.y ? true : false;
        return (LessorX && LessorY);
    }

    bool operator <(const T& value)
    {
        bool LessorX = this->x < value ? true : false;
        bool LessorY = this->y < value ? true : false;
        return (LessorX && LessorY);
    }

    friend bool operator <(const T value, OKVector2<T> rhs)
    {
        bool LessorX = rhs.x < value ? true : false;
        bool LessorY = rhs.y < value ? true : false;
        return (LessorX && LessorY);
    }

    bool operator >=(const OKVector2& value)
    {
        bool GreaterEqualX = this->x >= value.x ? true : false;
        bool GreaterEqualY = this->y >= value.y ? true : false;

        return (GreaterEqualX && GreaterEqualY);
    }

    bool operator <=(const OKVector2& value)
    {
        bool LessorEqualX = this->x <= value.x ? true : false;
        bool LessorEqualY = this->y <= value.y ? true : false;

        return (LessorEqualX && LessorEqualY);
    }
};

#define OKVECTOR2_ZERO {0, 0}
#define OKVECTOR2_ONE {1, 1}
#define OKVECTOR2_UP {0, -1}
#define OKVECTOR2_DOWN {0, 1}
#define OKVECTOR2_RIGHT {1, 0}
#define OKVECTOR2_LEFT {-1, 0}

#endif

