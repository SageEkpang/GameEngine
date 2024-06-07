#include "RectangleCollisionComponent.h"
#include "CircleCollisionComponent.h"

bool RectangleCollisionComponent::CollidesWith(RectangleCollisionComponent& other) 
{
    m_Max = Vector2Add(m_Transform->GetPosition(), m_Transform->GetScale());
    m_Min = Vector2Subtract(m_Transform->GetPosition(), m_Transform->GetScale());

    Vector2 OtherMax = Vector2Add(other.m_Transform->GetPosition(), other.m_Transform->GetScale());
    Vector2 OtherMin = Vector2Subtract(other.m_Transform->GetPosition(), other.m_Transform->GetScale());

    if (m_Min.x <= OtherMax.x && m_Max.x >= OtherMin.x &&
        m_Min.y <= OtherMax.y && m_Max.y >= OtherMin.y)
    {
        m_HasCollided = true;
        return m_HasCollided;
    }

    m_HasCollided = false;
    return m_HasCollided;
}

bool RectangleCollisionComponent::CollidesWith(CircleCollisionComponent& other) 
{

    if (CheckCollisionCircleRec(other.GetTransform()->GetPosition(), other.GetRadius(), 
    Rectangle{other.GetTransform()->GetPosition().x, other.GetTransform()->GetPosition().y, 
    other.GetTransform()->GetScale().x, other.GetTransform()->GetScale().y})
    )
    {
        m_HasCollided = true;
        return m_HasCollided;
    }

    m_HasCollided = false;
    return m_HasCollided;
}
