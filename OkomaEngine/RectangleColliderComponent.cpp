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

void RectangleColliderComponent::Update(const float deltaTime)
{

}

void RectangleColliderComponent::Draw()
{
	if (m_ColliderType == COLLIDER_TYPE_RECTANGLE)
	{
		DrawRectangleLines((int)m_Position.ConvertToVec2().x - (int)(m_Scale.x / 2.f), (int)m_Position.ConvertToVec2().y - (int)(m_Scale.y / 2.f), (int)m_Scale.ConvertToVec2().x, (int)m_Scale.ConvertToVec2().y, GREEN);
	}
	else
	{
		Rectangle t_Rec = Rectangle{ m_Position.x, m_Position.y, m_Scale.x, m_Scale.y };
		DrawRectanglePro(t_Rec, Vector2{m_Scale.x / 2.f, m_Scale.y / 2.f}, m_Rotation, GREEN);
	}
}
