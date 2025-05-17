#include "CapsuleColliderComponent.h"

CapsuleColliderComponent::CapsuleColliderComponent()
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> position, OKVector2<float> scale)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = position;
	m_Scale = scale;
	m_Rotation = 0.f;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> position, float width, float height)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, OKVector2<float> scale)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = 0.f;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, float width, float height)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> position, float width, float height, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, OKVector2<float> scale, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, float width, float height, float rotation)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

CapsuleColliderComponent::~CapsuleColliderComponent()
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_CAPSULE;
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

void CapsuleColliderComponent::Update(const float deltaTime)
{

}

void CapsuleColliderComponent::Draw()
{
	//case ColliderType::COLLIDER_CAPSULE:
	//{
	//    /*Rectangle t_SmoothRec = Rectangle{ m_Transform->position.x - (m_Transform->scale.x / 2), m_Transform->position.y - (m_Transform->scale.y / 2), m_Transform->scale.x, m_Transform->scale.y };
	//    DrawRectangleRoundedLines(t_SmoothRec, 10, 10, GREEN);*/
	//}
	//break;
}
