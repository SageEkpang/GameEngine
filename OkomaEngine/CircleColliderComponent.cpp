#include "CircleColliderComponent.h"

CircleColliderComponent::CircleColliderComponent()
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CIRCLE;
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}

CircleColliderComponent::CircleColliderComponent(OKVector2<float> position, float radius)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CIRCLE;
	m_Position = position;
	m_Radius = radius;
}

CircleColliderComponent::CircleColliderComponent(float x, float y, float radius)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CIRCLE;
	m_Position = OKVector2<float>(x, y);
	m_Radius = radius;
}

CircleColliderComponent::~CircleColliderComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Radius = 0.f;
}

void CircleColliderComponent::Update(const float deltaTime)
{

}

void CircleColliderComponent::Draw()
{
	DrawCircleLinesV(m_Position.ConvertToVec2(), m_Radius, GREEN);
}
