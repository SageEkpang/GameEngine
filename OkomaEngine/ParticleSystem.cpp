#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(OKVector2<float> position, unsigned int maxParticleCount, ParticleType particleType, ParticleSpawnArea particleSpawnArea, ParticleAction particleAction, float mass, bool isLooping, float simulationSpeed, bool simulateGravity)
{
	// NOTE: Init Timer to NULL for random function
	srand(time(NULL));

	// NOTE: Set Transform
	m_Transform = OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);

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
	m_ParticleType = particleType;

	// NOTE: Particle Timer and Incremet Variables
	m_ParticleTimer = 0.0f;
	m_ParticleIndexIncrement = 0u;
	m_ParticleSimulationDuration = 5.f;

	m_EmissionTimer = 0.f;
	m_EmissionRateOverTime = 10u;

	#pragma region Particle System Pointer Functions

		// NOTE: PARTICLE SPAWN MAP INIT AND ASSIGNMENT

		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_NONE] = &ParticleSystem::ProcessSpawnAreaNone;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CIRCLE] = &ParticleSystem::ProcessSpawnAreaCircle;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE] = &ParticleSystem::ProcessSpawnAreaRectangle;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE] = &ParticleSystem::ProcessSpawnAreaCapsule;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_DONUT] = &ParticleSystem::ProcessSpawnAreaDonut;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_EDGE] = &ParticleSystem::ProcessSpawnAreaEdge;
		m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CUSTOM] = &ParticleSystem::ProcessSpawnAreaCustom;

		m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[m_ParticleSpawnArea];


		// NOTE: PARTICLE ACTION MAP INIT AND ASSIGNMENT

		m_ParticleActionMap[PARTICLE_ACTION_NONE] = &ParticleSystem::ProcessActionNone;
		m_ParticleActionMap[PARTICLE_ACTION_BURST_OUT] = &ParticleSystem::ProcessActionBurstOut;
		m_ParticleActionMap[PARTICLE_ACTION_BURST_IN] = &ParticleSystem::ProcessActionBurstIn;

		m_ParticleActionMap[PARTICLE_ACTION_SCREEN] = &ParticleSystem::ProcessActionScreen;
		m_ParticleActionMap[PARTICLE_ACTION_SCREEN_OUT] = &ParticleSystem::ProcessActionScreenOut;
		m_ParticleActionMap[PARTICLE_ACTION_SCREEN_IN] = &ParticleSystem::ProcessActionScreenIn;

		m_ParticleActionMap[PARTICLE_ACTION_FALL] = &ParticleSystem::ProcessActionFall;
		m_ParticleActionMap[PARTICLE_ACTION_RISE] = &ParticleSystem::ProcessActionRise;
		m_ParticleActionMap[PARTICLE_ACTION_RIGHT] = &ParticleSystem::ProcessActionRight;
		m_ParticleActionMap[PARTICLE_ACTION_LEFT] = &ParticleSystem::ProcessActionLeft;

		m_ParticleActionMap[PARTICLE_ACTION_SPRAY] = &ParticleSystem::ProcessActionSpray;
		m_ParticleActionMap[PARTICLE_ACTION_SPIRAL] = &ParticleSystem::ProcessActionSpiral;

		m_ParticleActionMap[PARTICLE_ACTION_FIRE] = &ParticleSystem::ProcessActionFire;
		m_ParticleActionMap[PARTICLE_ACTION_SMOKE] = &ParticleSystem::ProcessActionSmoke;
		m_ParticleActionMap[PARTICLE_ACTION_SPARK] = &ParticleSystem::ProcessActionSpark;
		m_ParticleActionMap[PARTICLE_ACTION_WAVE] = &ParticleSystem::ProcessActionWave;

		m_ParticleActionMap[PARTICLE_ACTION_CUSTOM] = &ParticleSystem::ProcessActionCustom;

		m_CheckParticleActionFunctionPtr = m_ParticleActionMap[m_ParticleAction];


		// NOTE: PARTICLE RESIZING VARIABLE(s)
		// m_ParticleResizeMap[PARTICLE_RESIZE_NONE] = nullptr; // TODO: Can change this to a nullptr reference instead of a function pointer, can remove the 
		m_ParticleResizeMap[PARTICLE_RESIZE_NONE] = &ParticleSystem::ProcessResizeNone;
		m_ParticleResizeMap[PARTICLE_RESIZE_OVER_LIFETIME] = &ParticleSystem::ProcessResizeOverLifeTime;
		m_ParticleResizeMap[PARTICLE_RESIZE_VELOCITY] = &ParticleSystem::ProcessResizeVelocity;

		m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_NONE];


		// NOTE: PARTICLE PHYSICS FORCE OVER TIME
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_NONE] = &ParticleSystem::ProcessPhysicsOverLifeTimeNone;
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_FORCE_OVER_LIFETIME] = &ParticleSystem::ProcessPhysicsOverLifeTimeForce;
		m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_VELOCITY_OVER_LIFETIME] = &ParticleSystem::ProcessPhysicsOverLifeTimeVelocity;

		m_CheckPatriclePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_NONE];

	#pragma endregion

	#pragma region Particle System Object Inits

	m_StartDelay = 0.0f;
	m_StartLifeTime = 5.0f;
	m_StartSpeed = 1.0f;
	m_StartSize = OKVector2<float>(5.0f, 5.0f);
	m_Gravity = OKVector2<float>(0.0f, 0.0f);

	m_StartingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);
	m_EndingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);

	m_StartingSizeOverLifeTime = m_StartSize;
	m_EndingSizeOverLifeTime = m_StartSize;

	m_StartingSizeByVelocity = m_StartSize;
	m_EndingSizeByVelocity = m_StartSize;

	// NOTE: Set Defauls for Particles
	for (unsigned int i = 0; i < m_MaxParticleCount; ++i) 
	{ 
		OKTransform2<float>* transform = new OKTransform2<float>(position, OKVector2<float>(1.f, 1.f), 0);
		c_ParticleSystemObject* particle_system_objects = new c_ParticleSystemObject(transform, mass);

		particle_system_objects->SimulateGravity(m_SimulateGravity);
		particle_system_objects->SetGravity(m_Gravity);

		particle_system_objects->SetScale(m_StartSize.x, m_StartSize.y);
		particle_system_objects->SetRotation(0.0f);

		particle_system_objects->m_StartDelay = &m_StartDelay;
		particle_system_objects->m_StartLifeTime = &m_StartLifeTime;
		particle_system_objects->m_CurrentLifeTime = m_StartLifeTime;

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

		m_Particles.push_back(particle_system_objects);
	}

	#pragma endregion
}

