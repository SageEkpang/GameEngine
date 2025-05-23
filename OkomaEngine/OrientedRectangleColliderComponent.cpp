#include "OrientedRectangleColliderComponent.h"

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

void OrientedRectangleColliderComponent::Construct(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(OKVector2<float> position, float width, float height, float rotation)
{
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(float x, float y, OKVector2<float> scale, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(float x, float y, float width, float height, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::~OrientedRectangleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}
