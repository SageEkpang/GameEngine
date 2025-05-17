#include "ParticleEffectComponent.h"

ParticleEffectComponent::ParticleEffectComponent()
{
	m_CheckParticleActionFunctionPtr = nullptr;
	m_CheckParticleSpawnFunctionPtr = nullptr;
	m_CheckParticleResizingFunctionPtr = nullptr;
	m_CheckParticlePhysicsOverTimeFunctionPtr = nullptr;
	m_CheckParticleColourOverTimerFunctionPtr = nullptr;

	m_EmissionRateOverTime = 0u;
	m_IsLooping = false;
	m_MaxParticleCount = 0u;

	m_MaxVelocityByColour = 0.f;
	m_MaxVelocityBySize = 0.f;

	m_MinVelocityByColour = 0.f;
	m_MinVelocityBySize = 0.f;

	m_ParticleAction = PARTICLE_ACTION_NONE;
	m_ParticleEmitterType = PARTICLE_EMITTER_TYPE_SINGLE;
	m_ParticleIndexIncrement = 0u;
	m_ParticleSpawnArea = PARTICLE_SPAWN_AREA_NONE;

	m_ParticleTimer = 0.f;
	m_ParticleSimulationDuration = 0.f;
	m_SimulateGravity = false;
	m_SimulationSpeed = 0.f;
	m_StartDelay = 0.f;
	m_StartSpeed = 0.f;
	m_StartLifeTime = 0.f;


}

