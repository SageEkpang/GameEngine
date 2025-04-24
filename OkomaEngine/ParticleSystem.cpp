#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(OKVector2<float> position, float mass, unsigned int maxParticleCount, bool isLooping, ParticleType particleType, ParticleSpawnArea particleSpawnArea, ParticleAction particleAction, float simulationSpeed, bool simulateGravity)
{
	// NOTE: Init Timer to NULL for random function
	srand(time(NULL));

	// NOTE: Particle Timer and Incremet Variables
	m_ParticleTimer = 0.0f;
	m_ParticleIndexIncrement = 0u;

	// NOTE: Set Transform
	OKTransform2<float> transform = OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);
	m_Transform = transform;

	// NOTE: Init Particle System Variables
	m_MaxParticleCount = maxParticleCount;

	m_ParticleSpawnArea = particleSpawnArea;
	m_ParticleAction = particleAction;
	m_ParticleType = particleType;

	// NOTE: Fill Vector and reserve the set size for the particles
	m_Particles.reserve(m_MaxParticleCount);
	m_SimulatingParticles.reserve(m_MaxParticleCount);

	// NOTE: Fill Simulation Variables
	m_IsLooping = isLooping;
	m_SimulateGravity = simulateGravity;
	m_SimulationSpeed = simulationSpeed;

	m_ParticleSimulationDuration = 10.f;

	m_EmissionTimer = 0.f;
	m_EmissionRateOverTime = 5u;

	// NOTE: Set Defauls for Particles
	c_ParticleSystemObject particle_system_objects = c_ParticleSystemObject(m_Transform, mass);

	m_StartDelay = 0.0f;
	m_StartLifeTime = 2.0f;
	m_StartSpeed = 1.0f;
	m_StartSize = OKVector2<float>(10.0f, 10.0f);
	m_Gravity = OKVector2<float>(0.0f, 1.0f);

	m_StartingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingSizeOverLifeTime = OKVector2<float>(5.0f, 5.0f);
	m_EndingSizeOverLifeTime = OKVector2<float>(100.0f, 100.0f);

	m_StartingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);
	m_EndingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);

	m_SimulateGravity = simulateGravity;
	particle_system_objects.particle.SimulateGravity(m_SimulateGravity);
	particle_system_objects.particle.SetScale(m_StartSize.x, m_StartSize.y);
	particle_system_objects.particle.SetRotation(0.0f);

	{
		particle_system_objects.startDelay = &m_StartDelay;
		particle_system_objects.startLifeTime = &m_StartLifeTime;

		particle_system_objects.startSpeed = &m_StartSpeed;
		particle_system_objects.startSize = &m_StartSize;
		// particle_system_objects.particle.SetGravity(m_Gravity);
		particle_system_objects.gravity = &m_Gravity;

		particle_system_objects.startingVelocityOverLifeTime = &m_StartingVelocityOverLifeTime;
		particle_system_objects.endingVelocityOverLifeTime = &m_EndingVelocityOverLifeTime;

		particle_system_objects.startingForceOverLifeTime = &m_StartingForceOverLifeTime;
		particle_system_objects.endingForceOverLifeTime = &m_EndingForceOverLifeTime;

		particle_system_objects.startingSizeOverLifeTime = &m_StartingSizeOverLifeTime;
		particle_system_objects.endingSizeOverLifeTime = &m_EndingSizeOverLifeTime;

		particle_system_objects.startingSizeBySpeed = &m_StartingSizeBySpeed;
		particle_system_objects.endingSizeBySpeed = &m_EndingSizeBySpeed;

	}

	for (unsigned int i = 0; i < m_MaxParticleCount; ++i) { m_Particles.push_back(particle_system_objects); }
}

ParticleSystem::~ParticleSystem()
{
	m_ParticleActionFunctionPtr = nullptr;
	m_ParticleSpawnAreaFunctionPtr = nullptr;

	if (!m_Particles.empty()) { m_Particles.clear(); }
	if (!m_SimulatingParticles.empty()) { m_SimulatingParticles.clear(); }
}

