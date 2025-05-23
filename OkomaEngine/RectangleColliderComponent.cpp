#include "RectangleColliderComponent.h"

RectangleColliderComponent::RectangleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
}

void RectangleColliderComponent::Construct(OKVector2<float> position, OKVector2<float> scale)
{
	m_Position = position;
	m_Scale = scale;
}

void RectangleColliderComponent::Construct(OKVector2<float> position, float width, float height)
{
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
}

void RectangleColliderComponent::Construct(float x, float y, OKVector2<float> scale)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
}

void RectangleColliderComponent::Construct(float x, float y, float width, float height)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
}

RectangleColliderComponent::~RectangleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
}
