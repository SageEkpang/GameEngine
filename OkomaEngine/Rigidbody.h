#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// NOTE: Header File(S)
#include "HeaderManager.h"

// NOTE: Parent Class
#include "Particle.h"

enum RigidbodyShapeType
{
    RIGIDBODY_RECTANGLE,
    RIGIDBODY_CIRCLE,
    RIGIDBODY_CAPSULE,
    RIGIDBODY_COMPLEX
};

enum RigidbodyMovementType
{
    RIGIDBODY_STATIC,
    RIGIDBODY_DYNAMIC
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

class Rigidbody : public Particle
{
private:

    // RIGIDBODY SHAPE VARIABLE(s)
    float m_Radius{};
    float m_Height{};
    float m_CircularExpands{};

    float m_Orientation;
    float m_AngularVelocity;
    float m_Torque;

    // RIGIDBODY VARIABLE(s)
    RigidbodyShapeType m_RigidbodyShapeType;
    RigidbodyMovementType m_RigidbodyMovementType;

public:

    // CLASS FUNCTION(s)

    // RECTANGLE
    /// @brief Rectangle Rigidbody Constructor
    Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, RigidbodyMovementType rigidbodyMovementType, bool IsCapsule = false, bool lockZRot = true);

    // CIRCLE
    /// @brief Circle Rigidbody Constructor
    Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType);

    // DESTRUCTOR
    ~Rigidbody() override;


    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;


    // GETTER FUNCTION(s)
    inline RigidbodyShapeType GetRigidbodyShapeType() const { return m_RigidbodyShapeType; }
    inline RigidbodyMovementType GetRigidbodyMovementType() const { return m_RigidbodyMovementType; }


    // SETTER FUNCTION(s)
    inline void SetRigidbodyShapeType(RigidbodyShapeType rigidbodyShapeType) { m_RigidbodyShapeType = rigidbodyShapeType; }
    inline void SetRigidbodyMovementType(RigidbodyMovementType rigidbodyMovementType) { m_RigidbodyMovementType = rigidbodyMovementType; }

    // TODO: Move these to the OKVector2<float> struct when done
    float CrossProduct(const OKVector2<float>& a, const OKVector2<float>& b);
    OKVector2<float> CrossProduct(const OKVector2<float>& a, float s);
    OKVector2<float> CrossProduct(float s, const OKVector2<float> a);

    OKVector2<float> GetSupport(const OKVector2<float> direction);
    // float FindAxisLeastPenetration(int* faceIndex, Collider* a, Collider* b);

};

#endif