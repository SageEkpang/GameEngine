#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
    m_Camera.offset = Vector2{ 0, 0 };
    m_Camera.target = Vector2{ 0, 0 };
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
}

CameraComponent::~CameraComponent()
{
    
}

void CameraComponent::Update(float deltaTime)
{
    m_Camera.offset = Vector2{ m_Offset.x, m_Offset.y };
    m_Camera.target = Vector2{ m_Target.x, m_Target.y };
    m_Camera.rotation = m_Rotation;
    m_Camera.zoom = m_Zoom;
}

void CameraComponent::Draw()
{

}
