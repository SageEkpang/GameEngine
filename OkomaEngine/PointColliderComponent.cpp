#include "PointColliderComponent.h"

PointColliderComponent::PointColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = 1.f;
}

PointColliderComponent::PointColliderComponent(float radius)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = radius;
}

PointColliderComponent::PointColliderComponent(OKVector2<float> offset, float radius)
{
	m_Offset = offset;
	m_Radius = radius;
}

PointColliderComponent::PointColliderComponent(float x, float y, float radius)
{
	m_Offset = OKVector2<float>(x, y);
	m_Radius = radius;
}

void PointColliderComponent::Construct(float radius)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = radius;
}

void PointColliderComponent::Construct(OKVector2<float> offset, float radius)
{
	m_Offset = offset;
	m_Radius = radius;
}

void PointColliderComponent::Construct(float x, float y, float radius)
{
	m_Offset = OKVector2<float>(x, y);
	m_Radius = radius;
}

PointColliderComponent::~PointColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Radius = 1.f;
}