void ParticleSystem::Update(const float deltaTime)
{
	const float SimulationSpeedDelta = deltaTime * m_SimulationSpeed;

	// NOTE: Check if the Particles should be Looping through everything
	if (m_IsLooping == true)
	{
		// NOTE: Instead of just running it once like this, push the particles to the simulating particle vector
		if (m_SimulatingParticles.size() < m_MaxParticleCount)
		{
			// NOTE: Push particle into the simulating Vector
			// NOTE: Number of particles pushes is equal to the EmissionRateOverTimer
			m_EmissionTimer += SimulationSpeedDelta;
			if (m_EmissionTimer >= (float)(1.f / m_EmissionRateOverTime))
			{
				if (m_ParticleType == PARTICLE_TYPE_EMISSIVE)
				{
					// NOTE: Push particles to the simuatling vector
					m_SimulatingParticles.push_back(m_Particles[m_ParticleIndexIncrement]);
					CheckParticleSpawnArea(m_Transform, m_ParticleSpawnArea, m_SimulatingParticles[m_ParticleIndexIncrement]);
					CheckParticleAction(m_ParticleAction, m_SimulatingParticles[m_ParticleIndexIncrement]);
					++m_ParticleIndexIncrement;

				}
				else if (m_ParticleType == PARTICLE_TYPE_AREA)
				{
					for (int i = 0; i < m_EmissionRateOverTime; ++i)
					{
						m_SimulatingParticles.push_back(m_Particles[m_ParticleIndexIncrement]);
						CheckParticleSpawnArea(m_Transform, m_ParticleSpawnArea, m_SimulatingParticles[m_ParticleIndexIncrement]);
						CheckParticleAction(m_ParticleAction, m_SimulatingParticles[m_ParticleIndexIncrement]);
						++m_ParticleIndexIncrement;
					}
				}

				// NOTE: Reset the Particle Index Increment to 0, when equals the max particle count
				if (m_ParticleIndexIncrement >= m_MaxParticleCount) 
				{ 
					m_ParticleIndexIncrement = 0; 
				}

				// NOTE: Reset Emitter Timer
				m_EmissionTimer = 0;
			}
		}
	}
	else if (m_IsLooping == false)
	{
		// NOTE: Instead of just running it once like this, push the particles to the simulating particle vector
		// NOTE: Update Particle Constantly and based on a Timer
		m_ParticleTimer += SimulationSpeedDelta;
		if ((m_ParticleSimulationDuration >= m_ParticleTimer) && (m_SimulatingParticles.size() < m_MaxParticleCount))
		{
			// NOTE: Push particle into the simulating Vector
			// NOTE: Number of particles pushes is equal to the EmissionRateOverTimer
			m_EmissionTimer += SimulationSpeedDelta;
			if (m_EmissionTimer >= (float)(1.f / m_EmissionRateOverTime))
			{
				if (m_ParticleType == PARTICLE_TYPE_EMISSIVE)
				{
					// NOTE: Push particles to the simuatling vector
					m_SimulatingParticles.push_back(m_Particles[m_ParticleIndexIncrement]);
					CheckParticleSpawnArea(m_Transform, m_ParticleSpawnArea, m_SimulatingParticles[m_ParticleIndexIncrement]);
					CheckParticleAction(m_ParticleAction, m_SimulatingParticles[m_ParticleIndexIncrement]);
					++m_ParticleIndexIncrement;

				}
				else if (m_ParticleType == PARTICLE_TYPE_AREA)
				{
					for (int i = 0; i < m_EmissionRateOverTime; ++i)
					{
						m_SimulatingParticles.push_back(m_Particles[m_ParticleIndexIncrement]);
						CheckParticleSpawnArea(m_Transform, m_ParticleSpawnArea, m_SimulatingParticles[m_ParticleIndexIncrement]);
						CheckParticleAction(m_ParticleAction, m_SimulatingParticles[m_ParticleIndexIncrement]);
						
						++m_ParticleIndexIncrement;
					}
				}

				// NOTE: Reset the Particle Index Increment to 0, when equals the max particle count
				if (m_ParticleIndexIncrement >= m_MaxParticleCount)
				{
					m_ParticleIndexIncrement = 0;
				}

				// NOTE: Reset Emitter Timer
				m_EmissionTimer = 0;
			}
		}
	}

	// TODO: Check if particles need to be removed from the simulating particle vector
	// TODO: Might need to do the sizing in the update loop

	// Update Simulating Particles
	if (!m_SimulatingParticles.empty())
	{
		for (auto& v : m_SimulatingParticles)
		{
			CheckParticleSize(v, SimulationSpeedDelta);
			v.particle.Update(SimulationSpeedDelta);
		}
	}
	
	static float i;
	i += SimulationSpeedDelta;
	DrawText(TextFormat("Time: %f", i), 10, 10, 30, RED);
}

