#include "CircleColliderComponent.h"

CircleColliderComponent::CircleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}

void CircleColliderComponent::Construct(OKVector2<float> position, float radius)
{
	m_Position = position;
	m_Radius = radius;
}

void CircleColliderComponent::Construct(float x, float y, float radius)
{
	m_Position = OKVector2<float>(x, y);
	m_Radius = radius;
}

CircleColliderComponent::~CircleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}