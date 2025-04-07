#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(OKVector2<float> position, float mass, unsigned int maxParticleCount, bool isLooping, ParticleSpawnArea particleSpawnArea, ParticleAction particleAction, float simulationSpeed, bool simulateGravity)
{
	// NOTE: Init Timer to NULL for random function
	srand(time(NULL));
	m_ParticleTimer = 0.0f;

	// NOTE: Set Transform
	OKTransform2<float> transform = OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);
	m_Transform = transform;

	// NOTE: Init Particle System Variables
	
	// NOTE: Fill Vector and reserve the set size for the particles
	m_MaxParticleCount = maxParticleCount;
	//m_Particles.reserve(m_MaxParticleCount);
	// m_SimulateParticles.reserve(m_MaxParticleCount);

	// NOTE: Fill Simulation Variables
	m_IsLooping = isLooping;
	m_SimulateGravity = simulateGravity;
	m_SimulationSpeed = simulationSpeed;

	m_Duration = 10.f;

	m_EmissionRateOverTime = 5u;
	m_EmissionRateOverDistance = 0u;

	// NOTE: Set Defauls for Particles
	c_ParticleSystemObject particle_system_objects = c_ParticleSystemObject(&m_Transform, mass);
	particle_system_objects.particle.SimulateGravity(m_SimulateGravity);

	particle_system_objects.startDelay = 0.0f;
	particle_system_objects.startLifeTime = 1.0f;

	particle_system_objects.startSpeed = 1.0f;
	particle_system_objects.startSize = OKVector2<float>(1.0f);
	particle_system_objects.gravity = OKVector2<float>(0.f, 0.0f);

	particle_system_objects.startingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	particle_system_objects.endingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	particle_system_objects.startingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	particle_system_objects.endingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	particle_system_objects.startingSizeOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	particle_system_objects.endingSizeOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	particle_system_objects.startingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);
	particle_system_objects.endingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);

	for (unsigned int i = 0; i < m_MaxParticleCount; ++i)
	{
		m_Particles.push_back(particle_system_objects);
	}

	// NOTE: Set and "Proccess" Spawn Area
	#pragma region PARTICLE SYSTEM SPAWN AREA INIT

		m_ParticleSpawnArea = particleSpawnArea;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_NONE] = ProcessSpawnAreaNone;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_CIRCLE] = ProcessSpawnAreaCircle;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_HALF_CIRCLE] = ProcessSpawnAreaHalfCircle;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_RECTANGLE] = ProcessSpawnAreaRectangle;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_TRIANGLE] = ProcessSpawnAreaTriangle;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_CAPSULE] = ProcessSpawnAreaCapsule;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_DONUT] = ProcessSpawnAreaDonut;
		m_ParticleAreaMap[PARTICLE_SPAWN_AREA_EDGE] = ProcessSpawnAreaEdge;

	#pragma endregion

	#pragma region PARTICLE SYSTEM ACTION INIT

		// NOTE: Set and "Proccess" Action
		m_ParticleAction = particleAction;
		// m_ParticleActionMap[PARTICLE_ACTION_NONE] = ProcessActionNone;
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

	#pragma endregion

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
	// NOTE: Check if the Particles should be Looping through everything
	if (m_IsLooping == false)
	{
		// NOTE: Execute this Once and only once
		if (m_IsExecuted == false)
		{
			for (auto& v : m_Particles)
			{
				m_ParticleAreaMap[m_ParticleSpawnArea](m_Transform, v);
				ProcessActionNone(v);
			}

			m_IsExecuted = true;
		}

		// NOTE: Update Particle Constantly and based on a Timer
		m_ParticleTimer += deltaTime;
		if (m_Duration >= m_ParticleTimer / 60.f)
		{
			for (auto& v : m_Particles) 
			{ 
				v.particle.Update(deltaTime);
			}
		}
	}
	//else if (m_IsLooping == true)
	//{
	//	// NOTE: Loop the Particles
	//	m_IsExecuted = true;
	//	while (m_IsExecuted)
	//	{
	//		// NOTE: Set the Spawn Point of the Particle (Spawn Area) and Process the Desired Action (Particle Action)
	//		// NOTE: Based On Timer that will be created
	//		for (auto v : m_Particles)
	//		{
	//			m_ParticleAreaMap[m_ParticleSpawnArea](m_Transform, v);
	//			m_ParticleActionMap[m_ParticleAction](v);
	//		}

	//		// NOTE: Update Particles Constantly
	//		for (auto v : m_Particles) { v.particle.Update(deltaTime); }
	//	}
	//}
}

void ParticleSystem::Draw()
{
	for (auto& v : m_Particles)
	{
		DrawCircleV(v.particle.GetPosition().ConvertToVec2(), 10, RED);
	}
}

// NOTE: Spawn Area Functions
void ParticleSystem::ProcessSpawnAreaNone(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.SetPosition(transform.position);
}

void ParticleSystem::ProcessSpawnAreaCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int MaxX = 20;
	int MinX = 10;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 20;
	int MinY = 10;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	particle_system_object.particle.SetPosition(NumX + CentrePosition.x, NumY + CentrePosition.y);
}


void ParticleSystem::ProcessSpawnAreaHalfCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessSpawnAreaRectangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessSpawnAreaTriangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessSpawnAreaCapsule(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessSpawnAreaDonut(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessSpawnAreaEdge(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
}

// NOTE: Action Functions

void ParticleSystem::ProcessActionNone(c_ParticleSystemObject& particle_system_object)
{
	int MaxX = 10;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 10;
	int MinY = 1;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	particle_system_object.particle.AddImpulse(NumX, NumY);
}

void ParticleSystem::ProcessActionBurstOut(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionBurstIn(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionScreen(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionScreenOut(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionScreenIn(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionFall(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionRise(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionRight(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionLeft(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionSpray(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionSpiral(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionFire(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionSmoke(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionSpark(c_ParticleSystemObject& particle_system_object)
{
}

void ParticleSystem::ProcessActionWave(c_ParticleSystemObject& particle_system_object)
{
}


