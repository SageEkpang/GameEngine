#include "Rigidbody.h"

Rigidbody2DComponent::Rigidbody2DComponent()
{

}

Rigidbody2DComponent::Rigidbody2DComponent(OKVector2<float> position, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule, bool lockZRot)
    : PhysicsEntity(position, mass)
{
    m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_RECTANGLE;

    // if (transform->rotation != 0) { m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_ORIENTED_RECTANGLE; }
    // if (IsCapsule == true) { m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_CAPSULE; }
   //  if (lockZRot == true) { transform->rotation = 0; }

    m_RigidbodyMovementType = rigidbodyMovementType;
}

Rigidbody2DComponent::Rigidbody2DComponent(OKVector2<float> position, float mass, float radius, RigidbodyMovementType rigidbodyMovementType)
    : PhysicsEntity(position, mass)
{
    m_RigidbodyShapeType = RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_CIRCLE;
    m_RigidbodyMovementType = rigidbodyMovementType;
    // m_Radius = radius;
}

Rigidbody2DComponent::~Rigidbody2DComponent()
{

}

void Rigidbody2DComponent::Update(const float deltaTime)
{
    if (m_RigidbodyMovementType == RigidbodyMovementType::RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
    {
        PhysicsEntity::Update(deltaTime);

        float momentOfInteria = 10;
        m_AngularVelocity += m_Torque * (1.0f / momentOfInteria) * deltaTime;
    }

    m_AngularVelocity;
    //Mat22 m(PI / 2.0f);
    //OKVector2<float> r = m.xCol;

    //float angle = 0;
    //float a = angle;
    //std::cos(a); -std::sin(a);
    //std::sin(a); std::cos(a);

    // T = r x w
    // Torque = rotation force
    // Vector from the centre of mass to a particular point on a object. r can be thought of as referring to a radius from COM to a point, every single unique point on an object
    // w is called omega and refers to rotational velocity, this relationship will be used to integrate angular velocity of a rigid body

    // Point on a body and the velocity of that point
    // w = r x v

    // linear velocity to angular velocity
    // v = w x r


}

void Rigidbody2DComponent::Draw()
{
    switch (m_RigidbodyShapeType)
    {
        case RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_RECTANGLE:
        {
            DrawRectangleV(GetPosition().ConvertToVec2(), m_Scale.ConvertToVec2(), RED);
        }
        break;

        case RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_ORIENTED_RECTANGLE:
        {
            Rectangle t_Rec = Rectangle{ GetPosition().x, GetPosition().y, m_Scale.x, m_Scale.y };
            DrawRectanglePro(t_Rec, Vector2{ m_Scale.x / 2, m_Scale.y / 2 }, m_Rotation, RED);
        }
        break;

        case RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_CIRCLE:
        {
            DrawCircleV(GetPosition().ConvertToVec2(), m_Radius, RED);
        }
        break;

        case RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_CAPSULE:
        {
            Rectangle t_SmoothRec = Rectangle{ GetPosition().x - (m_Scale.x / 2), GetPosition().y - (m_Scale.y / 2), m_Scale.x, m_Scale.y };
            DrawRectangleRounded(t_SmoothRec, 10, 10, RED);
        }
        break;

        case RigidbodyShapeType::RIGIDBODY_SHAPE_TYPE_COMPLEX:
        {
            // TO BE ADDED: Render for Complex Collision
        }
        break;
    }

    PhysicsEntity::Draw(); // NOTE: Mainly holds the debugging information
}

float Rigidbody2DComponent::CrossProduct(const OKVector2<float>& a, const OKVector2<float>& b)
{
    return a.x * b.y - a.y * b.x;
}

OKVector2<float> Rigidbody2DComponent::CrossProduct(const OKVector2<float>& a, float s)
{
    return OKVector2<float>(s * a.y, -s * a.x);
}

OKVector2<float> Rigidbody2DComponent::CrossProduct(float s, const OKVector2<float> a)
{
    return OKVector2<float>(-s * a.y, s * a.x);
}

OKVector2<float> Rigidbody2DComponent::GetSupport(const OKVector2<float> direction)
{
    //float bestProjection = -FLT_MAX;
    //OKVector2<float> bestVertex;
    //for (int i = 0; i < m_vertexCount; ++i)
    //{
    //    OKVector2<float> v = m_vertices[i];
    //    real projection = Dot(v, dir);
    //    if (projection > bestProjection)
    //    {
    //        bestVertex = v;
    //        bestProjection = projection;
    //    }
    //}
    //return bestVertex;



    return OKVector2<float>();
}
