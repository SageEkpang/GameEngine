#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "ComponentEntity.h"
#include "HeaderManager.h"
#include "OKVector2.h"

class TransformComponent : public ComponentEntity
{
public:

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;
	float m_Rotation;

public:

    // CLASS FUNCTION(s) (Components)
    TransformComponent(OKVector2<float> position, OKVector2<float> scale, float rotation);
    TransformComponent(float x, float y, float width, float height, float rotation);

    // CLASS FUNCTION(s) (General)
    TransformComponent();

    void Construct(OKVector2<float> position, OKVector2<float> scale, float rotation);
    void Construct(float x, float y, float width, float height, float rotation);

    ~TransformComponent();

    TransformComponent zero()
    {
        this->m_Position = OKVector2<float>(0.f, 0.f);
        this->m_Scale = OKVector2<float>(0.f, 0.f);
        this->m_Rotation = 0.f;
        return *this;
    }

    TransformComponent one()
    {
        this->m_Position = OKVector2<float>(1.f, 1.f);
        this->m_Scale = OKVector2<float>(1.f, 1.f);
        this->m_Rotation = 0.f;
        return *this;
    }
};

#endif