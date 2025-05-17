#include "ColliderEntity.h"

ColliderEntity::ColliderEntity()
{
    m_ColliderType = ColliderType::COLLIDER_TYPE_NONE;
    m_HasCollided = false;
    m_IsActivated = true;
}

ColliderEntity::~ColliderEntity()
{

}

// POLYGONE FUNCTION(s)
float ColliderEntity::PolygonArea()
{
    // NOTE: Init Area
    float t_Area = 0.0f;
    size_t t_Size = m_Vertices.size();
    size_t t_J = t_Size - 1;

    // NOTE: Shoelace Formula
    for (int i = 0; i < t_Size; ++i)
    {
        t_Area += (m_Vertices[t_J].x + m_Vertices[i].x) * (m_Vertices[t_J].y - m_Vertices[i].y);
        t_J = i;
    }

    return (float)std::abs(t_Area / 2.0);
}