void ParticleSystem::Draw()
{
	if (!m_SimulatingParticles.empty())
	{
		for (auto& v : m_SimulatingParticles)
		{
			DrawRectangleV(v.particle.GetPosition().ConvertToVec2(), Vector2{100, 100}, GREEN);
			DrawRectangleV(v.particle.GetPosition().ConvertToVec2(), v.particle.GetScale().ConvertToVec2(), RED);
		}
	}

}

void ParticleSystem::CreateParticleAction(void(*particle_action_lamda)())
{
	m_ParticleActionFunctionPtr = particle_action_lamda;
}

void ParticleSystem::CreateParticleSpawnArea(void(*particle_spawn_area_lambda)())
{
	m_ParticleSpawnAreaFunctionPtr = particle_spawn_area_lambda;
}

void ParticleSystem::CheckParticleAction(ParticleAction particle_action, c_ParticleSystemObject& particle_system_object)
{
	switch (particle_action)
	{
		case PARTICLE_ACTION_NONE: ProcessActionNone(particle_system_object); break;

		case PARTICLE_ACTION_BURST_OUT: ProcessActionBurstOut(particle_system_object); break;
		case PARTICLE_ACTION_BURST_IN: ProcessActionBurstIn(particle_system_object); break;

		case PARTICLE_ACTION_SCREEN: ProcessActionScreen(particle_system_object); break;
		case PARTICLE_ACTION_SCREEN_OUT: ProcessActionScreenOut(particle_system_object); break;
		case PARTICLE_ACTION_SCREEN_IN: ProcessActionScreenIn(particle_system_object); break;

		case PARTICLE_ACTION_FALL: ProcessActionFall(particle_system_object); break;
		case PARTICLE_ACTION_RISE: ProcessActionRise(particle_system_object); break;
		case PARTICLE_ACTION_RIGHT: ProcessActionRight(particle_system_object); break;
		case PARTICLE_ACTION_LEFT: ProcessActionLeft(particle_system_object); break;

		case PARTICLE_ACTION_SPRAY: ProcessActionSpray(particle_system_object); break;
		case PARTICLE_ACTION_SPIRAL: ProcessActionSpiral(particle_system_object); break;

		case PARTICLE_ACTION_FIRE: ProcessActionFire(particle_system_object); break;
		case PARTICLE_ACTION_SMOKE: ProcessActionSmoke(particle_system_object); break;
		case PARTICLE_ACTION_SPARK: ProcessActionSpark(particle_system_object); break;
		case PARTICLE_ACTION_WAVE: ProcessActionWave(particle_system_object); break;

		case PARTICLE_ACTION_CUSTOM: ProcessActionCustom(particle_system_object); break;

		default: ProcessActionNone(particle_system_object); break;
	}
}