ParticleSystem::~ParticleSystem()
{
	m_CustomParticleActionFunctionPtr = nullptr;
	m_CustomParticleSpawnAreaFunctionPtr = nullptr;

	m_CheckParticleActionFunctionPtr = nullptr;
	m_CheckParticleSpawnFunctionPtr = nullptr;
	m_CheckParticleResizingFunctionPtr = nullptr;
	m_CheckPatriclePhysicsOverTimeFunctionPtr = nullptr;

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
					m_SimulatingParticles.push_back(*m_Particles[m_ParticleIndexIncrement]);

					// NOTE: Get the last particle that was inserted in the list and update that, assuming that is the particle that needs to be updated
					std::vector<c_ParticleSystemObject>::iterator itr = m_SimulatingParticles.end() - 1;
					(this->*m_CheckParticleSpawnFunctionPtr)(m_Transform, *itr);
					(this->*m_CheckParticleActionFunctionPtr)(*itr);
					++m_ParticleIndexIncrement;

				}
				else if (m_ParticleType == PARTICLE_TYPE_AREA)
				{
					for (unsigned int i = 0; i < m_EmissionRateOverTime; ++i)
					{
						// NOTE: Push particles to the simuatling vector
						m_SimulatingParticles.push_back(*m_Particles[m_ParticleIndexIncrement]);

						// NOTE: Get the last particle that was inserted in the list and update that, assuming that is the particle that needs to be updated
						std::vector<c_ParticleSystemObject>::iterator itr = m_SimulatingParticles.end() - 1;
						(this->*m_CheckParticleSpawnFunctionPtr)(m_Transform, *itr);
						(this->*m_CheckParticleActionFunctionPtr)(*itr);
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
					m_SimulatingParticles.push_back(*m_Particles[m_ParticleIndexIncrement]);

					// NOTE: Get the last particle that was inserted in the list and update that, assuming that is the particle that needs to be updated
					std::vector<c_ParticleSystemObject>::iterator itr = m_SimulatingParticles.end() - 1;
					(this->*m_CheckParticleSpawnFunctionPtr)(m_Transform, *itr);
					(this->*m_CheckParticleActionFunctionPtr)(*itr);
					++m_ParticleIndexIncrement;
				}
				else if (m_ParticleType == PARTICLE_TYPE_AREA)
				{
					for (unsigned int i = 0; i < m_EmissionRateOverTime; ++i)
					{
						// NOTE: Push particles to the simuatling vector
						m_SimulatingParticles.push_back(*m_Particles[m_ParticleIndexIncrement]);

						// NOTE: Get the last particle that was inserted in the list and update that, assuming that is the particle that needs to be updated
						std::vector<c_ParticleSystemObject>::iterator itr = m_SimulatingParticles.end() - 1;
						(this->*m_CheckParticleSpawnFunctionPtr)(m_Transform, *itr);
						(this->*m_CheckParticleActionFunctionPtr)(*itr);
						++m_ParticleIndexIncrement;
					}
				}

				// NOTE: Reset the Particle Index Increment to 0, when equals the max particle count
				if (m_ParticleIndexIncrement > m_MaxParticleCount - 1)
				{
					m_ParticleIndexIncrement = 0;
				}

				// NOTE: Reset Emitter Timer
				m_EmissionTimer = 0;
			}
		}
	}

	// NOTE: Update Simulating Particles
	// NOTE: Delete the particles that need to be deleted after lifetime 
	if (!m_SimulatingParticles.empty())
	{
		for (auto itr = m_SimulatingParticles.begin(); itr != m_SimulatingParticles.end();)
		{
			// NOTE: Check the particle life time and update the "life time" within the particle
			CheckParticleLifeTime(*itr, SimulationSpeedDelta);

			if ((*itr).m_CurrentLifeTime < 0.0f)
			{
				// NOTE: Remove element at array index depending on if it reaches the lifetime 
				itr = m_SimulatingParticles.erase(itr);
			}
			else
			{
				// NOTE: Iterate through vector
				// NOTE: Process the Particle Sizing, Velocity and Force Values (has to be here to properly update at the same time as the other particles)
				(this->*m_CheckParticleResizingFunctionPtr)(*itr, SimulationSpeedDelta);
				(this->*m_CheckPatriclePhysicsOverTimeFunctionPtr)(*itr, SimulationSpeedDelta);
				(*itr).Update(SimulationSpeedDelta);
				++itr;
			}
		}
	}
}

