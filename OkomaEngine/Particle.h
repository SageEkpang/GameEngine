#ifndef PARTICLE_H
#define PARTICLE_H

// NOTE: Header File(s)
#include "HeaderManager.h"

// NOTE: Variable Include(s)
#include "OKTransform2.h"

// NOTE: Constant(s)
#include "GravityConstants.h"

// NOTE: PARENT CLASS
#include "Component.h"

class Particle : public Component
{
private: // PRIVATE VARIABLE(s)

    OKVector2<float> pm_CalculatedGravity;
    OKVector2<float> pm_CalculatedDrag;
    OKVector2<float> pm_CalculatedLift;
    OKVector2<float> pm_CalculatedFriction;

protected: // PROTECTED VARIABLE(s)

    // TRANSFORM VARIABLE(s)
    const char* m_Tag;
    OKTransform2<float>* m_Transform;

    // FORCE VARIABLE(s)
    OKVector2<float> m_NetForce{};
    OKVector2<float> m_Acceleration{};
    OKVector2<float> m_Velocity{};

    float m_Mass{ 0 };
    float m_CrossSectionalArea{ 1.0 }; // NOTE: width x height

    // FORCES CONSTANT(s)
    mutable OKVector2<float> m_Gravity = OKVector2<float>(0, 50);

    // NOTE: Coefficients
    mutable float m_Drag{ 1.f };
    mutable float m_Lift{ 0.0 };
    mutable float m_Friction{ 0.0 };

    bool m_SimulateGravity = true;
    bool m_SimulateDrag = false;
    bool m_SimulateLift = false;
    bool m_SimulateFriction = false;

    // NOTE: Debug Lines
    bool m_DrawVelocity = true;
    bool m_DrawDrag = true;
    bool m_DrawLift = false;
    bool m_DrawGravity = false;
    bool m_DrawFriction = false;


public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    Particle(const char* tag, OKTransform2<float>* transform, float mass);
    virtual ~Particle();

    // BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw();

    // PHYSICS FUNCTION(s)
    void CalculateAcceleration(const float deltaTime);

    // FORCE FUNCTION(s)
    OKVector2<float> ApplyGravity();
    OKVector2<float> ApplyDrag();
    OKVector2<float> ApplyLift();
    OKVector2<float> ApplyFriction();

    void AddImpulse(OKVector2<float> impulse) { m_Velocity += impulse; }
    void AddImpulse(float x, float y) { m_Velocity += OKVector2<float>(x, y); };

    void AddForce(OKVector2<float> force) { m_NetForce += force; }
    void AddForce(float x, float y) { m_NetForce += OKVector2<float>(x, y); }

    void AddAcceleration(OKVector2<float> acceleration) { m_Acceleration += acceleration; }
    void AddAcceleration(float x, float y) { m_Acceleration += OKVector2<float>(x, y); }


    // GETTER FUNCTION(s)

        // TRANSFORM GETTER(s)
    inline const char* GetTag() { return m_Tag; }
    inline OKTransform2<float>* GetTransform() { return m_Transform; }
    inline OKVector2<float> GetPosition() { return m_Transform->position; }
    inline OKVector2<float> GetScale() { return m_Transform->scale; }
    inline OKVector2<float> GetRotation() { return m_Transform->rotation; }

    // PHYSICS GETTER(s)
    inline const float GetMass() { return m_Mass; }
    inline const float GetInverseMass() { return -m_Mass; }
    inline const OKVector2<float> GetVelocity() { return m_Velocity; }
    inline const OKVector2<float> GetAcceleration() { return m_Acceleration; }
    inline const OKVector2<float> GetGravity() { return m_Gravity; }
    inline const OKVector2<float> GetDrag() { return m_Drag; }
    inline const OKVector2<float> GetLift() { return m_Lift; }
    inline const OKVector2<float> GetFriction() { return m_Friction; }


    // SETTER FUNCTION(s)

        // TRANSFORM SETTER(s)
    inline void SetTag(const char* tag) { m_Tag = tag; }
    inline void SetTransform(OKTransform2<float>* transform) { m_Transform = transform; }
    inline void SetPosition(OKVector2<float> position) { m_Transform->position = position; }
    inline void SetScale(OKVector2<float> scale) { m_Transform->scale = scale; }
    inline void SetRotation(OKVector2<float> rotation) { m_Transform->rotation = rotation; }

    // PHYSICS SETTER(s)
    inline void SimulateGravity(bool simulateGravity) { m_SimulateGravity = simulateGravity; }
    inline void SimulateDrag(bool simulateDrag) { m_SimulateDrag = simulateDrag; }
    inline void SimulateLift(bool simulateLift) { m_SimulateLift = simulateLift; }
    inline void SimulateFriction(bool simulateFriction) { m_SimulateFriction = simulateFriction; }

    inline void SetMass(float mass) { m_Mass = mass; }
    inline void SetVelocity(OKVector2<float> velocity) { m_Velocity = velocity; }
    inline void SetAcceleration(OKVector2<float> acceleration) { m_Acceleration = acceleration; }
    inline void SetGravity(OKVector2<float> gravity) { m_Gravity = gravity; }
    inline void SetDrag(float drag) { m_Drag = drag; }
    inline void SetLift(float lift) { m_Lift = lift; }
    inline void SetFriction(float friction) { m_Friction = friction; }
};

#endif
