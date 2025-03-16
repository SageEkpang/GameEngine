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

class Rigidbody : public Particle
{
private:

    // RIGIDBODY SHAPE VARIABLE(s)
    float m_Radius{};
    float m_Height{};
    float m_CircularExpands{};

    // RIGIDBODY VARIABLE(s)
    RigidbodyShapeType m_RigidbodyShapeType;
    RigidbodyMovementType m_RigidbodyMovementType;

public:

    // CLASS FUNCTION(s)

    // RECTANGLE
    /// @brief Rectangle Rigidbody Constructor
    Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, RigidbodyMovementType rigidbodyMovementType);

    // CIRCLE
    /// @brief Circle Rigidbody Constructor
    Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, float radius, RigidbodyMovementType rigidbodyMovementType);

    // CAPSULE
    /// @brief Capsule Rigidbody Constructor
    Rigidbody(const char* tag, OKTransform2<float>* transform, float mass, float height, float circularExpands, RigidbodyMovementType rigidbodyMovementType);

    // DESTRUCTOR
    ~Rigidbody() override;


    // BASE FUNCTION(s)
    void Update(const float deltaTime) override;
    void Draw() override;


    // GETTER FUNCTION(s)
    inline RigidbodyShapeType GetRigidbodyShapeType() { return m_RigidbodyShapeType; }
    inline RigidbodyMovementType GetRigidbodyMovementType() { return m_RigidbodyMovementType; }


    // SETTER FUNCTION(s)
    inline void SetRigidbodyShapeType(RigidbodyShapeType rigidbodyShapeType) { m_RigidbodyShapeType = rigidbodyShapeType; }
    inline void SetRigidbodyMovementType(RigidbodyMovementType rigidbodyMovementType) { m_RigidbodyMovementType = rigidbodyMovementType; }

};

#endif