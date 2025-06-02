#ifndef PHYSICS_ENTITY_H
#define PHYSICS_ENTITY_H

// NOTE: Header File(s)
#include "HeaderManager.h"
#include "ComponentEntity.h"

// NOTE: Variable Include(s)
#include "OKTransform2.h"

// NOTE: Constant(s)
#include "GravityConstants.h"

class PhysicsEntity : public ComponentEntity
{
private: // PRIVATE VARIABLE(s)

    // CALCULATING VARIABLE(s)
    OKVector2<float> pm_CalculatedGravity;
    OKVector2<float> pm_CalculatedDrag;
    OKVector2<float> pm_CalculatedLift;
    OKVector2<float> pm_CalculatedFriction;

    // FORCE VARIABLE(s)
    OKVector2<float> m_NetForce{};
    OKVector2<float> m_Acceleration{};
    OKVector2<float> m_Velocity{};

public: // PROTECTED VARIABLE(s)

    // POSITION VARIABLE(s)
    OKVector2<float> m_Position;

    float m_Mass{ 0.f };

    // FORCES CONSTANT(s)
    mutable OKVector2<float> m_Gravity = GRAVITY_EARTH;

    // NOTE: Coefficient of Drag
    mutable float m_Drag{ 1.f };
    mutable float m_DragFluidDensity{ 1.4f };
    mutable float m_DragCrossSectionalArea{ 1.f };

    // NOTE: Coefficient of Lift
    mutable float m_Lift{ 1.f };
    mutable float m_LiftFluidDensity{ 1.4f };
    mutable float m_LiftCrossSectionalArea{ 1.f };

    // NOTE: Coefficient of Friction
    mutable float m_Friction{ 1.f };

    bool m_SimulateGravity = true;
    bool m_SimulateDrag = false;
    bool m_SimulateLift = false;
    bool m_SimulateFriction = false;

    // NOTE: Debug Lines
    bool m_DrawVelocity = false;
    bool m_DrawDrag = false;
    bool m_DrawLift = false;
    bool m_DrawGravity = false;
    bool m_DrawFriction = false;

private:

    // FORCE FUNCTION(s)
    OKVector2<float> ApplyGravity();
    OKVector2<float> ApplyDrag();
    OKVector2<float> ApplyLift();
    OKVector2<float> ApplyFriction();

    void CalculateAcceleration(const float deltaTime);

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    PhysicsEntity();
    PhysicsEntity(OKVector2<float> position, float mass);
    virtual ~PhysicsEntity();

    // BASE FUNCTION(s)
    virtual void Update(const float deltaTime);
    virtual void Draw() { }

    // PHYSICS FUNCTION(s)
    void ApplyImpulse(OKVector2<float> impulse) { m_Velocity += impulse; }
    void ApplyImpulse(float x, float y) { m_Velocity += OKVector2<float>(x, y); };

    void ApplyImpulseX(float impulseX) { m_Velocity += OKVector2<float>(impulseX, 0.0f); }
    void ApplyImpulseY(float impulseY) { m_Velocity += OKVector2<float>(0.0f, impulseY); }

    void ApplyForce(OKVector2<float> force) { m_NetForce += force; }
    void ApplyForce(float x, float y) { m_NetForce += OKVector2<float>(x, y); }

    void ApplyAcceleration(OKVector2<float> acceleration) { m_Acceleration += acceleration; }
    void ApplyAcceleration(float x, float y) { m_Acceleration += OKVector2<float>(x, y); }


    #pragma region Getter Function(s)

    // GETTER FUNCTION(s)

        // NOTE: BASE(s)
        inline OKVector2<float> GetPosition() { return m_Position; }

        // NOTE: PHYSICS FUNCTION(s)
        inline float GetMass() const { return m_Mass; }
        inline float GetInverseMass()
        {
            if (m_Mass == 0.0f) return 0.0f;
            else return 1 / m_Mass; 
        }
        inline OKVector2<float> GetForce() const { return m_NetForce; }
        inline OKVector2<float> GetVelocity() const { return m_Velocity; }
        inline OKVector2<float> GetDirection() { return m_Velocity.normalise(); }
        inline OKVector2<float> GetAcceleration() const { return m_Acceleration; }

