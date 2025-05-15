#include "RectangleComponent.h"

RectangleComponent::RectangleComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}

RectangleComponent::RectangleComponent(OKVector2<float> position, OKVector2<float> scale)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = 0.f;
}

RectangleComponent::RectangleComponent(OKVector2<float> position, float width, float height)
{
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

RectangleComponent::RectangleComponent(float x, float y, OKVector2<float> scale)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = 0.f;
}

RectangleComponent::RectangleComponent(float x, float y, float width, float height)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = 0.f;
}

RectangleComponent::RectangleComponent(OKVector2<float> position, OKVector2<float> scale, float rotation)
{
	m_Position = position;
	m_Scale = scale;
	m_Rotation = rotation;
}

RectangleComponent::RectangleComponent(OKVector2<float> position, float width, float height, float rotation)
{
	m_Position = position;
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

RectangleComponent::RectangleComponent(float x, float y, OKVector2<float> scale, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = scale;
	m_Rotation = rotation;
}

RectangleComponent::RectangleComponent(float x, float y, float width, float height, float rotation)
{
	m_Position = OKVector2<float>(x, y);
	m_Scale = OKVector2<float>(width, height);
	m_Rotation = rotation;
}

RectangleComponent::~RectangleComponent()
{
	m_Position = OKVector2<float>(0.f, 0.f);
	m_Scale = OKVector2<float>(0.f, 0.f);
	m_Rotation = 0.f;
}
