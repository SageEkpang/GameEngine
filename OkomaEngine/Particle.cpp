#include "Particle.h"

Particle::Particle(OKTransform2<float>* transform, float mass)
{
    m_Transform = transform;
    m_Mass = mass;
}

Particle::~Particle()
{

}

void Particle::Update(const float deltaTime)
{
    if (m_Mass == 0) return;

    // NOTE: Apply Physics Forces to Particle
    if (m_SimulateGravity) { m_NetForce += ApplyGravity(); }
    if (m_SimulateDrag) { m_NetForce += ApplyDrag(); }
    if (m_SimulateFriction) { m_NetForce += ApplyFriction(); }

    // NOTE: Force Calculation
    CalculateAcceleration(deltaTime);

    m_NetForce.zero();
    m_Acceleration.zero();
}

void Particle::Draw()
{

    // DrawCircleV(m_Transform->position.ConvertToVec2(), m_Transform->scale.ConvertToVec2().x, RED);

    // NOTE: Debug Drawing

    // Draw Velocity Direction (Not Normalised)
    //if (m_DrawVelocity)
    //{
    //    Vector2 t_VecEnd = Vector2Multiply(m_Velocity.normalise().ConvertToVec2(), Vector2{ m_Velocity.magnitude(), m_Velocity.magnitude() });
    //    t_VecEnd = Vector2Add(t_VecEnd, m_Transform->position.ConvertToVec2());
    //    DrawLineV(m_Transform->position.ConvertToVec2(), t_VecEnd, GREEN);
    //}

    //// Draw Gravity Force Line
    //if (m_DrawGravity)
    //{
    //    Vector2 t_GravityVec = Vector2Add(pm_CalculatedGravity.ConvertToVec2(), m_Transform->position.ConvertToVec2());
    //    DrawLineV(m_Transform->position.ConvertToVec2(), t_GravityVec, PURPLE);
    //}

    //// Draw Drag Force Line
    //if (m_DrawDrag)
    //{
    //    Vector2 t_DragVec = Vector2Add(pm_CalculatedDrag.ConvertToVec2(), m_Transform->position.ConvertToVec2());
    //    DrawLineV(m_Transform->position.ConvertToVec2(), t_DragVec, BLUE);
    //}

    //// Draw Lift Force Line
    //if (m_DrawLift)
    //{

    //}
}

void Particle::CalculateAcceleration(const float deltaTime)
{
    // NOTE: Add Force to Acceleration
    m_Acceleration += m_NetForce;

    // NOTE: Work out Velocity Calculation
    OKVector2<float> t_Position = m_Transform->position;
    m_Velocity += m_Acceleration * deltaTime;

    // NOTE: Augment Position by Velocity
    t_Position += m_Velocity * deltaTime;
    m_Transform->position = t_Position;
}

OKVector2<float> Particle::ApplyGravity()
{
    pm_CalculatedGravity = m_Gravity * m_Mass;
    pm_CalculatedGravity.negate();
    return pm_CalculatedGravity;
}

OKVector2<float> Particle::ApplyDrag()
{
    if (m_Velocity == OKVector2<float>(0, 0)) { return OKVector2<float>(0, 0); }

    // Calculate drag using the fluid density, velocity squared, drag coefficient and cross sectional area
    float t_DensityOfFluid = 0.1; // Density of Air 
    OKVector2<float> t_CalculateDrag = t_DensityOfFluid * m_Velocity.pow(2) * m_Drag * m_CrossSectionalArea;
    float t_Drag = t_CalculateDrag.magnitude() * 0.5;

    // NOTE: Intergrate Drag
    pm_CalculatedDrag = m_Velocity * -1;
    pm_CalculatedDrag = pm_CalculatedDrag.normalise() * t_Drag;
    return pm_CalculatedDrag;
}

OKVector2<float> Particle::ApplyLift()
{
    // NOTE: Reverse of the Drag Equation
    return OKVector2<float>();
}

OKVector2<float> Particle::ApplyFriction()
{
    // NOTE: This would have to do with collision response
    // FORMULA: Dynamic Friction = Dynamic Friction Coefficient * Normal Reaction Between the 2 Surfaces
    // Ff = uKR



    return OKVector2<float>();
}