        inline OKVector2<float> GetGravity() const { return m_Gravity; }
        inline OKVector2<float> GetDrag() { return m_Drag; }
        inline OKVector2<float> GetLift() { return m_Lift; }
        inline OKVector2<float> GetFriction() { return m_Friction; }

        inline OKVector2<float> GetCurrentGravity() { return pm_CalculatedGravity; }
        inline OKVector2<float> GetCurrentDrag() { return pm_CalculatedDrag; }
        inline OKVector2<float> GetCurrentLift() { return pm_CalculatedLift; }
        inline OKVector2<float> GetCurrentFriction() { return pm_CalculatedFriction; }

    #pragma endregion

    #pragma region Setter Function(s)

    // SETTER FUNCTION(s)

        // NOTE: BASE(s)
       inline void SetPosition(OKVector2<float> position) { m_Position = position; }
       inline void SetPosition(float x, float y) { m_Position = OKVector2<float>(x, y); }

        // NOTE: PHYSICS FUNCTION(s) 
        inline void SetMass(float mass) { m_Mass = mass; }

        inline void SimulateGravity(bool simulateGravity) { m_SimulateGravity = simulateGravity; }
        inline void SimulateDrag(bool simulateDrag) { m_SimulateDrag = simulateDrag; }
        inline void SimulateLift(bool simulateLift) { m_SimulateLift = simulateLift; }
        inline void SimulateFriction(bool simulateFriction) { m_SimulateFriction = simulateFriction; }

        inline void SetVelocity(OKVector2<float> velocity) { m_Velocity = velocity; }
        inline void SetVelocity(float x, float y) { m_Velocity = OKVector2<float>(x, y); }
        inline void SetVelocityX(float x) { m_Velocity.x = x; }
        inline void SetVelocityY(float y) { m_Velocity.y = y; }

        // inline void SetDirection(OKVector2<float> normalised_direction, float multiplier = 1.f) { m_Velocity = normalised_direction; }

        inline void SetForce(OKVector2<float> force) { m_NetForce = force; }
        inline void SetForce(float x, float y) { m_NetForce = OKVector2<float>(x, y); }
        inline void SetForceX(float x) { m_NetForce.x = x; }
        inline void SetForceY(float y) { m_NetForce.y = y; }

        inline void SetAcceleration(OKVector2<float> acceleration) { m_Acceleration = acceleration; }
        inline void SetAcceleration(float x, float y) { m_Acceleration = OKVector2<float>(x, y); }
        inline void SetAccelerationX(float x) { m_Acceleration.x = x; }
        inline void SetAccelerationY(float y) { m_Acceleration.y = y; }

        inline void SetGravity(OKVector2<float> gravity) { m_Gravity = gravity; }
        inline void SetGravity(float x, float y) { m_Gravity = OKVector2<float>(x, y); }
        inline void SetGravityX(float x) { m_Gravity.x = x; }
        inline void SetGravityY(float y) { m_Gravity.y = y; }

        inline void SetDrag(float drag) { m_Drag = drag; }
        inline void SetDragFluidDensity(float dragFluidDensity) { m_DragFluidDensity = dragFluidDensity; }
        inline void SetDragCrossSectionalArea(float dragCrossSectionalArea) { m_DragCrossSectionalArea = dragCrossSectionalArea; }

        inline void SetLift(float lift) { m_Lift = lift; }
        inline void SetLiftFluidDensity(float liftFluidDensity) { m_LiftFluidDensity = liftFluidDensity; }
        inline void SetLiftCrossSectionalArea(float liftCrossSectionalArea) { m_LiftCrossSectionalArea = liftCrossSectionalArea; }

        inline void SetFriction(float friction) { m_Friction = friction; }

    #pragma endregion

};

#endif
