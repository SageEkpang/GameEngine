#ifndef OK_TRANSFORM_H
#define OK_TRANSFORM_H

#include "HeaderManager.h"
#include "OKVector2.h"

template<class T>
class OKTransform2
{
public: // PUBLIC VARIABLE(s)

    OKVector2<T> position;
    OKVector2<T> rotation;
    OKVector2<T> scale;

    OKTransform2 zero()
    {
        this->position = OKVector2<T>(0.f, 0.f);
        this->rotation = OKVector2<T>(0.f, 0.f);
        this->scale = OKVector2<T>(0.f, 0.f);
        return *this;
    }

    OKTransform2 one()
    {
        this->position = OKVector2<T>(1.f, 1.f);
        this->rotation = OKVector2<T>(1.f, 1.f);
        this->scale = OKVector2<T>(1.f, 1.f);
        return *this;
    }

    OKTransform2 inf()
    {
        this->position = OKVector2<T>(std::numeric_limits<T>::infinity, std::numeric_limits<T>::infinity);
        this->rotation = OKVector2<T>(std::numeric_limits<T>::infinity, std::numeric_limits<T>::infinity);
        this->scale = OKVector2<T>(std::numeric_limits<T>::infinity, std::numeric_limits<T>::infinity);
        return *this;
    }

public: // MATH FUNCTION(s)


public: // OPERATOR OVERLOAD FUNCTION(s)

    OKTransform2() = default;
    OKTransform2(OKVector2<T> position, OKVector2<T> rotation, OKVector2<T> scale)
    {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

};

#endif

