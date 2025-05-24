#include "PointColliderComponent.h"

PointColliderComponent::PointColliderComponent(OKVector2<float> position, float radius)
{
	m_Position = position;
	m_Radius = radius;
}

PointColliderComponent::PointColliderComponent(float x, float y, float radius)
{
	m_Position = OKVector2<float>(x, y);
	m_Radius = radius;
}

PointColliderComponent::PointColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 1.f;
}

void PointColliderComponent::Construct(OKVector2<float> position, float radius)
{
	m_Position = position;
	m_Radius = radius;
}

void PointColliderComponent::Construct(float x, float y, float radius)
{
	m_Position = OKVector2<float>(x, y);
	m_Radius = radius;
}

PointColliderComponent::~PointColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 1.f;
}
