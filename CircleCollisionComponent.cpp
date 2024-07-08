#include "CircleCollisionComponent.h"
#include "RectangleCollisionComponent.h"

bool CircleCollisionComponent::CollidesWith(CircleCollisionComponent& other) 
{
    Vector2 DistanceBetweenPoints = Vector2Subtract(other.m_Transform->position.vec2, m_Transform->position.vec2);
    float CombinedRadii = other.m_Radius + m_Radius;
    float Magnitude = sqrt((DistanceBetweenPoints.x * DistanceBetweenPoints.x) + (DistanceBetweenPoints.y * DistanceBetweenPoints.y));

    if (Magnitude < CombinedRadii) 
    {
        m_HasCollided = true;
        return m_HasCollided;
    }

    m_HasCollided = false;
    return m_HasCollided;
}

bool CircleCollisionComponent::CollidesWith(RectangleCollisionComponent& other) 
{

    // if (CheckCollisionCircleRec(m_Transform->position.vec2, m_Radius, 
    // Rectangle{m_Transform->position.x, m_Transform->position.y, 
    // m_Transform->scale.x, m_Transform->scale.y})
    // )
    // {
    //     m_HasCollided = true;
    //     return m_HasCollided;
    // }

    // m_HasCollided = false;
    // return m_HasCollided;
}

