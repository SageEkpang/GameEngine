#include "CameraComponent.h"

CameraComponent::CameraComponent() 
{
    m_Camera = new Camera2D();
    m_Camera->offset = m_Offset;
    m_Camera->target = m_Target;
    m_Camera->rotation = m_Rotation;
    m_Camera->zoom = m_Zoom;
}

CameraComponent::~CameraComponent() 
{
    m_Camera = nullptr;
    delete m_Camera;
}

void CameraComponent::Update(float deltaTime) 
{
    m_Camera->offset = m_Offset;    
    m_Camera->target = m_Target;
    m_Camera->rotation = m_Rotation;
    m_Camera->zoom = m_Zoom;
}

void CameraComponent::Draw() 
{
    
}
