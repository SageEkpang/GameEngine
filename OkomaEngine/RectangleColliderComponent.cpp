#include "RectangleColliderComponent.h"

RectangleColliderComponent::RectangleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> offset, OKVector2<float> scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> offset, float width, float height)
{
	m_Offset = offset;
	m_Scale = OKVector2<float>(width, height);
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = scale;
}

RectangleColliderComponent::RectangleColliderComponent(float x, float y, float width, float height)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
}

RectangleColliderComponent::RectangleColliderComponent(OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = scale;
}

RectangleColliderComponent::RectangleColliderComponent(float width, float height)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale.x = width;
	m_Scale.y = height;
}

void RectangleColliderComponent::Construct(OKVector2<float> offset, OKVector2<float> scale)
{
	m_Offset = offset;
	m_Scale = scale;
}

void RectangleColliderComponent::Construct(OKVector2<float> offset, float width, float height)
{
	m_Offset = offset;
	m_Scale = OKVector2<float>(width, height);
}

void RectangleColliderComponent::Construct(float x, float y, OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = scale;
}

void RectangleColliderComponent::Construct(float x, float y, float width, float height)
{
	m_Offset = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
}

void RectangleColliderComponent::Construct(OKVector2<float> scale)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = scale;
}

void RectangleColliderComponent::Construct(float width, float height)
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale.x = width;
	m_Scale.y = height;
}

RectangleColliderComponent::~RectangleColliderComponent()
{
	m_Offset = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
}