ParticleEffectComponent::ParticleEffectComponent(OKVector2<float> position, unsigned int maxParticleCount, ParticleEmitterType particleEmitterType, ParticleSpawnArea particleSpawnArea, ParticleAction particleAction, float mass, bool isLooping, float simulationSpeed, bool simulateGravity)
{
	// NOTE: Init Timer to NULL for random function
	srand((unsigned int)time(NULL));

	// NOTE: Init Velocity Variables
	m_MaxVelocityByColour = 0.f;
	m_MinVelocityByColour = 0.f;

	m_MaxVelocityBySize = 0.f;
	m_MinVelocityBySize = 0.f;

	// NOTE: Set Transform
	m_Transform = OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);
	m_EmitterPositionOffset = OKVector2<float>();

	// NOTE: Fill Vector and reserve the set size for the particles
	m_MaxParticleCount = maxParticleCount;
	m_Particles.reserve(m_MaxParticleCount);
	m_SimulatingParticles.reserve(m_MaxParticleCount);

	// NOTE: Fill Simulation & Particle Variables
	m_IsLooping = isLooping;
	m_SimulateGravity = simulateGravity;
	m_SimulationSpeed = simulationSpeed;
	m_ParticleSpawnArea = particleSpawnArea;
	m_ParticleAction = particleAction;
	m_ParticleEmitterType = particleEmitterType;

	// NOTE: Particle Timer and Incremet Variables
	m_ParticleTimer = 0.0f;
	m_ParticleIndexIncrement = 0u;
	m_ParticleSimulationDuration = 5.f;

	m_EmissionTimer = 0.f;
	m_EmissionRateOverTime = 1u;

	#pragma region Particle System Pointer Functions

		// NOTE: PARTICLE SPAWN MAP INIT AND ASSIGNMENT

		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_NONE] = &ParticleEffectComponent::ProcessSpawnAreaNone;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CIRCLE] = &ParticleEffectComponent::ProcessSpawnAreaCircle;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE] = &ParticleEffectComponent::ProcessSpawnAreaRectangle;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE] = &ParticleEffectComponent::ProcessSpawnAreaCapsule;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_DONUT] = &ParticleEffectComponent::ProcessSpawnAreaDonut;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_EDGE] = &ParticleEffectComponent::ProcessSpawnAreaEdge;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CUSTOM] = &ParticleEffectComponent::ProcessSpawnAreaCustom;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_SPRAY] = &ParticleEffectComponent::ProcessSpawnAreaSpray;

		m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[m_ParticleSpawnArea];


		// NOTE: PARTICLE ACTION MAP INIT AND ASSIGNMENT

		m_ParticleActionMap[PARTICLE_ACTION_NONE] = &ParticleEffectComponent::ProcessActionNone;
		m_ParticleActionMap[PARTICLE_ACTION_BURST_OUT] = &ParticleEffectComponent::ProcessActionBurstOut;
		m_ParticleActionMap[PARTICLE_ACTION_BURST_IN] = &ParticleEffectComponent::ProcessActionBurstIn;

		m_ParticleActionMap[PARTICLE_ACTION_SCREEN] = &ParticleEffectComponent::ProcessActionScreen;
		m_ParticleActionMap[PARTICLE_ACTION_SCREEN_OUT] = &ParticleEffectComponent::ProcessActionScreenOut;
		m_ParticleActionMap[PARTICLE_ACTION_SCREEN_IN] = &ParticleEffectComponent::ProcessActionScreenIn;

		m_ParticleActionMap[PARTICLE_ACTION_FALL] = &ParticleEffectComponent::ProcessActionFall;
		m_ParticleActionMap[PARTICLE_ACTION_RISE] = &ParticleEffectComponent::ProcessActionRise;
		m_ParticleActionMap[PARTICLE_ACTION_RIGHT] = &ParticleEffectComponent::ProcessActionRight;
		m_ParticleActionMap[PARTICLE_ACTION_LEFT] = &ParticleEffectComponent::ProcessActionLeft;

		m_ParticleActionMap[PARTICLE_ACTION_SPRAY] = &ParticleEffectComponent::ProcessActionSpray;

		m_ParticleActionMap[PARTICLE_ACTION_FIRE] = &ParticleEffectComponent::ProcessActionFire;
		m_ParticleActionMap[PARTICLE_ACTION_SMOKE] = &ParticleEffectComponent::ProcessActionSmoke;
		m_ParticleActionMap[PARTICLE_ACTION_SPARK] = &ParticleEffectComponent::ProcessActionSpark;

		m_ParticleActionMap[PARTICLE_ACTION_CUSTOM] = &ParticleEffectComponent::ProcessActionCustom;

		m_CheckParticleActionFunctionPtr = m_ParticleActionMap[m_ParticleAction];


		// NOTE: PARTICLE RESIZING VARIABLE(s)
		// m_ParticleResizeMap[PARTICLE_RESIZE_NONE] = nullptr; // TODO: Can change this to a nullptr reference instead of a function pointer, can remove the 
		m_ParticleResizeMap[PARTICLE_RESIZE_NONE] = &ParticleEffectComponent::ProcessResizeNone;
		m_ParticleResizeMap[PARTICLE_RESIZE_OVER_LIFETIME] = &ParticleEffectComponent::ProcessResizeOverLifeTime;
		m_ParticleResizeMap[PARTICLE_RESIZE_VELOCITY] = &ParticleEffectComponent::ProcessResizeVelocity;

		m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_NONE];


		// NOTE: PARTICLE PHYSICS FORCE OVER TIME
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_NONE] = &ParticleEffectComponent::ProcessPhysicsOverLifeTimeNone;
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_FORCE_OVER_LIFETIME] = &ParticleEffectComponent::ProcessPhysicsOverLifeTimeForce;
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_VELOCITY_OVER_LIFETIME] = &ParticleEffectComponent::ProcessPhysicsOverLifeTimeVelocity;

		m_CheckParticlePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_NONE];


		// NOTE: PARTICLE COLOUR OVER TIME VARIABLE(s)
		m_ParticleColourOverTimerMap[PARTICLE_COLOUR_NONE] = &ParticleEffectComponent::ProcessColourNone;
		m_ParticleColourOverTimerMap[PARTICLE_COLOUR_OVER_LIFE_TIME] = &ParticleEffectComponent::ProcessColourOverLifeTime;
		m_ParticleColourOverTimerMap[PARTICLE_COLOUR_VELOCITY_OVER_LIFE_TIME] = &ParticleEffectComponent::ProcessColourOverVelocity;

		m_CheckParticleColourOverTimerFunctionPtr = m_ParticleColourOverTimerMap[PARTICLE_COLOUR_NONE];

	#pragma endregion

	#pragma region Particle System Object Inits

	m_StartDelay = 0.0f;
	m_StartLifeTime = 1.0f;
	m_StartSpeed = 1.0f;
	m_StartSize = OKVector2<float>(5.0f, 5.0f);
	m_Gravity = OKVector2<float>(0.0f, 750.0f);

	m_StartingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingColourOverLifeTime = OKVector3<unsigned int>(255, 255, 255);
	m_StartingColourOverLifeTime = OKVector3<unsigned int>(255, 255, 255);

	m_StartingSizeOverLifeTime = m_StartSize;
	m_EndingSizeOverLifeTime = m_StartSize;

	m_StartingSizeByVelocity = m_StartSize;
	m_EndingSizeByVelocity = m_StartSize;

	// NOTE: Set Defauls for Particles
	for (unsigned int i = 0; i < m_MaxParticleCount; ++i) 
	{ 
		OKTransform2<float>* transform = new OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);
		ParticleEffectObject* particle_system_objects = new ParticleEffectObject(position, mass);

		particle_system_objects->SimulateGravity(m_SimulateGravity);
		particle_system_objects->SetGravity(m_Gravity);

		particle_system_objects->m_Scale = (m_StartSize.x, m_StartSize.y);
		particle_system_objects->m_Rotation = 0.f;

		particle_system_objects->m_StartDelay = &m_StartDelay;
		particle_system_objects->m_StartLifeTime = &m_StartLifeTime;
		particle_system_objects->m_CurrentLifeTime = 0;

		particle_system_objects->m_StartSpeed = &m_StartSpeed;
		particle_system_objects->m_StartSize = &m_StartSize;

		particle_system_objects->m_StartingVelocityOverLifeTime = &m_StartingVelocityOverLifeTime;
		particle_system_objects->m_EndingVelocityOverLifeTime = &m_EndingVelocityOverLifeTime;

		particle_system_objects->m_StartingForceOverLifeTime = &m_StartingForceOverLifeTime;
		particle_system_objects->m_EndingForceOverLifeTime = &m_EndingForceOverLifeTime;

		particle_system_objects->m_StartingSizeOverLifeTime = &m_StartingSizeOverLifeTime;
		particle_system_objects->m_EndingSizeOverLifeTime = &m_EndingSizeOverLifeTime;

		particle_system_objects->m_StartingSizeByVelocity = &m_StartingSizeByVelocity;
		particle_system_objects->m_EndingSizeByVelocity = &m_EndingSizeByVelocity;

		particle_system_objects->m_StartingColourOverLifeTime = &m_StartingColourOverLifeTime;
		particle_system_objects->m_EndingColourOverLifeTime = &m_EndingColourOverLifeTime;

		m_Particles.push_back(particle_system_objects);
	}

	#pragma endregion
}

