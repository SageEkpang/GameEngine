#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int maxParticleCount)
{
	m_MaxParticleCount = maxParticleCount;
	m_Particles.reserve(m_MaxParticleCount);
}

ParticleSystem::~ParticleSystem()
{
	if (!m_Particles.empty())
	{
		m_Particles.clear();
	}
}

void ParticleSystem::Update(const float deltaTime)
{
	for (auto v : m_Particles)
	{
		v.Update(deltaTime);
	}
}

void ParticleSystem::Draw()
{
	for (auto v : m_Particles)
	{
		v.Draw();
	}
}
