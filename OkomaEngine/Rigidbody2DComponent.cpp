#include "Rigidbody2DComponent.h"

Rigidbody2DComponent::~Rigidbody2DComponent()
{

}

void Rigidbody2DComponent::Construct(float mass, RigidbodyMovementType rigidbodyMovementType)
{
    m_Mass = mass;
    m_RigidbodyMovementType = rigidbodyMovementType;

}

void Rigidbody2DComponent::Update(const float deltaTime)
{
    if (m_RigidbodyMovementType == RigidbodyMovementType::RIGIDBODY_MOVEMENT_TYPE_DYNAMIC)
    {
        PhysicsEntity::Update(deltaTime);

        float momentOfInteria = 10;
        m_AngularVelocity += m_Torque * (1.0f / momentOfInteria) * deltaTime;
    }

    // m_AngularVelocity;
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
