#include "CameraComponent.h"

CameraComponent::CameraComponent() 
{
    m_Camera = new Camera2D();
    m_Camera->offset = Vector2{0, 0};
    m_Camera->target = Vector2{0, 0};
    m_Camera->rotation = 0.0f;
    m_Camera->zoom = 1.0f;
}

CameraComponent::~CameraComponent() 
{
    m_Camera = nullptr;
    delete m_Camera;
}

void CameraComponent::Update(float deltaTime) 
{
    m_Camera->offset = m_Offset.vec2;    
    m_Camera->target = m_Target.vec2;
    m_Camera->rotation = m_Rotation;
    m_Camera->zoom = m_Zoom;
}

void CameraComponent::Draw() 
{
}
