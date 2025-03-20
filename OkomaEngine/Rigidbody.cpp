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

        float momentOfInteria = 10;
        m_AngularVelocity += m_Torque * (1.0f / momentOfInteria) * deltaTime;
    }

    Mat22 m(PI / 2.0f);
    OKVector2<float> r = m.xCol;

    float angle = 0;
    float a = angle;
    std::cos(a); -std::sin(a);
    std::sin(a); std::cos(a);

    // T = r x w
    // Torque = rotation force
    // Vector from the centre of mass to a particular point on a object. r can be thought of as referring to a radius from COM to a point, every single unique point on an object
    // w is called omega and refers to rotational velocity, this relationship will be used to integrate angular velocity of a rigid body

    // Point on a body and the velocity of that point
    // w = r x v

    // linear velocity to angular velocity
    // v = w x r


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

float Rigidbody::CrossProduct(const OKVector2<float>& a, const OKVector2<float>& b)
{
    return a.x * b.y - a.y * b.x;
}

OKVector2<float> Rigidbody::CrossProduct(const OKVector2<float>& a, float s)
{
    return OKVector2<float>(s * a.y, -s * a.x);
}

OKVector2<float> Rigidbody::CrossProduct(float s, const OKVector2<float> a)
{
    return OKVector2<float>(-s * a.y, s * a.x);
}

OKVector2<float> Rigidbody::GetSupport(const OKVector2<float> direction)
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
