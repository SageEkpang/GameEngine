#include "TransformUtility.h"

TransformUtility::TransformUtility() 
{
    m_Position = Vector2();
    m_Scale = Vector2();
    m_Rotation = 0;
}

TransformUtility::~TransformUtility() 
{
    
}

void TransformUtility::Update(float deltaTime) 
{
    Vector2 Position = this->m_Position;
    Vector2 Scale = this->m_Scale;
    float Rotation = this->m_Rotation;
}