ParticleEffectComponent::~ParticleEffectComponent()
{
	m_CustomParticleActionFunctionPtr = nullptr;
	m_CustomParticleSpawnAreaFunctionPtr = nullptr;

	m_CheckParticleActionFunctionPtr = nullptr;
	m_CheckParticleSpawnFunctionPtr = nullptr;
	m_CheckParticleResizingFunctionPtr = nullptr;
	m_CheckParticlePhysicsOverTimeFunctionPtr = nullptr;
	m_CheckParticleColourOverTimerFunctionPtr = nullptr;

	if (!m_Particles.empty()) { m_Particles.clear(); }
	if (!m_SimulatingParticles.empty()) { m_SimulatingParticles.clear(); }
}

void ParticleEffectComponent::Update(const float deltaTime)
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
				ProcessParticleToSimulatingParticles();
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
				ProcessParticleToSimulatingParticles();
			}
		}
	}

	// NOTE: Executes the Particle Effect Once only when there is a particle in there (Best Used for Multiple Particles)
	if (m_ExecuteOnce == true && !m_SimulatingParticles.empty())
	{
		m_ParticleTimer = m_ParticleSimulationDuration;
	}

	// NOTE: Update Simulating Particles
	// NOTE: Delete the particles that need to be deleted after lifetime

	#pragma region Updating_and_Deleting_Particles

	if (!m_SimulatingParticles.empty())
	{
		for (auto itr = m_SimulatingParticles.begin(); itr != m_SimulatingParticles.end();)
		{
			// NOTE: Check the particle life time and update the "life time" within the particle
			CheckParticleLifeTime(*itr, SimulationSpeedDelta);

			if ((*itr).m_CurrentLifeTime <= 0.0f)
			{
				// NOTE: Remove element at array index depending on if it reaches the lifetime 
				itr = m_SimulatingParticles.erase(itr);
			}
			else
			{
				// NOTE: Iterate through vector
				// NOTE: Process the Particle Sizing, Velocity and Force Values (has to be here to properly update at the same time as the other particles)
				(this->*m_CheckParticleResizingFunctionPtr)(*itr, SimulationSpeedDelta);
				(this->*m_CheckParticlePhysicsOverTimeFunctionPtr)(*itr, SimulationSpeedDelta);
				(this->*m_CheckParticleColourOverTimerFunctionPtr)(*itr, SimulationSpeedDelta);
				(*itr).Update(SimulationSpeedDelta);
				++itr;
			}
		}
	}

	#pragma endregion

	static float SimpleCounter;
	SimpleCounter += SimulationSpeedDelta;
	DrawText(TextFormat("Timer: %f", SimpleCounter), 10, 10, 40, GREEN);

}

void ParticleEffectComponent::Draw()
{
	if (!m_SimulatingParticles.empty())
	{
		for (auto& v : m_SimulatingParticles)
		{
			Color tempColour = {v.m_Colour.x, v.m_Colour.y, v.m_Colour.z, 255.f};
			DrawRectangleV(v.GetPosition().ConvertToVec2(), v.m_Scale.ConvertToVec2(), tempColour);
		}
	}
}

void ParticleEffectComponent::PrefabFire()
{
	AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
	AssignParticleAction(PARTICLE_ACTION_BURST_OUT);
	AssignParticleSpawnAreaCircle(40.f);
	AssignParticleAction(PARTICLE_ACTION_SPRAY);
	SetLooping(true);
	SetEmissionRateOverTime(500u);
	SetDuration(0.5f);
	SetStartSpeed(5.0);
	SetStartSpeed(1.0);
	SetStartLifeTime(1.0f);
	AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
	AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
	AssignColourOverLifeTime(OKVector3<unsigned int>(255, 255, 0), OKVector3<unsigned int>(255, 0, 0));
	AssignResizeOverLifeTime(OKVector2<float>(20.f, 20.f), OKVector2<float>(1.f, 1.f));
}

