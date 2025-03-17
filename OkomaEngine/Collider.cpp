#include "Collider.h"

// RECTANGLE / Capsule
Collider::Collider(const char* tag, OKTransform2<float>* transform, bool IsCapsule, bool lockZRot)
{
    // NOTE: Set the Collider Type in the Constructor
    m_ColliderType = ColliderType::COLLIDER_RECTANGLE;

    if (IsCapsule == true) 
    { 
        m_ColliderType = ColliderType::COLLIDER_CAPSULE; 
    }

    if (lockZRot == true) 
    { 
        transform->rotation = OKVector2<float>(0, 0); 
    }

    // NOTE: Set Member Variable Types
    // strcpy_s(m_Tag, strlen(tag), tag);
    m_Transform = transform;
}

// CIRCLE
Collider::Collider(const char* tag, OKTransform2<float>* transform, float radius)
{
    // NOTE: Set the Collider Type in the Constructor
    m_ColliderType = ColliderType::COLLIDER_CIRCLE;

    // NOTE: Set Member Variable Types
    // strcpy_s(m_Tag, strlen(tag), tag);
    m_Transform = transform;
    m_Radius = radius;
}

Collider::~Collider()
{

}

void Collider::Update(const float deltaTime)
{

}

void Collider::Draw()
{
    switch (m_ColliderType)
    {
        case ColliderType::COLLIDER_RECTANGLE: DrawRectangleLines(m_Transform->position.ConvertToVec2().x, m_Transform->position.ConvertToVec2().y, m_Transform->scale.ConvertToVec2().x, m_Transform->scale.ConvertToVec2().y, GREEN); break;

        case ColliderType::COLLIDER_CIRCLE: DrawCircleLines(m_Transform->position.ConvertToVec2().x, m_Transform->position.ConvertToVec2().y, m_Radius, GREEN); break;

        case ColliderType::COLLIDER_CAPSULE:
        {
            // TO BE ADDED: Rendering for CAPSULE
            OKVector2<float> tip_a = OKVector2<float>(m_Transform->position.x, m_Transform->position.y + (m_Transform->scale.y / 2) - (m_Transform->scale.x / 2));
            OKVector2<float> base_a = OKVector2<float>(m_Transform->position.x, m_Transform->position.y - (m_Transform->scale.y / 2) + (m_Transform->scale.x / 2));
            OKVector2<float> line_a = tip_a + base_a;
            DrawLineV(tip_a.ConvertToVec2(), base_a.ConvertToVec2(), GREEN);

            // NOTE: Closest Point
            float line_length = line_a.magnitude();
            float dot = line_a.dot(m_Transform->position) / line_length * line_length;
            OKVector2<float> closest_point = line_a + (dot * (base_a - tip_a));

            DrawCircleV(closest_point.ConvertToVec2(), 3, BLUE);
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
float Collider::PolygonArea()
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

