#include "PhysicsEntity.h"
#include "GameObjectEntity.h"

PhysicsEntity::PhysicsEntity()
{
    m_Velocity = OKVector2<float>();
    pm_CalculatedGravity = OKVector2<float>();
    pm_CalculatedDrag = OKVector2<float>();
    pm_CalculatedLift = OKVector2<float>();
    pm_CalculatedFriction = OKVector2<float>();
}

PhysicsEntity::~PhysicsEntity()
{

}

void PhysicsEntity::Update(const float deltaTime)
{
    if (m_Mass == 0) return;

    // NOTE: Apply Physics Forces to Particle
    if (m_SimulateGravity) { m_NetForce += ApplyGravity(); }
    if (m_SimulateDrag) { m_NetForce += ApplyDrag(); }
    if (m_SimulateLift) { m_NetForce += ApplyLift(); }
    if (m_SimulateFriction) { m_NetForce += ApplyFriction(); }

    // NOTE: Force Calculation
    CalculateAcceleration(deltaTime);

    m_NetForce.zero();
    m_Acceleration.zero();
}

void PhysicsEntity::CalculateAcceleration(const float deltaTime)
{
    // NOTE: Add Force to Acceleration
    m_Acceleration += m_NetForce;

    // NOTE: Work out Velocity Calculation
    OKVector2<float> t_Position = m_Owner->m_Transform.position;
    m_Velocity += m_Acceleration * deltaTime;

    // NOTE: Augment Position by Velocity
    t_Position += m_Velocity * deltaTime;
    m_Owner->m_Transform.position = t_Position;
}

OKVector2<float> PhysicsEntity::ApplyGravity()
{
    pm_CalculatedGravity = m_Gravity * m_Mass * -1;
    pm_CalculatedGravity.negate();

    return pm_CalculatedGravity;
}

OKVector2<float> PhysicsEntity::ApplyDrag()
{
    // NOTE: Drag is apparently only a force to be applied left and right
    if (m_Velocity.x == 0.f) { return OKVector2<float>(0.f, 0.f); }

    OKVector2<float> t_CopyVelocity = m_Velocity;

    // Calculate drag using the fluid density, velocity squared, drag coefficient and cross sectional area
    float t_DensityOfFluid = m_DragFluidDensity; // Density of Air 
    OKVector2<float> t_CalculateDrag = t_DensityOfFluid * (t_CopyVelocity.pow(2) * 0.5f) * m_Drag * m_DragCrossSectionalArea;
    float t_Drag = t_CalculateDrag.magnitude();

    // NOTE: Intergrate Drag
    pm_CalculatedDrag = t_CopyVelocity * -1;
    pm_CalculatedDrag = pm_CalculatedDrag.normalise() * t_Drag;
    pm_CalculatedDrag = OKVector2<float>(pm_CalculatedDrag.x, t_CopyVelocity.y);

    return pm_CalculatedDrag;
}

OKVector2<float> PhysicsEntity::ApplyLift()
{
    // NOTE: Lift is apparently only a force for up and down
    if (m_Velocity.y == 0.f) { return OKVector2<float>(0.0f, 0.0f); }

    OKVector2<float> t_CopyVelocity = m_Velocity;

    float t_DensityOfFluid = m_LiftFluidDensity;
    OKVector2<float> t_CalculateLift = t_DensityOfFluid * (t_CopyVelocity.pow(2) * 0.5f) * m_Lift * m_LiftCrossSectionalArea;
    float t_Lift = t_CalculateLift.magnitude();

    pm_CalculatedLift = t_CopyVelocity * -1;
    pm_CalculatedLift = pm_CalculatedLift.normalise() * t_Lift;
    pm_CalculatedLift = OKVector2<float>(t_CopyVelocity.x, pm_CalculatedLift.y);

    return pm_CalculatedLift;
}

// NOTE: This would have to do with collision response
// FORMULA: Dynamic Friction = Dynamic Friction Coefficient * Normal Reaction Between the 2 Surfaces
// Ff = uKR
OKVector2<float> PhysicsEntity::ApplyFriction()
{
    if (m_Velocity.x == 0.f) { return OKVector2<float>(0.f, 0.f); }

    OKVector2<float> t_CopyVelocity = m_Velocity;
    OKVector2<float> t_CalculatedFriction = t_CopyVelocity.pow(2) * m_Friction;
    float t_Friction = t_CalculatedFriction.magnitude();

    pm_CalculatedFriction = t_CopyVelocity * -1;
    pm_CalculatedFriction = pm_CalculatedFriction.normalise() * t_Friction;
    pm_CalculatedFriction = OKVector2<float>(pm_CalculatedFriction.x, pm_CalculatedFriction.y);

    return pm_CalculatedFriction;
}


