#include "CircleColliderComponent.h"


CircleColliderComponent::CircleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}

CircleColliderComponent::CircleColliderComponent(OKVector2<float> offset, float radius)
{
	m_Offset = offset;
	m_Radius = radius;
}

CircleColliderComponent::CircleColliderComponent(float x, float y, float radius)
{
	m_Offset = OKVector2<float>(x, y);
	m_Radius = radius;
}

CircleColliderComponent::CircleColliderComponent(float radius)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = radius;
}

void CircleColliderComponent::Construct(OKVector2<float> offset, float radius)
{
	m_Offset = offset;
	m_Radius = radius;
}

void CircleColliderComponent::Construct(float x, float y, float radius)
{
	m_Offset = OKVector2<float>(x, y);
	m_Radius = radius;
}

void CircleColliderComponent::Construct(float radius)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = radius;
}

CircleColliderComponent::~CircleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}