void ParticleSystem::Draw()
{
	if (!m_SimulatingParticles.empty())
	{
		for (auto& v : m_SimulatingParticles)
		{
			DrawRectangleV(v.GetTransform()->position.ConvertToVec2(), v.GetTransform()->scale.ConvertToVec2(), RED);
		}
	}
}

void ParticleSystem::CreateParticleAction(void(*particle_action_lamda)())
{
	m_CustomParticleActionFunctionPtr = particle_action_lamda;
}

void ParticleSystem::AssignSpawnAreaNone()
{
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_NONE];
}

void ParticleSystem::AssignSpawnAreaCircle(float radius)
{
	m_CircleRadius = radius;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CIRCLE];
}

void ParticleSystem::AssignSpawnAreaRectangle(float width, float height)
{
	m_RectangleScale.x = width;
	m_RectangleScale.y = height;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE];
}

void ParticleSystem::AssignSpawnAreaRectangle(OKVector2<float> scale)
{
	m_RectangleScale = scale;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_RECTANGLE];
}

void ParticleSystem::AssignSpawnAreaCapsule(float width, float height)
{
	m_CapsuleWidth = width;
	m_CapsuleHeight = height;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE];
}

void ParticleSystem::AssignSpawnAreaCapsule(OKVector2<float> scale)
{
	m_CapsuleWidth = scale.x;
	m_CapsuleHeight = scale.y;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CAPSULE];
}

