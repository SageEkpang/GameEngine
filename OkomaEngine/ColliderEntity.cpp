#include "ColliderEntity.h"

ColliderEntity::ColliderEntity()
{



}

// RECTANGLE / Capsule
ColliderEntity::ColliderEntity(OKTransform2<float>* transform, bool IsCapsule, bool lockZRot)
{
    // NOTE: Set the Collider Type in the Constructor
    m_ColliderType = ColliderType::COLLIDER_RECTANGLE;

    if (transform->rotation != 0)
    { 
        m_ColliderType = ColliderType::COLLIDER_ORIENTED_RECTANGLE; 
    }

    if (IsCapsule == true) { m_ColliderType = ColliderType::COLLIDER_CAPSULE; }
    if (lockZRot == true) 
    { 
        transform->rotation = 0; 
    }

    // NOTE: Set Member Variable Types
    // strcpy_s(m_Tag, strlen(tag), tag);
    m_Transform = transform;
}

// CIRCLE
ColliderEntity::ColliderEntity(OKTransform2<float>* transform, float radius, bool isPoint)
{
    // NOTE: Set the Collider Type in the Constructor
    m_ColliderType = ColliderType::COLLIDER_CIRCLE;
    if (isPoint == true)
    {
        m_ColliderType = ColliderType::COLLIDER_POINT;
    }

    // NOTE: Set Member Variable Types
    // strcpy_s(m_Tag, strlen(tag), tag);
    m_Transform = transform;
    m_Radius = radius;
}

ColliderEntity::ColliderEntity(OKTransform2<float>* transform, OKVector2<float> start_position, OKVector2<float> end_position)
{
    // NOTE: Set the Collider Typein the Constructor
    m_ColliderType = ColliderType::COLLIDER_LINE;

    // NOTE: Set Member Variable Types
    m_Transform = transform;
    m_LineStartPosition = start_position;
    m_LineEndPosition = end_position;
}

ColliderEntity::~ColliderEntity()
{

}

void ColliderEntity::Update(const float deltaTime)
{

}

void ColliderEntity::Draw()
{
    switch (m_ColliderType)
    {
        case ColliderType::COLLIDER_RECTANGLE: 
        {
            DrawRectangleLines(m_Transform->position.ConvertToVec2().x, m_Transform->position.ConvertToVec2().y, m_Transform->scale.ConvertToVec2().x, m_Transform->scale.ConvertToVec2().y, GREEN);
        }
        break;

        case ColliderType::COLLIDER_POINT:
        {
            DrawCircleV(m_Transform->position.ConvertToVec2(), 1.f, GREEN);
        }
        break;

        case ColliderType::COLLIDER_CIRCLE:
        {
            DrawCircleLines(m_Transform->position.ConvertToVec2().x, m_Transform->position.ConvertToVec2().y, m_Radius, GREEN);
        }
        break;

        case ColliderType::COLLIDER_ORIENTED_RECTANGLE:
        {
            /*Rectangle t_Rec = Rectangle{ m_Transform->position.x, m_Transform->position.y, m_Transform->scale.x, m_Transform->scale.y };
            DrawRectanglePro(t_Rec, Vector2{m_Transform->scale.x / 2, m_Transform->scale.y / 2}, m_Transform->rotation, GREEN);*/
        }
        break;

        case ColliderType::COLLIDER_CAPSULE:
        {
            Rectangle t_SmoothRec = Rectangle{ m_Transform->position.x - (m_Transform->scale.x / 2), m_Transform->position.y - (m_Transform->scale.y / 2), m_Transform->scale.x, m_Transform->scale.y };
            DrawRectangleRoundedLines(t_SmoothRec, 10, 10, GREEN);

        }
        break;

        case ColliderType::COLLIDER_LINE:
        {
            DrawLineV(m_LineStartPosition.ConvertToVec2(), m_LineEndPosition.ConvertToVec2(), GREEN);
        }
        break;

        case ColliderType::COLLIDER_COMPLEX:
        {
            // TO BE ADDED: Render for Complex Collision
        }
        break;
    }
}

// POLYGONE FUNCTION(s)
float ColliderEntity::PolygonArea()
{
    // NOTE: Init Area
    float t_Area = 0.0f;
    int t_Size = m_Vertices.size();
    int t_J = t_Size - 1;

    // NOTE: Shoelace Formula
    for (int i = 0; i < t_Size; ++i)
    {
        t_Area += (m_Vertices[t_J].x + m_Vertices[i].x) * (m_Vertices[t_J].y - m_Vertices[i].y);
        t_J = i;
    }

    return std::abs(t_Area / 2.0);
}

