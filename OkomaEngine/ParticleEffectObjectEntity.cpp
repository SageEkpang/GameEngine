#include "ParticleEffectObjectEntity.h"

ParticleEffectObjectEntity::ParticleEffectObjectEntity(OKVector2<float> position, float mass)
{
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
	PhysicsEntity::Update(deltaTime);


}

void ParticleEffectObjectEntity::Draw()
{
	PhysicsEntity::Draw();
}