void ParticleSystem::AssignSpawnAreaDonut(float outer_circle_radius, float inner_circle_radius)
{
	m_OuterDonutScale = outer_circle_radius;
	m_InnerDonutScale = inner_circle_radius;
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_DONUT];
}

void ParticleSystem::AssignSpawnAreaCustom()
{
	m_CheckParticleSpawnFunctionPtr = m_ParticleSpawnMap[PARTICLE_SPAWN_AREA_CUSTOM];
}

void ParticleSystem::AssignParticleAction(ParticleAction particle_action)
{
	m_CheckParticleActionFunctionPtr = m_ParticleActionMap[particle_action];
}


void ParticleSystem::AssignParticleType(ParticleType particle_type)
{
	m_ParticleType = particle_type;
}


void ParticleSystem::CheckParticleLifeTime(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	particle_system_object.m_CurrentLifeTime -= deltaTime;
}

void ParticleSystem::CreateParticleSpawnArea(void(*particle_spawn_area_lambda)())
{
	m_CustomParticleSpawnAreaFunctionPtr = particle_spawn_area_lambda;
}

// NOTE: Spawn Area Functions
void ParticleSystem::ProcessSpawnAreaNone(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.SetPosition(transform.position);
}

void ParticleSystem::ProcessSpawnAreaCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
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

void ParticleSystem::ProcessSpawnAreaRectangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
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

void ParticleSystem::ProcessSpawnAreaCapsule(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
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

	particle_system_object.SetPosition(PositionX, PositionY);
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

	particle_system_object.SetPosition(RandXRange, CentrePosition.y);
}

void ParticleSystem::ProcessSpawnAreaCustom(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object)
{
	if (m_CustomParticleSpawnAreaFunctionPtr != nullptr) { m_CustomParticleSpawnAreaFunctionPtr(); }
	else { particle_system_object.SetPosition(transform.position); }
}


// NOTE: Resizing Functions
void ParticleSystem::ProcessResizeNone(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: Do nothing
}

void ParticleSystem::ProcessResizeOverLifeTime(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if you sizes are the same, meaning this code does not have to be ran
	if (particle_system_object.m_StartingSizeOverLifeTime == particle_system_object.m_EndingSizeOverLifeTime) { return; }

	// NOTE: Calculate the sizing of the particle
	particle_system_object.m_CurrentSizeOverLifeTimer += (1.f / *particle_system_object.m_StartLifeTime / *particle_system_object.m_StartLifeTime) / 1000;

	// NOTE: Resize the Particle based on time
	const float tempLerpX = lerp(particle_system_object.m_StartingSizeOverLifeTime->x, particle_system_object.m_EndingSizeOverLifeTime->x, particle_system_object.m_CurrentSizeOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingSizeOverLifeTime->y, particle_system_object.m_EndingSizeOverLifeTime->y, particle_system_object.m_CurrentSizeOverLifeTimer);

	// NOTE: Assign the resize to the scale of the current particle
	particle_system_object.SetScale(tempLerpX, tempLerpY);
}