void ParticleEffectComponent::PrefabSmoke()
{
	AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
	AssignParticleSpawnAreaCircle(40.f);
	SetLooping(true);
	SetEmissionRateOverTime(5u);
	SetDuration(0.5f);
	SetStartLifeTime(6.0f);
	AssignVelocityOverLifeTime(OKVector2<float>(0.f, -50.f), OKVector2<float>(0.f, -100.f));
	AssignColourOverLifeTime(OKVector3<unsigned int>(200, 200, 200), OKVector3<unsigned int>(50, 50, 50));
	AssignResizeOverLifeTime(OKVector2<float>(20.f, 20.f), OKVector2<float>(5.f, 5.f));
}

void ParticleEffectComponent::ProcessParticleToSimulatingParticles()
{
	unsigned int tempParticleAmount = 0;
	if (m_ParticleEmitterType == PARTICLE_EMITTER_TYPE_SINGLE) { tempParticleAmount = 1; }
	if (m_ParticleEmitterType == PARTICLE_EMITTER_TYPE_MULTIPLE) { tempParticleAmount = m_EmissionRateOverTime; }

	// NOTE: Loop through the amount of particles you want
	for (unsigned int i = 0; i < tempParticleAmount; ++i)
	{
		// NOTE: Push particles to the simuatling vector
		m_SimulatingParticles.push_back(*m_Particles[m_ParticleIndexIncrement]);

		// NOTE: Get the last particle that was inserted in the list and update that, assuming that is the particle that needs to be updated
		std::vector<ParticleEffectObject>::iterator itr = m_SimulatingParticles.end() - 1;

		// NOTE: Set Variables for the Particle
		(*itr).m_CurrentLifeTime = m_StartLifeTime;
		(*itr).SimulateGravity(m_SimulateGravity);
		(*itr).SetGravity(m_Gravity);

		(this->*m_CheckParticleSpawnFunctionPtr)(m_Transform, *itr);
		(this->*m_CheckParticleActionFunctionPtr)(*itr);
		++m_ParticleIndexIncrement;
	}

	// NOTE: Reset the Particle Index Increment to 0, when equals the max particle count
	if (m_ParticleIndexIncrement > m_MaxParticleCount - 1) { m_ParticleIndexIncrement = 0; }

	// NOTE: Reset Emitter Timer
	m_EmissionTimer = 0;
}

void ParticleEffectComponent::CreateParticleAction(void(*particle_action_lamda)())
{
	m_CustomParticleActionFunctionPtr = particle_action_lamda;
}

