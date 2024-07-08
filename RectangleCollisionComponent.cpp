#include "RectangleCollisionComponent.h"
#include "CircleCollisionComponent.h"

bool RectangleCollisionComponent::CollidesWith(RectangleCollisionComponent& other) 
{
    m_Max = m_Transform->position + m_Transform->scale;
    m_Min = m_Transform->position - m_Transform->scale;

    Vector2Utility OtherMax = other.m_Transform->position + other.m_Transform->scale;
    Vector2Utility OtherMin = other.m_Transform->position - other.m_Transform->scale;

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

    // if (CheckCollisionCircleRec(other.GetTransform()->GetPosition(), other.GetRadius(), 
    // Rectangle{other.GetTransform()->GetPosition().x, other.GetTransform()->GetPosition().y, 
    // other.GetTransform()->GetScale().x, other.GetTransform()->GetScale().y})
    // )
    // {
    //     m_HasCollided = true;
    //     return m_HasCollided;
    // }

    // m_HasCollided = false;
    // return m_HasCollided;
}
