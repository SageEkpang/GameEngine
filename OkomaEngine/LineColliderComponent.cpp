#include "LineColliderComponent.h"

LineColliderComponent::LineColliderComponent()
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_LINE;
	m_LineStartPosition = OKVector2<float>(0.f, 0.f);
	m_LineEndPosition = OKVector2<float>(0.f, 0.f);
}

LineColliderComponent::LineColliderComponent(OKVector2<float> lineStartPosition, OKVector2<float> lineEndPosition)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_LINE;
	m_LineStartPosition = lineStartPosition;
	m_LineEndPosition = lineEndPosition;
}

LineColliderComponent::LineColliderComponent(OKVector2<float> lineStartPosition, float endX, float endY)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_LINE;
	m_LineStartPosition = lineStartPosition;
	m_LineEndPosition = OKVector2<float>(endX, endY);
}

LineColliderComponent::LineColliderComponent(float startX, float startY, OKVector2<float> lineEndPosition)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_LINE;
	m_LineStartPosition = OKVector2<float>(startX, startY);
	m_LineEndPosition = lineEndPosition;
}

LineColliderComponent::LineColliderComponent(float startX, float startY, float endX, float endY)
{
	m_ColliderType = ColliderType::COLLIDER_TYPE_LINE;
	m_LineStartPosition = OKVector2<float>(startX, startY);
	m_LineEndPosition = OKVector2<float>(endX, endY);
}

LineColliderComponent::~LineColliderComponent()
{
	m_LineStartPosition = OKVector2<float>(0.f, 0.f);
	m_LineEndPosition = OKVector2<float>(0.f, 0.f);
}
