#include "ComplexColliderComponent.h"

ComplexColliderComponent::ComplexColliderComponent()
{
    m_Vertices.clear();

}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName)
{
    m_Vertices.clear();


}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, float sizeOffset)
{
    m_Vertices.clear();

}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, OKVector2<float> positionOffset)
{
    m_Vertices.clear();

}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, OKVector2<float> positionOffset, float sizeOffset)
{
    m_Vertices.clear();

}

ComplexColliderComponent::~ComplexColliderComponent()
{
    m_Vertices.clear();

}

float ComplexColliderComponent::PolygonArea()
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
