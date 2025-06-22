#ifndef RIGIDBODY_2D_COMPONENT_H
#define RIGIDBODY_2D_COMPONENT_H

// NOTE: Header File(S)
#include "HeaderManager.h"
#include <map>
#include <utility>

// NOTE: Parent Class
#include "PhysicsEntity.h"
#include "ComponentEntity.h"
#include <cmath>

enum RigidbodyMovementType
{
    RIGIDBODY_MOVEMENT_TYPE_STATIC,
    RIGIDBODY_MOVEMENT_TYPE_DYNAMIC
};

struct Mat22
{
    OKVector2<float> xCol;
    OKVector2<float> yCol;

    Mat22(const OKVector2<float> x, const OKVector2<float> y)
    {
        xCol = x;
        yCol = y;
    }

    Mat22(float radians)
    {
        float c = std::cos(radians);
        float s = std::sin(radians);

        xCol.x = c;
        xCol.y = -s;

        yCol.x = s;
        yCol.y = c;
    }

    const OKVector2<float> operator*(const OKVector2<float>& rhs) const
    {
        // m00 -> xCol.x
        // m01 -> xCol.y

        // m10 -> yCol.x
        // m11 -> yCol.y

        return OKVector2<float>(xCol.x * rhs.x + xCol.y * rhs.y, yCol.x * rhs.x + yCol.y * rhs.y);
    }
};

// TODO: Split these into different rigidbody classes
class Rigidbody2DComponent : public PhysicsEntity
{
private:

    float m_PhysicsMaterialMultiplier = 1.f;

public:

    // PHYSICS MATERIAL VARIABLE(s)
    float m_FrictionMaterial = 0.5f;

    // BOUNCE MATERIAL VARIABLE(s)
    float m_PhysicsMaterial = 0.0f;

    // RIGIDBODY SHAPE VARIABLE(s)

    float m_Rotation;
    float m_Orientation;
    float m_AngularVelocity;
    float m_Torque;

    // TO ADD
    // Collision Detection type
    // Sleeping Mode
    // Interpolate
    // Constraints

    // RIGIDBODY VARIABLE(s)
    RigidbodyMovementType m_RigidbodyMovementType;

public:

    // CLASS FUNCTION(s) (General)
    Rigidbody2DComponent() = default;

    ~Rigidbody2DComponent() override;

    // CLASS FUNCTION(s) (Components)
    void Construct(float mass = 1.f, RigidbodyMovementType rigidbodyMovementType = RigidbodyMovementType::RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);


    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;


    // GETTER FUNCTION(s)
    inline RigidbodyMovementType GetRigidbodyMovementType() const { return m_RigidbodyMovementType; }

    // SETTER FUNCTION(s)
    inline void SetRigidbodyMovementType(RigidbodyMovementType rigidbodyMovementType) { m_RigidbodyMovementType = rigidbodyMovementType; }

    // TODO: Move these to the OKVector2<float> struct when done
    float CrossProduct(const OKVector2<float>& a, const OKVector2<float>& b);
    OKVector2<float> CrossProduct(const OKVector2<float>& a, float s);
    OKVector2<float> CrossProduct(float s, const OKVector2<float> a);

    OKVector2<float> GetSupport(const OKVector2<float> direction);
    // float FindAxisLeastPenetration(int* faceIndex, Collider* a, Collider* b);

};

#endif