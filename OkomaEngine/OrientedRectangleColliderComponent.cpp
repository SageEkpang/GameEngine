#include "OrientedRectangleColliderComponent.h"

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(OKVector2<float> offset, OKVector2<float> scale, float rotation)
{
	m_Offset = offset;
	m_Scale = scale;
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(OKVector2<float> offset, float width, float height, float rotation)
{
	m_Offset = offset;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(float x, float y, OKVector2<float> scale, float rotation)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(float x, float y, float width, float height, float rotation)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(OKVector2<float> scale, float rotation)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = scale;
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::OrientedRectangleColliderComponent(float width, float height, float rotation)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale.x = width;
	m_Scale.y = height;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(OKVector2<float> offset, OKVector2<float> scale, float rotation)
{
	m_Offset = offset;
	m_Scale = scale;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(OKVector2<float> offset, float width, float height, float rotation)
{
	m_Offset = offset;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(float x, float y, OKVector2<float> scale, float rotation)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(float x, float y, float width, float height, float rotation)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(OKVector2<float> scale, float rotation)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = scale;
	m_Rotation = rotation;
}

void OrientedRectangleColliderComponent::Construct(float width, float height, float rotation)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale.x = width;
	m_Scale.y = height;
	m_Rotation = rotation;
}

OrientedRectangleColliderComponent::~OrientedRectangleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

