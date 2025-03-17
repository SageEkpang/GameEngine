#include "Rigidbody.h"

Rigidbody::Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule, bool lockZRot)
    : Particle(tag, transform, mass)
{
    m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_RECTANGLE;
    if (IsCapsule == true)
    {
        m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_CAPSULE;
    }

    if (lockZRot == true)
    {
        transform->rotation = OKVector2<float>(0, 0);
    }

    m_RigidbodyMovementType = rigidbodyMovementType;
}

Rigidbody::Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType)
    : Particle(tag, transform, mass)
{
    m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_CIRCLE;
    m_RigidbodyMovementType = rigidbodyMovementType;
    m_Radius = radius;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Update(const float deltaTime)
{
    if (m_RigidbodyMovementType == RIGIDBODY_DYNAMIC)
    {
        Particle::Update(deltaTime);
    }
}

void Rigidbody::Draw()
{
    switch (m_RigidbodyShapeType)
    {
        case RigidbodyShapeType::RIGIDBODY_RECTANGLE: 
            DrawRectangleV(m_Transform->position.ConvertToVec2(), m_Transform->scale.ConvertToVec2(), RED); 
        break;

        case RigidbodyShapeType::RIGIDBODY_CIRCLE: DrawCircleV(m_Transform->position.ConvertToVec2(), m_Radius, RED); break;

        case RigidbodyShapeType::RIGIDBODY_CAPSULE:
        {
            Rectangle t_SmoothRec = Rectangle{ m_Transform->position.x - (m_Transform->scale.x / 2), m_Transform->position.y - (m_Transform->scale.y / 2), m_Transform->scale.x, m_Transform->scale.y };
            DrawRectangleRoundedLines(t_SmoothRec, 10, 10, RED);
        }
        break;

        case RigidbodyShapeType::RIGIDBODY_COMPLEX:
        {
            // TO BE ADDED: Render for Complex Collision
        }
        break;
    }

    Particle::Draw(); // NOTE: Mainly holds the debugging information
}
