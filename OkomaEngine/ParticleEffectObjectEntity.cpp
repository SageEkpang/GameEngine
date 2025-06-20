#include "ParticleEffectObjectEntity.h"

ParticleEffectObjectEntity::ParticleEffectObjectEntity(OKVector2<float> position, float mass)
{
	// NOTE: Force Variable
	m_Mass = 1.f;

	m_Gravity = OKVector2<float>(0, 0);
	m_NetForce = OKVector2<float>(0, 0);
	m_Acceleration = OKVector2<float>(0, 0);
	m_Velocity = OKVector2<float>(0, 0);


	// NOTE: Particle Effect Object Entity
	m_StartDelay = nullptr;
	m_StartLifeTime = nullptr;
	m_CurrentLifeTime = 0.f;
	m_StartSpeed = nullptr;
	m_Theta = 0.f;

	m_Position = position;
	m_Scale = OKVector2<float>(1.f, 1.f);
	m_Rotation = 0.f;

	m_Colour = OKVector4<unsigned int>(255, 255, 255, 255);

	m_StartSize = nullptr;

	m_StartingVelocityOverLifeTime = nullptr;
	m_EndingVelocityOverLifeTime = nullptr;
	m_CurrentVelocityOverLifeTimer = 0.0f;

	m_StartingForceOverLifeTime = nullptr;
	m_EndingForceOverLifeTime = nullptr;
	m_CurrentForceOverLifeTimer = 0.0f;

	m_StartingSizeOverLifeTime = nullptr;
	m_EndingSizeOverLifeTime = nullptr;
	m_CurrentSizeOverLifeTimer = 0.0f;

	m_StartingSizeByVelocity = nullptr;
	m_EndingSizeByVelocity = nullptr;
	m_CurrentSizeByVelocity = 0.0f;

	m_StartingColourOverLifeTime = nullptr;
	m_EndingColourOverLifeTime = nullptr;
	m_CurrentColourOverLifeTimer = 0.0f;
}

ParticleEffectObjectEntity::~ParticleEffectObjectEntity()
{
	m_StartDelay = nullptr;
	m_StartLifeTime = nullptr;
	m_StartSpeed = nullptr;

	m_StartSize = nullptr;

	m_StartingVelocityOverLifeTime = nullptr;
	m_EndingVelocityOverLifeTime = nullptr;

	m_StartingForceOverLifeTime = nullptr;
	m_EndingForceOverLifeTime = nullptr;

	m_StartingSizeOverLifeTime = nullptr;
	m_EndingSizeOverLifeTime = nullptr;

	m_StartingSizeByVelocity = nullptr;
	m_EndingSizeByVelocity = nullptr;

	m_StartingColourOverLifeTime = nullptr;
	m_EndingColourOverLifeTime = nullptr;
}

void ParticleEffectObjectEntity::Update(float deltaTime)
{
	// NOTE: Return if the Mass is zero, Mass == 0 can cause wrong force calculations
	if (m_Mass == 0) return;

	if (m_SimulateGravity == true)
	{
		// NOTE: Gravity Calculation: G = M *  (-1) -> For the inverse of Y-Axis
		OKVector2<float> t_tempGrav = m_Gravity * m_Mass * -1;
		t_tempGrav.negate();

		m_NetForce += t_tempGrav;
	}

	// NOTE: Force Calculation
	CalculateAcceleration(deltaTime);

	m_NetForce.zero();
	m_Acceleration.zero();
}

void ParticleEffectObjectEntity::CalculateAcceleration(const float deltaTime)
{   
	// NOTE: Add Force to Acceleration
	m_Acceleration += m_NetForce;

	// NOTE: Work out Velocity Calculation
	OKVector2<float> t_Position = m_Position;
	m_Velocity += m_Acceleration * deltaTime;

	// NOTE: Augment Position by Velocity
	t_Position += m_Velocity * deltaTime;
	m_Position = t_Position;
}
