#include "RectangleColliderComponent.h"

RectangleColliderComponent::RectangleColliderComponent()
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> position, OKVector2<float> scale)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	m_Position = position;
	m_Scale = scale;
	m_Rotation = 0.f;
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> position, float width, float height)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, OKVector2<float> scale)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = 0.f;
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, float width, float height)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	if (rotation != 0.f) { m_ColliderType = ColliderType::COLLIDER_TYPE_ORIENTED_RECTANGLE; }

	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> position, float width, float height, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	if (rotation != 0.f) { m_ColliderType = ColliderType::COLLIDER_TYPE_ORIENTED_RECTANGLE; }

	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, OKVector2<float> scale, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	if (rotation != 0.f) { m_ColliderType = ColliderType::COLLIDER_TYPE_ORIENTED_RECTANGLE; }

	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, float width, float height, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_RECTANGLE;
	if (rotation != 0.f) { m_ColliderType = ColliderType::COLLIDER_TYPE_ORIENTED_RECTANGLE; }

	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

RectangleColliderComponent::~RectangleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}