void ParticleSystem::ProcessResizeVelocity(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if you sizes are the same, meaning this code does not have to be ran
	if (particle_system_object.m_StartingSizeByVelocity == particle_system_object.m_EndingSizeByVelocity) { return; }

	// NOTE: Calculate the sizing of the particle (Velocity resizing calculation)
	particle_system_object.m_CurrentSizeByVelocity = particle_system_object.GetVelocity().magnitude();
	const float MagStart = particle_system_object.m_StartingSizeByVelocity->magnitude();
	const float MagEnd = particle_system_object.m_EndingSizeByVelocity->magnitude();

	// NOTE: Calculate the remapping range of Velocity via the Magnitude
	const float tempRemapValue = remap(particle_system_object.m_CurrentSizeByVelocity, MagStart, MagEnd);
	
	// NOTE: Resize the particle based on time 
	const float tempLerpX = lerp(particle_system_object.m_StartingSizeByVelocity->x, particle_system_object.m_EndingSizeOverLifeTime->x, tempRemapValue);
	const float tempLerpY = lerp(particle_system_object.m_StartingSizeByVelocity->y, particle_system_object.m_EndingSizeOverLifeTime->y, tempRemapValue);

	// NOTE: Assign the resize to the scale of the current particle
	particle_system_object.SetScale(tempLerpX, tempLerpY);
}

void ParticleSystem::ProcessPhysicsOverLifeTimeNone(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: No Functionality
}

void ParticleSystem::ProcessPhysicsOverLifeTimeForce(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if the force over life time is the same, if it is, skip it
	if (particle_system_object.m_StartingForceOverLifeTime == particle_system_object.m_EndingForceOverLifeTime) { return; }

	// NOTE: Calculating the force over time particle
	particle_system_object.m_CurrentForceOverLifeTimer += (1.f / *particle_system_object.m_StartLifeTime / *particle_system_object.m_StartLifeTime) / 1000;

	// NOTE: Force over time lerping
	const float tempLerpX = lerp(particle_system_object.m_StartingForceOverLifeTime->x, particle_system_object.m_EndingForceOverLifeTime->x, particle_system_object.m_CurrentForceOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingForceOverLifeTime->y, particle_system_object.m_EndingForceOverLifeTime->y, particle_system_object.m_CurrentForceOverLifeTimer);
	
	// NOTE: Assign the force over time of the current particle
	particle_system_object.SetForce(OKVector2<float>(tempLerpX, tempLerpY));
}

void ParticleSystem::ProcessPhysicsOverLifeTimeVelocity(c_ParticleSystemObject& particle_system_object, float deltaTime)
{
	// NOTE: Check if the velocity over life time is the same
	if (particle_system_object.m_StartingVelocityOverLifeTime == particle_system_object.m_EndingVelocityOverLifeTime) { return; }

	// NOTE: Calculating the velocity over time particle
	particle_system_object.m_CurrentVelocityOverLifeTimer += (1.f / *particle_system_object.m_StartLifeTime / *particle_system_object.m_StartLifeTime) / 1000;

	// NOTE: Force over time lerping
	const float tempLerpX = lerp(particle_system_object.m_StartingVelocityOverLifeTime->x, particle_system_object.m_EndingVelocityOverLifeTime->x, particle_system_object.m_CurrentVelocityOverLifeTimer);
	const float tempLerpY = lerp(particle_system_object.m_StartingVelocityOverLifeTime->y, particle_system_object.m_EndingVelocityOverLifeTime->y, particle_system_object.m_CurrentVelocityOverLifeTimer);

	// NOTE: Assign the force over time of the current particle
	particle_system_object.SetVelocity(OKVector2<float>(tempLerpX, tempLerpY));
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

	particle_system_object.AddImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
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
	theta += GetFrameTime(); // TODO: SIMUATLION SPEED HERE

	if (theta > 360) { theta = 0; }

	float PositionX = particle_system_object.GetPosition().x + cos(theta * NumX);
	float PositionY = particle_system_object.GetPosition().y + sin(theta * NumY);

	particle_system_object.SetPosition(PositionX, PositionY);
}

void ParticleSystem::ProcessActionScreenOut(c_ParticleSystemObject& particle_system_object)
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
	particle_system_object.AddImpulse(-DistanceParticle.x * m_StartSpeed, -DistanceParticle.y * m_StartSpeed);

	// Pulsing
	// particle_system_object.particle.AddImpulse(DistanceParticle);
}

