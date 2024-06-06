#include "CircleCollisionComponent.h"
#include "RectangleCollisionComponent.h"

bool CircleCollisionComponent::CollidesWith(CircleCollisionComponent& other) 
{
    Vector2 DistanceBetweenPoints = Vector2Subtract(other.m_Transform->GetPosition(), m_Transform->GetPosition());
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





    m_HasCollided = false;
    return m_HasCollided;
}

