#include "CapsuleColliderComponent.h"

CapsuleColliderComponent::CapsuleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = 0.f;
	m_Height = 0.f;
}

void CapsuleColliderComponent::Construct(OKVector2<float> offset, OKVector2<float> scale)
{
	m_Offset = offset;
	m_Width = scale.x;
	m_Height = scale.y;
}

void CapsuleColliderComponent::Construct(OKVector2<float> offset, float width, float height)
{
	m_Offset = offset;
	m_Width = width;
	m_Height = height;
}

void CapsuleColliderComponent::Construct(float x, float y, OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(x, y);
	m_Width = scale.x;
	m_Height = scale.y;
}

void CapsuleColliderComponent::Construct(float x, float y, float width, float height)
{
	m_Offset = OKVector2<float>(x, y);
	m_Width = width;
	m_Height = height;
}

void CapsuleColliderComponent::Construct(OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = scale.x;
	m_Height = scale.y;
}

void CapsuleColliderComponent::Construct(float width, float height)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = width;
	m_Height = height;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> offset, OKVector2<float> scale)
{
	m_Offset = offset;
	m_Width = scale.x;
	m_Height = scale.y;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> offset, float width, float height)
{
	m_Offset = offset;
	m_Width = width;
	m_Height = height;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(x, y);
	m_Width = scale.x;
	m_Height = scale.y;
}

CapsuleColliderComponent::CapsuleColliderComponent(float x, float y, float width, float height)
{
	m_Offset = OKVector2<float>(x, y);
	m_Width = width;
	m_Height = height;
}

CapsuleColliderComponent::CapsuleColliderComponent(OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = scale.x;
	m_Height = scale.y;
}

CapsuleColliderComponent::CapsuleColliderComponent(float width, float height)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = width;
	m_Height = height;
}

CapsuleColliderComponent::~CapsuleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Width = 0.f;
	m_Height = 0.f;
}

