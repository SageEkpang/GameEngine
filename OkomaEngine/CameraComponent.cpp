#include "CameraComponent.h"

OKCameraComponent::OKCameraComponent()
{
    m_Camera = new Camera2D();
    m_Camera->offset = Vector2{ 0, 0 };
    m_Camera->target = Vector2{ 0, 0 };
    m_Camera->rotation = 0.0f;
    m_Camera->zoom = 1.0f;
}

OKCameraComponent::~OKCameraComponent()
{
    m_Camera = nullptr;
    delete m_Camera;
}

void OKCameraComponent::Update(float deltaTime)
{
    m_Camera->offset = Vector2{ m_Offset.x, m_Offset.y };
    m_Camera->target = Vector2{ m_Target.x, m_Target.y };
    m_Camera->rotation = m_Rotation;
    m_Camera->zoom = m_Zoom;
}