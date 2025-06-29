#include "CameraComponent.h"
#include "GameObjectEntity.h"

CameraComponent::CameraComponent()
{
    m_Camera.offset = Vector2{ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
    m_Camera.target = Vector2{ 0.f, 0.f};
    m_Camera.rotation = 0.0f;
    m_Camera.zoom = 1.0f;
}

CameraComponent::~CameraComponent()
{
    m_Camera = { 0 };
}

void CameraComponent::Construct()
{
    m_Offset = OKVector2<float>();
    m_Target = OKVector2<float>();
    m_Rotation = 0.f;
    m_Zoom = 1.0f;

    m_Camera.offset = Vector2{ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
    m_Camera.target = Vector2{ 0.f, 0.f };
    m_Camera.rotation = m_Rotation;
    m_Camera.zoom = m_Zoom;
}

void CameraComponent::Construct(float offsetX, float offsetY)
{
    m_Offset = OKVector2<float>(offsetX, offsetY);
    m_Target = OKVector2<float>(0.f, 0.f);
    m_Rotation = 0.f;
    m_Zoom = 1.0f;
}

void CameraComponent::Construct(OKVector2<float> offset)
{
    m_Offset = offset;
    m_Target = OKVector2<float>(0.f, 0.f);
    m_Rotation = 0.f;
    m_Zoom = 1.0f;
}

void CameraComponent::Construct(OKVector2<float> offset, OKVector2<float> target)
{
    m_Offset = offset;
    m_Target = target;
    m_Rotation = 0.f;
    m_Zoom = 1.0f;
}

void CameraComponent::Construct(OKVector2<float> offset, float targetX, float targetY)
{
    m_Offset = offset;
    m_Target = OKVector2<float>(targetX, targetY);
    m_Rotation = 0.f;
    m_Zoom = 1.0f;
}

void CameraComponent::Construct(OKVector2<float> offset, OKVector2<float> target, float zoom)
{
    m_Offset = offset;
    m_Target = target;
    m_Rotation = 0.f;
    m_Zoom = zoom;
}

void CameraComponent::Update(float deltaTime)
{
    m_Camera.offset = Vector2{ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    m_Camera.target = Vector2{ m_Owner->m_Transform.position.x + m_Offset.x, m_Owner->m_Transform.position.y + m_Offset.y};
    m_Camera.rotation = 0.f;

    // TODO: Change to -1 (will flip the screen)
    m_Camera.zoom = 1.0f;
}

void CameraComponent::Draw()
{

}
