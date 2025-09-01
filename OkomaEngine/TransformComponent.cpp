#include "TransformComponent.h"

TransformComponent::TransformComponent(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

TransformComponent::TransformComponent(float x, float y, float width, float height, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

TransformComponent::TransformComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(1.f, 1.f);
	m_Rotation = 0.f;
}

TransformComponent::~TransformComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(1.f, 1.f);
	m_Rotation = 0.f;
}

void TransformComponent::Construct(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

void TransformComponent::Construct(float x, float y, float width, float height, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}
