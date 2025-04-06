#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(OKTransform2<float> transform, float mass, unsigned int maxParticleCount, ParticleSpawnArea particleSpawnArea, ParticleAction particleAction)
{
	// NOTE: Set Transform
	m_Transform = transform;

	// NOTE: Fill Vector and reserve the set size for the particles
	m_MaxParticleCount = maxParticleCount;
	m_Particles.reserve(m_MaxParticleCount);

	for (unsigned int i = 0; i < m_MaxParticleCount; ++i)
	{
		Particle particle = Particle(&m_Transform, mass);
		m_Particles.push_back(particle);
	}

	// NOTE: Set and "Proccess" Spawn Area
	m_ParticleSpawnArea = particleSpawnArea;
	m_ParticleAction = particleAction;

	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_NONE] = ProcessSpawnAreaNone;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_CIRCLE] = ProcessSpawnAreaCircle;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_HALF_CIRCLE] = ProcessSpawnAreaHalfCircle;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_RECTANGLE] = ProcessSpawnAreaRectangle;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_TRIANGLE] = ProcessSpawnAreaTriangle;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_CAPSULE] = ProcessSpawnAreaCapsule;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_DONUT] = ProcessSpawnAreaDonut;
	m_ParticleAreaMap[PARTICLE_SPAWN_AREA_EDGE] = ProcessSpawnAreaEdge;


	// NOTE: Set and "Proccess" Action
	m_ParticleActionMap[PARTICLE_ACTION_NONE] = ProcessActionNone;
	m_ParticleActionMap[PARTICLE_ACTION_BURST_OUT] = ProcessActionBurstOut;
	m_ParticleActionMap[PARTICLE_ACTION_BURST_IN] = ProcessActionBurstIn;

	m_ParticleActionMap[PARTICLE_ACTION_SCREEN] = ProcessActionScreen;
	m_ParticleActionMap[PARTICLE_ACTION_SCREEN_OUT] = ProcessActionScreenOut;
	m_ParticleActionMap[PARTICLE_ACTION_SCREEN_IN] = ProcessActionScreenIn;

	m_ParticleActionMap[PARTICLE_ACTION_FALL] = ProcessActionFall;
	m_ParticleActionMap[PARTICLE_ACTION_RISE] = ProcessActionRise;
	m_ParticleActionMap[PARTICLE_ACTION_RIGHT] = ProcessActionRight;
	m_ParticleActionMap[PARTICLE_ACTION_LEFT] = ProcessActionLeft;

	m_ParticleActionMap[PARTICLE_ACTION_SPRAY] = ProcessActionSpray;
	m_ParticleActionMap[PARTICLE_ACTION_SPIRAL] = ProcessActionSpiral;

	m_ParticleActionMap[PARTICLE_ACTION_FIRE] = ProcessActionFire;
	m_ParticleActionMap[PARTICLE_ACTION_SMOKE] = ProcessActionSmoke;
	m_ParticleActionMap[PARTICLE_ACTION_SPARK] = ProcessActionSpark;
	m_ParticleActionMap[PARTICLE_ACTION_WAVE] = ProcessActionWave;

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
		// NOTE: Set the Spawn Point of the Particle (Spawn Area) and Process the Desired Action (Particle Action)
		m_ParticleAreaMap[m_ParticleSpawnArea](v);
		m_ParticleActionMap[m_ParticleAction](v);
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

void ParticleSystem::ProcessSpawnAreaNone(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaCircle(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaHalfCircle(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaRectangle(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaTriangle(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaCapsule(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaDonut(Particle& particle)
{
}

void ParticleSystem::ProcessSpawnAreaEdge(Particle& particle)
{
}

void ParticleSystem::ProcessActionNone(Particle& particle)
{
}

void ParticleSystem::ProcessActionBurstOut(Particle& particle)
{
}

void ParticleSystem::ProcessActionBurstIn(Particle& particle)
{
}

void ParticleSystem::ProcessActionScreen(Particle& particle)
{
}

void ParticleSystem::ProcessActionScreenOut(Particle& particle)
{
}

void ParticleSystem::ProcessActionScreenIn(Particle& particle)
{
}

void ParticleSystem::ProcessActionFall(Particle& particle)
{
}

void ParticleSystem::ProcessActionRise(Particle& particle)
{
}

void ParticleSystem::ProcessActionRight(Particle& particle)
{
}

void ParticleSystem::ProcessActionLeft(Particle& particle)
{
}

void ParticleSystem::ProcessActionSpray(Particle& particle)
{

}

void ParticleSystem::ProcessActionSpiral(Particle& particle)
{
}

void ParticleSystem::ProcessActionFire(Particle& particle)
{
}

void ParticleSystem::ProcessActionSmoke(Particle& particle)
{
}

void ParticleSystem::ProcessActionSpark(Particle& particle)
{
}

void ParticleSystem::ProcessActionWave(Particle& particle)
{
}