void ParticleEffectComponent::AssignParticleSpawnAreaNone()
{
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_NONE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaCircle(float radius)
{
	m_CircleRadius = radius;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CIRCLE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaRectangle(float width, float height)
{
	m_RectangleScale.x = width;
	m_RectangleScale.y = height;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaRectangle(OKVector2<float> scale)
{
	m_RectangleScale = scale;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaCapsule(float width, float height)
{
	m_CapsuleWidth = width;
	m_CapsuleHeight = height;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaCapsule(OKVector2<float> scale)
{
	m_CapsuleWidth = scale.x;
	m_CapsuleHeight = scale.y;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaDonut(float outer_circle_radius, float inner_circle_radius)
{
	m_OuterDonutScale = outer_circle_radius;
	m_InnerDonutScale = inner_circle_radius;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_DONUT];
}

void ParticleEffectComponent::AssignParticleSpawnAreaEdge(float m_edge_length)
{
	m_EdgeLength = m_edge_length;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_EDGE];
}

void ParticleEffectComponent::AssignParticleSpawnAreaSpray(float spray_angle, float spray_length, OKVector2<float> spray_direction)
{
	m_SprayAngle = spray_angle;
	m_SprayLength = spray_length;
	m_SprayDirection = spray_direction;

	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_SPRAY];
}

void ParticleEffectComponent::AssignParticleSpawnAreaCustom()
{
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CUSTOM];
}

void ParticleEffectComponent::AssignParticleAction(ParticleAction particle_action)
{
	m_CheckParticleActionFunctionPtr = m_ParticleActionMap[particle_action];
}


void ParticleEffectComponent::AssignParticleEmitterType(ParticleEmitterType particle_emitter_type)
{
	m_ParticleEmitterType = particle_emitter_type;
}


void ParticleEffectComponent::CheckParticleLifeTime(ParticleEffectObject& particle_system_object, float deltaTime)
{
	particle_system_object.m_CurrentLifeTime -= deltaTime;
}

void ParticleEffectComponent::CreateParticleSpawnArea(void(*particle_spawn_area_lambda)())
{
	m_CustomParticleSpawnAreaFunctionPtr = particle_spawn_area_lambda;
}

// NOTE: Spawn Area Functions
void ParticleEffectComponent::ProcessSpawnAreaNone(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	particle_system_object.SetPosition(transform.position);
}

void ParticleEffectComponent::ProcessSpawnAreaCircle(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int theta = rand() % 360; // 360 (degrees)

	int MaxRadius = m_CircleRadius;
	int Min = 1;
	int Range = MaxRadius - Min + 1;
	int TotalNumber = rand() % MaxRadius + Min;
	float radius = TotalNumber;

	float PositionX = CentrePosition.x + radius * cos(theta);
	float PositionY = CentrePosition.y + radius * sin(theta);

	particle_system_object.SetPosition(PositionX, PositionY);
}

void ParticleEffectComponent::ProcessSpawnAreaRectangle(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	const int ExtentX = m_RectangleScale.x;
	const int ExtentY = m_RectangleScale.y;

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

	particle_system_object.SetPosition(PositionX, PositionY);
}

void ParticleEffectComponent::ProcessSpawnAreaCapsule(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	float EdgeLength = m_CapsuleHeight;

	int MaxX = EdgeLength;
	int MinX = -EdgeLength;
	int RangeX = MaxX - MinX + 1;
	int NumY = rand() % RangeX + MinX;

	float RandYRange = CentrePosition.y + NumY;

	OKTransform2<float> temp_transform = OKTransform2<float>(OKVector2<float>(CentrePosition.x, RandYRange), OKVector2<float>(m_CapsuleWidth, m_CapsuleWidth), 0);

	ProcessSpawnAreaCircle(temp_transform, particle_system_object);
}

void ParticleEffectComponent::ProcessSpawnAreaDonut(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	int theta = rand() % 360; // 360 (degrees)

	int sec_radius = m_InnerDonutScale;
	int MaxRadius = m_OuterDonutScale - sec_radius;
	int Min = 1;

	int Range = MaxRadius - Min + 1;
	int TotalNumber = rand() % MaxRadius + Min;
	int radius = TotalNumber + sec_radius;

	float PositionX = CentrePosition.x + radius * cos(theta);
	float PositionY = CentrePosition.y + radius * sin(theta);

	particle_system_object.SetPosition(PositionX, PositionY);
}

void ParticleEffectComponent::ProcessSpawnAreaEdge(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	float EdgeLength = 100.f;

	int MaxX = EdgeLength;
	int MinX = -EdgeLength;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	float RandXRange = CentrePosition.x + NumX;

	particle_system_object.SetPosition(RandXRange, CentrePosition.y);
}

void ParticleEffectComponent::ProcessSpawnAreaCustom(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	if (m_CustomParticleSpawnAreaFunctionPtr != nullptr) { m_CustomParticleSpawnAreaFunctionPtr(); }
	else { particle_system_object.SetPosition(transform.position); }
}

// NOTE: This may or may not work
void ParticleEffectComponent::ProcessSpawnAreaSpray(OKTransform2<float> transform, ParticleEffectObject& particle_system_object)
{
	OKVector2<float> CentrePosition = transform.position;

	// NOTE: Get the Direction you want the Spray to go in
	const float t_spray_length = m_SprayLength;
	OKVector2<float> Direction = OKVector2<float>((m_SprayDirection.normalise().x * m_SprayLength), (m_SprayDirection.normalise().y * m_SprayLength));

	// NOTE: Working out the Maxmium and Minimum range of the spray line
	int MaxX = Direction.x + CentrePosition.x;
	int MinX = CentrePosition.x;

	int MaxY = Direction.y + CentrePosition.y;
	int MinY = CentrePosition.y;

	// NOTE: Randomise the Lerp Range
	int RandXMax = MaxX;
	int RandXMin = MinX;
	int RandomisingRangeX = RandXMax - RandXMin + 1;
	int NumX = rand() % RandomisingRangeX + RandXMin;

	int RandYMax = MaxY;
	int RandYMin = MinY;
	int RandomisingRangeY = RandYMax - RandYMin + 1;
	int NumY = rand() % RandomisingRangeY + RandYMin;

	// NOTE: Remapping the spray line to a range of 0.f - 1.f for linear interp
	float NewRangeX = remap(NumX, MinX, MaxX);
	float NewRangeY = remap(NumY, MinY, MaxY);

	float thing = remap(NewRangeX, 0, 1, MinX, MaxX);

	// NOTE: Random Lerp Range between the values
	float LerpXRange = lerp(CentrePosition.x, t_spray_length + CentrePosition.x, NewRangeX);
	float LerpYRange = lerp(CentrePosition.y, t_spray_length + CentrePosition.y, NewRangeY);

	// NOTE: Setting Position
	particle_system_object.SetPosition(CentrePosition.x, LerpYRange);
}

// NOTE: Resizing Functions
void ParticleEffectComponent::ProcessResizeNone(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Do nothing
}

void ParticleEffectComponent::ProcessResizeOverLifeTime(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if you sizes are the same, meaning this code does not have to be ran
	if (particle_system_object.m_StartingSizeOverLifeTime == particle_system_object.m_EndingSizeOverLifeTime) { return; }

	// NOTE: Calculate the sizing of the particle
	// NOTE: Might need to divide some things my the startlife time 
	particle_system_object.m_CurrentSizeOverLifeTimer += *particle_system_object.m_StartLifeTime / (*particle_system_object.m_StartLifeTime * *particle_system_object.m_StartLifeTime) * deltaTime;

	// NOTE: Resize the Particle based on time
	const float tempLerpX = lerp(particle_system_object.m_StartingSizeOverLifeTime->x, particle_system_object.m_EndingSizeOverLifeTime->x, particle_system_object.m_CurrentSizeOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingSizeOverLifeTime->y, particle_system_object.m_EndingSizeOverLifeTime->y, particle_system_object.m_CurrentSizeOverLifeTimer);

	// NOTE: Assign the resize to the scale of the current particle
	particle_system_object.m_Scale = OKVector2<float>(tempLerpX, tempLerpY);
}

void ParticleEffectComponent::ProcessResizeVelocity(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if you sizes are the same, meaning this code does not have to be ran
	if (particle_system_object.m_StartingSizeByVelocity == particle_system_object.m_EndingSizeByVelocity) { return; }

	// NOTE: Calculate the sizing of the particle (Velocity resizing calculation)
	particle_system_object.m_CurrentSizeByVelocity = particle_system_object.GetVelocity().magnitude();

	const float MagMax = m_MaxVelocityBySize;
	const float MagMin = m_MinVelocityBySize;

	// NOTE: Calculate the remapping range of Velocity via the Magnitude
	const float tempRemapValue = remap(particle_system_object.m_CurrentSizeByVelocity, MagMin, MagMax, 0, 1);
	
	// NOTE: Resize the particle based on time 
	const float tempLerpX = lerp(particle_system_object.m_StartingSizeByVelocity->x, particle_system_object.m_EndingSizeOverLifeTime->x, tempRemapValue);
	const float tempLerpY = lerp(particle_system_object.m_StartingSizeByVelocity->y, particle_system_object.m_EndingSizeOverLifeTime->y, tempRemapValue);

	// NOTE: Assign the resize to the scale of the current particle
	particle_system_object.m_Scale = OKVector2<float>(tempLerpX, tempLerpY);
}

void ParticleEffectComponent::ProcessPhysicsOverLifeTimeNone(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: No Functionality
}

void ParticleEffectComponent::ProcessPhysicsOverLifeTimeForce(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if the force over life time is the same, if it is, skip it
	if (particle_system_object.m_StartingForceOverLifeTime == particle_system_object.m_EndingForceOverLifeTime) { return; }

	// NOTE: Calculating the force over time particle
	particle_system_object.m_CurrentForceOverLifeTimer += *particle_system_object.m_StartLifeTime / (*particle_system_object.m_StartLifeTime * *particle_system_object.m_StartLifeTime) * deltaTime;

	// NOTE: Force over time lerping
	const float tempLerpX = lerp(particle_system_object.m_StartingForceOverLifeTime->x, particle_system_object.m_EndingForceOverLifeTime->x, particle_system_object.m_CurrentForceOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingForceOverLifeTime->y, particle_system_object.m_EndingForceOverLifeTime->y, particle_system_object.m_CurrentForceOverLifeTimer);
	
	// NOTE: Assign the force over time of the current particle
	particle_system_object.SetForce(OKVector2<float>(tempLerpX, tempLerpY));
}

void ParticleEffectComponent::ProcessPhysicsOverLifeTimeVelocity(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if the velocity over life time is the same
	if (particle_system_object.m_StartingVelocityOverLifeTime == particle_system_object.m_EndingVelocityOverLifeTime) { return; }

	// NOTE: Calculating the velocity over time particle
	particle_system_object.m_CurrentVelocityOverLifeTimer += *particle_system_object.m_StartLifeTime / (*particle_system_object.m_StartLifeTime * *particle_system_object.m_StartLifeTime) * deltaTime;

	// NOTE: Force over time lerping
	const float tempLerpX = lerp(particle_system_object.m_StartingVelocityOverLifeTime->x, particle_system_object.m_EndingVelocityOverLifeTime->x, particle_system_object.m_CurrentVelocityOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingVelocityOverLifeTime->y, particle_system_object.m_EndingVelocityOverLifeTime->y, particle_system_object.m_CurrentVelocityOverLifeTimer);

	// NOTE: Assign the force over time of the current particle
	particle_system_object.SetVelocity(OKVector2<float>(tempLerpX, tempLerpY));
}

void ParticleEffectComponent::ProcessColourNone(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Do nothing
}

// FIXME: just use a similar way of resize velocity function
void ParticleEffectComponent::ProcessColourOverLifeTime(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if the colour over life time is the same, if it is, skip it
	if (particle_system_object.m_StartingColourOverLifeTime == particle_system_object.m_EndingColourOverLifeTime) { return; }
	
	// NOTE: Calculating the colour over life time for particle
	particle_system_object.m_CurrentColourOverLifeTimer += *particle_system_object.m_StartLifeTime / (*particle_system_object.m_StartLifeTime * *particle_system_object.m_StartLifeTime) * deltaTime;
	
	// NOTE: Force over time lerping
	const float tempLerpX = lerp(particle_system_object.m_StartingColourOverLifeTime->x, particle_system_object.m_EndingColourOverLifeTime->x, particle_system_object.m_CurrentColourOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingColourOverLifeTime->y, particle_system_object.m_EndingColourOverLifeTime->y, particle_system_object.m_CurrentColourOverLifeTimer);
	const float tempLerpZ = lerp(particle_system_object.m_StartingColourOverLifeTime->z, particle_system_object.m_EndingColourOverLifeTime->z, particle_system_object.m_CurrentColourOverLifeTimer);

	// NOTE: Set Particle Colour
	particle_system_object.m_Colour = OKVector3<unsigned int>(tempLerpX, tempLerpY, tempLerpZ);
}

void ParticleEffectComponent::ProcessColourOverVelocity(ParticleEffectObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if you sizes are the same, meaning this code does not have to be ran
	if (particle_system_object.m_StartingColourOverLifeTime == particle_system_object.m_EndingColourOverLifeTime) { return; }

	// NOTE: Calculate the sizing of the particle (Velocity resizing calculation)
	particle_system_object.m_CurrentSizeByVelocity = particle_system_object.GetVelocity().magnitude();

	const float MagMax = m_MaxVelocityByColour;
	const float MagMin = m_MaxVelocityByColour;

	// NOTE: Calculate the remapping range of Velocity via the Magnitude
	const float tempRemapValue = remap(particle_system_object.m_CurrentSizeByVelocity, MagMin, MagMax, 0, 1);

	// NOTE: Resize the particle based on time 
	const float tempLerpX = lerp(particle_system_object.m_StartingColourOverLifeTime->x, particle_system_object.m_EndingColourOverLifeTime->x, tempRemapValue);
	const float tempLerpY = lerp(particle_system_object.m_StartingColourOverLifeTime->y, particle_system_object.m_EndingColourOverLifeTime->y, tempRemapValue);
	const float tempLerpZ = lerp(particle_system_object.m_StartingColourOverLifeTime->z, particle_system_object.m_EndingColourOverLifeTime->z, tempRemapValue);

	// NOTE: Assign the resize to the scale of the current particle
	particle_system_object.m_Colour = OKVector3<unsigned int>(tempLerpX, tempLerpY, tempLerpZ);
}

// NOTE: Action Functions

void ParticleEffectComponent::ProcessActionNone(ParticleEffectObject& particle_system_object)
{
	// NOTE: Does Nothing
}

void ParticleEffectComponent::ProcessActionBurstOut(ParticleEffectObject& particle_system_object)
{
	float MaxX = 360.0f;
	float MinX = -360.0f;
	int RangeX = MaxX - MinX + 1;
	float NumX = rand() % RangeX + MinX;

	float MaxY = 360;
	float MinY = -360;
	int RangeY = MaxY - MinY + 1;
	float NumY = rand() % RangeY + MinY;

	particle_system_object.ApplyImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionBurstIn(ParticleEffectObject& particle_system_object)
{
	// SPEED = DISTANCE / TIME
}

void ParticleEffectComponent::ProcessActionScreen(ParticleEffectObject& particle_system_object)
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
	theta += GetFrameTime(); // TODO: SIMUATLION SPEED HERE

	if (theta > 360) { theta = 0; }

	float PositionX = particle_system_object.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.GetPosition().y + sin(theta * NumY);

	particle_system_object.SetPosition(PositionX, PositionY);
}

void ParticleEffectComponent::ProcessActionScreenOut(ParticleEffectObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.GetPosition();

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

	float PositionX = particle_system_object.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.GetPosition().y + sin(theta * NumY);

	particle_system_object.SetPosition(PositionX, PositionY);
	particle_system_object.ApplyImpulse(-DistanceParticle.x * m_StartSpeed, -DistanceParticle.y * m_StartSpeed);

	// Pulsing
	// particle_system_object.particle.ApplyImpulse(DistanceParticle);
}

void ParticleEffectComponent::ProcessActionScreenIn(ParticleEffectObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.GetPosition();

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

	float PositionX = particle_system_object.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.GetPosition().y + sin(theta * NumY);

	particle_system_object.SetPosition(PositionX, PositionY);
	particle_system_object.ApplyImpulse(DistanceParticle.x * m_StartSpeed, DistanceParticle.y * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionFall(ParticleEffectObject& particle_system_object)
{
	particle_system_object.ApplyImpulse(0, 1 * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionRise(ParticleEffectObject& particle_system_object)
{
	particle_system_object.ApplyImpulse(0, -1 * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionRight(ParticleEffectObject& particle_system_object)
{
	particle_system_object.ApplyImpulse(1 * m_StartSpeed, 0);
}

void ParticleEffectComponent::ProcessActionLeft(ParticleEffectObject& particle_system_object)
{
	particle_system_object.ApplyImpulse(-1 * m_StartSpeed, 0);
}

void ParticleEffectComponent::ProcessActionSpray(ParticleEffectObject& particle_system_object)
{
	// NOTE: Calculating position from the origin

	const OKVector2<float> centre_position = m_Transform.position + m_EmitterPositionOffset;
	OKVector2<float> CalulatedPosition = particle_system_object.GetPosition() - centre_position;
	OKVector2<float> Direction = CalulatedPosition;

	// NOTE: Assumes that it is using the None Spawn Function
	if (particle_system_object.GetPosition() == centre_position)
	{
		int RangeX = (45) - (-45) + 1;
		int NumX = rand() % RangeX + -45;

		int RangeY = (45) - (-45) + 1;
		int NumY = rand() % RangeY + -45;

		OKVector2<float> NewDirction = OKVector2<float>(Direction.x + NumX, Direction.y + NumY);
		
		// NOTE: Calculated a projected position to the origin (this would be more so to do with point)
		particle_system_object.ApplyImpulse(NewDirction.x * m_StartSpeed, NewDirction.y * m_StartSpeed);

		return;
	}

	// NOTE: Assign impulse
	particle_system_object.ApplyImpulse(Direction.x * m_StartSpeed, Direction.y * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionFire(ParticleEffectObject& particle_system_object)
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

	float PositionX = particle_system_object.GetPosition().x + cos(theta);
	particle_system_object.ApplyImpulse(0 * m_StartSpeed, -NumY * m_StartSpeed);
	particle_system_object.SetPosition(PositionX, particle_system_object.GetPosition().y);
}

void ParticleEffectComponent::ProcessActionSmoke(ParticleEffectObject& particle_system_object)
{
	OKVector2<float> DistanceParticle = m_Transform.position - particle_system_object.GetPosition();

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

	float PositionX = lerp(particle_system_object.GetPosition().x, DistanceProjectionX, 0.5);
	float PositionY = lerp(particle_system_object.GetPosition().y, DistanceProjectionY, 0.5);

	particle_system_object.ApplyImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionSpark(ParticleEffectObject& particle_system_object)
{
	int MaxX = 360;
	int MinX = -360;
	int RangeX = MaxX - MinX + 1;
	int NumX = rand() % RangeX + MinX;

	int MaxY = 360;
	int MinY = -360;
	int RangeY = MaxY - MinY + 1;
	int NumY = rand() % RangeY + MinY;

	particle_system_object.ApplyImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
}

void ParticleEffectComponent::ProcessActionCustom(ParticleEffectObject& particle_system_object)
{
	if (m_CustomParticleActionFunctionPtr != nullptr) { m_CustomParticleActionFunctionPtr(); }
}

void ParticleEffectComponent::AssignVelocityOverLifeTime(OKVector2<float> starting_velocity_over_lifetime, OKVector2<float> ending_velocity_over_lifetime)
{
	m_StartingVelocityOverLifeTime = starting_velocity_over_lifetime;
	m_EndingVelocityOverLifeTime = ending_velocity_over_lifetime;

	m_CheckParticlePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_VELOCITY_OVER_LIFETIME];
}

void ParticleEffectComponent::AssignForceOverLifeTime(OKVector2<float> starting_force_over_lifetime, OKVector2<float> ending_force_over_lifetime)
{
	m_StartingForceOverLifeTime = starting_force_over_lifetime;
	m_EndingForceOverLifeTime = ending_force_over_lifetime;

	m_CheckParticlePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_FORCE_OVER_LIFETIME];
}

void ParticleEffectComponent::AssignResizeOverLifeTime(OKVector2<float> starting_resize_over_lifetime, OKVector2<float> ending_resize_over_lifetime)
{
	m_StartingSizeOverLifeTime = starting_resize_over_lifetime;
	m_EndingSizeOverLifeTime = ending_resize_over_lifetime;

	m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_OVER_LIFETIME];
}

void ParticleEffectComponent::AssignResizeByVelocityOverLifeTime(OKVector2<float> starting_resize_velocity_over_lifetime, OKVector2<float> ending_resize_velocity_over_lifetime, float max_velocity_by_size, float min_velocity_by_size)
{
	m_StartingSizeByVelocity = starting_resize_velocity_over_lifetime;
	m_EndingSizeByVelocity = ending_resize_velocity_over_lifetime;

	m_MaxVelocityBySize = max_velocity_by_size;
	m_MinVelocityBySize = min_velocity_by_size;

	m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_VELOCITY];
}

void ParticleEffectComponent::AssignColourOverLifeTime(OKVector3<unsigned int> starting_colour_over_lifetime, OKVector3<unsigned int> ending_colour_over_lifetime)
{
	m_StartingColourOverLifeTime = starting_colour_over_lifetime;
	m_EndingColourOverLifeTime = ending_colour_over_lifetime;

	m_CheckParticleColourOverTimerFunctionPtr = m_ParticleColourOverTimerMap[PARTICLE_COLOUR_OVER_LIFE_TIME];
}

void ParticleEffectComponent::AssignColourVelocityOverLifeTime(OKVector3<unsigned int> starting_colour_over_lifetime, OKVector3<unsigned int> ending_colour_over_lifetime, float max_velocity_by_colour, float min_velocity_by_colour)
{
	m_StartingColourOverLifeTime = starting_colour_over_lifetime;
	m_EndingColourOverLifeTime = ending_colour_over_lifetime;

	m_MaxVelocityByColour = max_velocity_by_colour;
	m_MinVelocityByColour = min_velocity_by_colour;

	m_CheckParticleColourOverTimerFunctionPtr = m_ParticleColourOverTimerMap[PARTICLE_COLOUR_VELOCITY_OVER_LIFE_TIME];
}


