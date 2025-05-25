#include "ComplexColliderComponent.h"

ComplexColliderComponent::ComplexColliderComponent(const char* fileName)
{

}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, float sizeOffset)
{
}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, OKVector2<float> offset)
{
}

ComplexColliderComponent::ComplexColliderComponent(const char* fileName, OKVector2<float> offset, float sizeOffset)
{
}

ComplexColliderComponent::ComplexColliderComponent()
{
    m_Vertices.clear();
    m_FileName = " ";

}

void ComplexColliderComponent::Construct(const char* fileName)
{
    m_FileName = fileName;
}

void ComplexColliderComponent::Construct(const char* fileName, float sizeOffset)
{
    m_FileName = fileName;

}

void ComplexColliderComponent::Construct(const char* fileName, OKVector2<float> offset)
{
    m_FileName = fileName;

}

void ComplexColliderComponent::Construct(const char* fileName, OKVector2<float> offset, float sizeOffset)
{
    m_FileName = fileName;

}

ComplexColliderComponent::~ComplexColliderComponent()
{
    m_Vertices.clear();
    m_FileName = " ";
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