void ParticleSystem::CheckParticleSpawnArea(OKTransform2<float> transform, ParticleSpawnArea particle_spawn_area, c_ParticleSystemObject& particle_system_object)
{
	switch (particle_spawn_area)
	{
		case PARTICLE_SPAWN_AREA_NONE: ProcessSpawnAreaNone(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_CIRCLE: ProcessSpawnAreaCircle(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_RECTANGLE: ProcessSpawnAreaRectangle(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_CAPSULE: ProcessSpawnAreaCapsule(transform, particle_system_object); break;
		
		case PARTICLE_SPAWN_AREA_DONUT: ProcessSpawnAreaDonut(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_EDGE: ProcessSpawnAreaEdge(transform, particle_system_object); break;

		case PARTICLE_SPAWN_AREA_CUSTOM: ProcessSpawnAreaCustom(transform, particle_system_object); break;

		default: ProcessSpawnAreaNone(transform, particle_system_object); break;
	}
}

void ParticleSystem::CheckParticleSize(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	if (particle_system_object.startingSizeOverLifeTime == particle_system_object.endingSizeOverLifeTime) { return; }

	// NOTE: Calculate the sizing of the particle
	particle_system_object.currentSizeOverLifeTimer += (1.f / *particle_system_object.startLifeTime / *particle_system_object.startLifeTime) / 1000;

	// NOTE: Resize the Particle based on time
	const float tempLerpX = lerp(particle_system_object.startingSizeOverLifeTime->x, particle_system_object.endingSizeOverLifeTime->x, particle_system_object.currentSizeOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.startingSizeOverLifeTime->y, particle_system_object.endingSizeOverLifeTime->y, particle_system_object.currentSizeOverLifeTimer);

	particle_system_object.particle.SetScale(tempLerpX, tempLerpY);
}

// NOTE: Spawn Area Functions
void ParticleSystem::ProcessSpawnAreaNone(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.SetPosition(transform.position);
}

void ParticleSystem::ProcessSpawnAreaCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int theta = rand() % 360; // 360 (degrees)

	int MaxRadius = 100;
	int Min = 1;
	int Range = MaxRadius - Min + 1;
	int TotalNumber = rand() % MaxRadius + Min;
	int radius = TotalNumber;

	float PositionX = CentrePosition.x + radius * cos(theta);
	float PositionY = CentrePosition.y + radius * sin(theta);

	particle_system_object.particle.SetPosition(PositionX, PositionY);
}

void ParticleSystem::ProcessSpawnAreaRectangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int ExtentX = 100;
	int ExtentY = 100;

	int MaxX = ExtentX;
	int MinX = -ExtentX;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = ExtentY;
	int MinY = -ExtentY;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	float PositionX = CentrePosition.x + NumX;
	float PositionY = CentrePosition.y + NumY;

	particle_system_object.particle.SetPosition(PositionX, PositionY);
}

void ParticleSystem::ProcessSpawnAreaCapsule(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	float EdgeLength = 100.f;

	int MaxX = EdgeLength;
	int MinX = -EdgeLength;
	int RangeX = MaxX - MinX + 1;
	int NumY = rand() % RangeX + MinX;

	float RandYRange = CentrePosition.y + NumY;

	OKTransform2<float> temp_transform = OKTransform2<float>(OKVector2<float>(CentrePosition.x, RandYRange), OKVector2<float>(1.f, 1.f), 0);

	ProcessSpawnAreaCircle(temp_transform, particle_system_object);
}

void ParticleSystem::ProcessSpawnAreaDonut(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int theta = rand() % 360; // 360 (degrees)

	int sec_radius = 90;
	int MaxRadius = 100 - sec_radius;
	int Min = 1;

	int Range = MaxRadius - Min + 1;
	int TotalNumber = rand() % MaxRadius + Min;
	int radius = TotalNumber + sec_radius;

	float PositionX = CentrePosition.x + radius * cos(theta);
	float PositionY = CentrePosition.y + radius * sin(theta);

	particle_system_object.particle.SetPosition(PositionX, PositionY);
}

void ParticleSystem::ProcessSpawnAreaEdge(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	float EdgeLength = 100.f;

	int MaxX = EdgeLength;
	int MinX = -EdgeLength;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	float RandXRange = CentrePosition.x + NumX;

	particle_system_object.particle.SetPosition(RandXRange, CentrePosition.y);
}

void ParticleSystem::ProcessSpawnAreaCustom(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	if (m_ParticleSpawnAreaFunctionPtr != nullptr) { m_ParticleSpawnAreaFunctionPtr(); }
	else { particle_system_object.particle.SetPosition(transform.position); }
}

// NOTE: Action Functions

void ParticleSystem::ProcessActionNone(c_ParticleSystemObject& particle_system_object)
{
	// NOTE: Does Nothing
}

void ParticleSystem::ProcessActionBurstOut(c_ParticleSystemObject& particle_system_object)
{
	float MaxX = 360.0f;
	float MinX = -360.0f;
	int RangeX = MaxX - MinX + 1;
	float NumX = rand() % RangeX + MinX;

	float MaxY = 360;
	float MinY = -360;
	int RangeY = MaxY - MinY + 1;
	float NumY = rand() % RangeY + MinY;

	particle_system_object.particle.AddImpulse(NumX, NumY);
}

void ParticleSystem::ProcessActionBurstIn(c_ParticleSystemObject& particle_system_object)
{
	// SPEED = DISTANCE / TIME




}

void ParticleSystem::ProcessActionScreen(c_ParticleSystemObject& particle_system_object)
{
	int MaxX = 10;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 360;
	int MinY = -360;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	static float theta; // 360 (degrees)
	theta += GetFrameTime();

	if (theta > 360) { theta = 0; }

	float PositionX = particle_system_object.particle.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.particle.GetPosition().y + sin(theta * NumY);

	particle_system_object.particle.SetPosition(PositionX, PositionY);
}

void ParticleSystem::ProcessActionScreenOut(c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.particle.GetPosition();

	int MaxX = 10;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 360;
	int MinY = -360;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	static float theta; // 360 (degrees)
	theta += GetFrameTime();

	if (theta > 360) { theta = 0; }

	float PositionX = particle_system_object.particle.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.particle.GetPosition().y + sin(theta * NumY);

	particle_system_object.particle.SetPosition(PositionX, PositionY);
	particle_system_object.particle.AddImpulse(-DistanceParticle.x, -DistanceParticle.y);

	// Pulsing
	// particle_system_object.particle.AddImpulse(DistanceParticle);
}

void ParticleSystem::ProcessActionScreenIn(c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.particle.GetPosition();

	int MaxX = 10;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 360;
	int MinY = -360;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	static float theta; // 360 (degrees)
	theta += GetFrameTime();

	if (theta > 360) { theta = 0; }

	float PositionX = particle_system_object.particle.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.particle.GetPosition().y + sin(theta * NumY);

	particle_system_object.particle.SetPosition(PositionX, PositionY);
	particle_system_object.particle.AddImpulse(DistanceParticle.x * 2, DistanceParticle.y * 2);
}

void ParticleSystem::ProcessActionFall(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.AddImpulse(0, 1);
}

void ParticleSystem::ProcessActionRise(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.AddImpulse(0, -1);
}

void ParticleSystem::ProcessActionRight(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.AddImpulse(1, 0);
}

void ParticleSystem::ProcessActionLeft(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.particle.AddImpulse(-1, 0);
}

// TODO:
void ParticleSystem::ProcessActionSpray(c_ParticleSystemObject& particle_system_object)
{
	// Add some functionality to spray it in a certain direction dependant on the dot product angle 







	particle_system_object.particle.AddImpulse(-1, 0);
}

void ParticleSystem::ProcessActionSpiral(c_ParticleSystemObject& particle_system_object)
{

}

void ParticleSystem::ProcessActionFire(c_ParticleSystemObject& particle_system_object)
{
	int MaxX = 10;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	static float theta; // 360 (degrees)
	theta += GetFrameTime();

	if (theta > 360) { theta = 0; }

	float MaxY = 1;
	float MinY = 0;
	float RangeY = MaxY - MinY + 1;
	float NumY = rand() % RangeX + MinX;

	float PositionX = particle_system_object.particle.GetPosition().x + cos(theta);
	particle_system_object.particle.AddImpulse(0, -NumY);
	particle_system_object.particle.SetPosition(PositionX, particle_system_object.particle.GetPosition().y);
}

void ParticleSystem::ProcessActionSmoke(c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.particle.GetPosition();

	int MaxX = 100;
	int MinX = -100;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 100;
	int MinY = -100;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	float DistanceProjectionX = DistanceParticle.x * 10;
	float DistanceProjectionY = DistanceParticle.y * 10;

	float PositionX = lerp(particle_system_object.particle.GetPosition().x, DistanceProjectionX, 0.5);
	float PositionY = lerp(particle_system_object.particle.GetPosition().y, DistanceProjectionY, 0.5);

	particle_system_object.particle.AddImpulse(NumX, NumY);
}

void ParticleSystem::ProcessActionSpark(c_ParticleSystemObject& particle_system_object)
{
	int MaxX = 360;
	int MinX = -360;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 360;
	int MinY = -360;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	particle_system_object.particle.AddImpulse(NumX, NumY);
}

// TODO: Fix This	
void ParticleSystem::ProcessActionWave(c_ParticleSystemObject& particle_system_object)
{

	particle_system_object.particle.SetPosition(particle_system_object.particle.GetPosition().x, particle_system_object.particle.GetPosition().y);
	//particle_system_object.particle.AddImpulse(0, NumY);
}

void ParticleSystem::ProcessActionCustom(c_ParticleSystemObject& particle_system_object)
{
	if (m_ParticleActionFunctionPtr != nullptr) { m_ParticleActionFunctionPtr(); }
}