void ParticleSystem::ProcessActionScreenIn(c_ParticleSystemObject& particle_system_object)
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
	particle_system_object.AddImpulse(DistanceParticle.x * m_StartSpeed, DistanceParticle.y * m_StartSpeed);
}

void ParticleSystem::ProcessActionFall(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.AddImpulse(0, 1 * m_StartSpeed);
}

void ParticleSystem::ProcessActionRise(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.AddImpulse(0, -1 * m_StartSpeed);
}

void ParticleSystem::ProcessActionRight(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.AddImpulse(1 * m_StartSpeed, 0);
}

void ParticleSystem::ProcessActionLeft(c_ParticleSystemObject& particle_system_object)
{
	particle_system_object.AddImpulse(-1 * m_StartSpeed, 0);
}

// TODO:
void ParticleSystem::ProcessActionSpray(c_ParticleSystemObject& particle_system_object)
{
	// Add some functionality to spray it in a certain direction dependant on the dot product angle 







	particle_system_object.AddImpulse(-1 * m_StartSpeed, 0);
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

	float PositionX = particle_system_object.GetPosition().x + cos(theta);
	particle_system_object.AddImpulse(0 * m_StartSpeed, -NumY * m_StartSpeed);
	particle_system_object.SetPosition(PositionX, particle_system_object.GetPosition().y);
}

void ParticleSystem::ProcessActionSmoke(c_ParticleSystemObject& particle_system_object)
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

	particle_system_object.AddImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
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

	particle_system_object.AddImpulse(NumX * m_StartSpeed, NumY * m_StartSpeed);
}

// TODO: Fix This	
void ParticleSystem::ProcessActionWave(c_ParticleSystemObject& particle_system_object)
{

	// particle_system_object.particle.SetPosition(particle_system_object.particle.GetPosition().x, particle_system_object.particle.GetPosition().y);
	// particle_system_object.particle.AddImpulse(0, NumY);
}

void ParticleSystem::ProcessActionCustom(c_ParticleSystemObject& particle_system_object)
{
	if (m_CustomParticleActionFunctionPtr != nullptr) { m_CustomParticleActionFunctionPtr(); }
}

void ParticleSystem::AssignVelocityOverLifeTime(OKVector2<float> starting_velocity_over_lifetime, OKVector2<float> ending_velocity_over_lifetime)
{
	m_StartingVelocityOverLifeTime = starting_velocity_over_lifetime;
	m_EndingVelocityOverLifeTime = ending_velocity_over_lifetime;

	m_CheckPatriclePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_VELOCITY_OVER_LIFETIME];
}

void ParticleSystem::AssignForceOverLifeTime(OKVector2<float> starting_force_over_lifetime, OKVector2<float> ending_force_over_lifetime)
{
	m_StartingForceOverLifeTime = starting_force_over_lifetime;
	m_EndingForceOverLifeTime = ending_force_over_lifetime;

	m_CheckPatriclePhysicsOverTimeFunctionPtr = m_ParticlePhysicsOverTimeMap[PARTICLE_PHYSICS_FORCE_OVER_LIFETIME];
}

void ParticleSystem::AssignResizeOverLifeTime(OKVector2<float> starting_resize_over_lifetime, OKVector2<float> ending_resize_over_lifetime)
{
	m_StartingSizeOverLifeTime = starting_resize_over_lifetime;
	m_EndingSizeOverLifeTime = ending_resize_over_lifetime;

	m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_OVER_LIFETIME];
}

void ParticleSystem::AssignResizeByVelocityOverLifeTime(OKVector2<float> starting_resize_velocity_over_lifetime, OKVector2<float> ending_resize_velocity_over_lifetime)
{
	m_StartingSizeByVelocity = starting_resize_velocity_over_lifetime;
	m_EndingSizeByVelocity = ending_resize_velocity_over_lifetime;

	m_CheckParticleResizingFunctionPtr = m_ParticleResizeMap[PARTICLE_RESIZE_VELOCITY];
}
