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

public: // PROTECTED VARIABLE(s)

    float m_Mass{ 1.f };

    // FORCES CONSTANT(s)
    mutable OKVector2<float> m_Gravity = GRAVITY_EARTH;

    // NOTE: FORCE VARIABLE(s)
    OKVector2<float> m_NetForce{};
    OKVector2<float> m_Acceleration{};
    OKVector2<float> m_Velocity{};

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

        // NOTE: PHYSICS FUNCTION(s)
        inline float GetInverseMass()
        {
            if (m_Mass == 0.0f) return 0.0f;
            else return 1 / m_Mass; 
        }

        inline OKVector2<float> GetDirection() { return m_Velocity.normalise(); }

        inline OKVector2<float> GetCurrentGravity() { return pm_CalculatedGravity; }
        inline OKVector2<float> GetCurrentDrag() { return pm_CalculatedDrag; }
        inline OKVector2<float> GetCurrentLift() { return pm_CalculatedLift; }
        inline OKVector2<float> GetCurrentFriction() { return pm_CalculatedFriction; }

    #pragma endregion

    #pragma region Setter Function(s)

    // SETTER FUNCTION(s)

        // NOTE: PHYSICS FUNCTION(s) 
        inline void SimulateGravity(bool simulateGravity) { m_SimulateGravity = simulateGravity; }
        inline void SimulateDrag(bool simulateDrag) { m_SimulateDrag = simulateDrag; }
        inline void SimulateLift(bool simulateLift) { m_SimulateLift = simulateLift; }
        inline void SimulateFriction(bool simulateFriction) { m_SimulateFriction = simulateFriction; }

    #pragma endregion

};

#endif
