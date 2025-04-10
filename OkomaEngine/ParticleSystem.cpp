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
	m_Particles.reserve(m_MaxParticleCount);

	m_ParticleSpawnArea = particleSpawnArea;
	m_ParticleAction = particleAction;
	// m_SimulateParticles.reserve(m_MaxParticleCount);

	// NOTE: Fill Simulation Variables
	m_IsLooping = isLooping;
	m_SimulateGravity = simulateGravity;
	m_SimulationSpeed = simulationSpeed;

	m_Duration = 10.f;

	m_EmissionRateOverTime = 5u;
	m_EmissionRateOverDistance = 0u;

	// NOTE: Set Defauls for Particles
	c_ParticleSystemObject particle_system_objects = c_ParticleSystemObject(m_Transform, mass);
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

	for (unsigned int i = 0; i < m_MaxParticleCount; ++i) { m_Particles.push_back(particle_system_objects); }



}

ParticleSystem::~ParticleSystem()
{
	m_ParticleActionFunctionPtr = nullptr;
	m_ParticleSpawnAreaFunctionPtr = nullptr;
	if (!m_Particles.empty()) { m_Particles.clear(); }
}

void ParticleSystem::Update(const float deltaTime)
{
	(*const_cast<float*>(&deltaTime)) *= 0.1f;

	// NOTE: Check if the Particles should be Looping through everything
	if (m_IsLooping == false)
	{
		// NOTE: Execute this Once and only once
		if (m_IsExecuted == false)
		{
			for (auto& v : m_Particles)
			{
				CheckParticleSpawnArea(m_Transform, m_ParticleSpawnArea, v);
				CheckParticleAction(m_ParticleAction, v);
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
		DrawRectangleV(v.particle.GetPosition().ConvertToVec2(), OKVector2<float>(10.f, 10.f).ConvertToVec2(), RED);
		// DrawCircleV(v.particle.GetPosition().ConvertToVec2(), 10, RED);
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
		case PARTICLE_SPAWN_AREA_HALF_CIRCLE: ProcessSpawnAreaCircle(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_RECTANGLE: ProcessSpawnAreaRectangle(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_TRIANGLE: ProcessSpawnAreaTriangle(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_CAPSULE: ProcessSpawnAreaCapsule(transform, particle_system_object); break;
		
		case PARTICLE_SPAWN_AREA_DONUT: ProcessSpawnAreaDonut(transform, particle_system_object); break;
		case PARTICLE_SPAWN_AREA_EDGE: ProcessSpawnAreaEdge(transform, particle_system_object); break;

		case PARTICLE_SPAWN_AREA_CUSTOM: ProcessSpawnAreaCustom(transform, particle_system_object); break;

		default: ProcessSpawnAreaNone(transform, particle_system_object); break;
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

// CHECK THIS: Fix this Function
void ParticleSystem::ProcessSpawnAreaHalfCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	const OKVector2<float> CentrePosition = transform.position;

	float radius = 100;
	
	// NOTE: X Position of the New Area	
	int MaxX = 100;
	int MinX = 1;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	float RandXRange = CentrePosition.x + NumX;

	// NOTE: Y Position of the New Area
	int theta = rand() % 360; // 360 (degrees)
	float PositionY = CentrePosition.y + radius * sin(theta); // TODO: Replace the sin wave with the dot product

	particle_system_object.particle.SetPosition(RandXRange, PositionY);
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

void ParticleSystem::ProcessSpawnAreaTriangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	// NOTE: Triangle Height
	// 180 Angles of a Triangle
	// Height
	// + Half Height
	// 
	float TriangleHeight = 100.f;

	// NOTE: Work out the base of the Triangle
	int MaxX = TriangleHeight;
	int MinX = 0;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;
	float RandXRange = CentrePosition.x + NumX;
	float RandCopy = CentrePosition.x + NumX;

	// NOTE: Work out the Height of the triangle

	int MaxY = TriangleHeight * 3;
	int MinY = 0;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	float Line_Start_X = MaxX + CentrePosition.x;
	float Line_End_X = MinX + CentrePosition.x;
	float ClampRanged = Clamp(RandXRange, Line_End_X, Line_Start_X);
	float LerpValue = remap(ClampRanged, Line_Start_X, Line_End_X);
	float LerpY = lerp(CentrePosition.y, TriangleHeight + NumY, LerpValue);

	particle_system_object.particle.SetPosition(RandCopy, LerpY);
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

void ParticleSystem::ProcessActionSpray(c_ParticleSystemObject& particle_system_object)
{
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

void ParticleSystem::ProcessActionWave(c_ParticleSystemObject& particle_system_object)
{

}

void ParticleSystem::ProcessActionCustom(c_ParticleSystemObject& particle_system_object)
{
	if (m_ParticleActionFunctionPtr != nullptr) { m_ParticleActionFunctionPtr(); }
}


