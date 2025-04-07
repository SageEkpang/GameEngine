#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include <memory>
#include <vector>
#include <utility>
#include <map>
#include <random>
// NOTE: In the collab project, rendering will have to be included here as well

// NOTE: Variables to Manipulate for Each Area
/*
	- Rectangle = Scale
	- Circle = Radius
	- Triangle = Scale
	- Donut = Inner Side and Outer Side
	- Capsule = Height and Width
	- None = Assumes just use the base position
*/

enum ParticleSpawnArea
{
	PARTICLE_SPAWN_AREA_NONE,
	PARTICLE_SPAWN_AREA_CIRCLE,
	PARTICLE_SPAWN_AREA_HALF_CIRCLE,
	PARTICLE_SPAWN_AREA_RECTANGLE,
	PARTICLE_SPAWN_AREA_TRIANGLE,
	PARTICLE_SPAWN_AREA_CAPSULE,
	PARTICLE_SPAWN_AREA_DONUT,
	PARTICLE_SPAWN_AREA_EDGE,
};

enum ParticleAction
{
	PARTICLE_ACTION_NONE,
	PARTICLE_ACTION_BURST_OUT,
	PARTICLE_ACTION_BURST_IN,

	PARTICLE_ACTION_SCREEN,
	PARTICLE_ACTION_SCREEN_OUT,
	PARTICLE_ACTION_SCREEN_IN,

	PARTICLE_ACTION_FALL,
	PARTICLE_ACTION_RISE,
	PARTICLE_ACTION_RIGHT,
	PARTICLE_ACTION_LEFT,

	PARTICLE_ACTION_SPRAY,
	PARTICLE_ACTION_SPIRAL, // NOTE: This one may be a bit long to code :-)

	PARTICLE_ACTION_FIRE,
	PARTICLE_ACTION_SMOKE,
	PARTICLE_ACTION_SPARK,
	PARTICLE_ACTION_WAVE
};

struct c_ParticleSystemObject
{
	Particle particle;

	// NOTE: Both
	float startDelay; // NOTE: In Seconds
	float startLifeTime;
	float startSpeed;
	OKVector2<float> startSize;
	OKVector2<float> gravity;

	OKVector2<float> startingVelocityOverLifeTime;
	OKVector2<float> endingVelocityOverLifeTime;

	OKVector2<float> startingForceOverLifeTime;
	OKVector2<float> endingForceOverLifeTime;

	OKVector2<float> startingSizeOverLifeTime;
	OKVector2<float> endingSizeOverLifeTime;

	OKVector2<float> startingSizeBySpeed;
	OKVector2<float> endingSizeBySpeed;

	c_ParticleSystemObject() = default;
	c_ParticleSystemObject(OKTransform2<float>* transform, float mass)
	{
		particle = Particle(transform, mass);
		startDelay = 0.f;
		startLifeTime = 1.0f;
		startSpeed = 1.0f;

		startSize = OKVector2<float>(1.0f);
		gravity = OKVector2<float>(0.f, 0.0f);

		startingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);
		endingVelocityOverLifeTime = OKVector2<float>(1.0f, 1.0f);

		startingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);
		endingForceOverLifeTime = OKVector2<float>(1.0f, 1.0f);

		startingSizeOverLifeTime = OKVector2<float>(1.0f, 1.0f);
		endingSizeOverLifeTime = OKVector2<float>(1.0f, 1.0f);

		startingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);
		endingSizeBySpeed = OKVector2<float>(1.0f, 1.0f);
	}

};

class ParticleSystem
{
private:

	// CUSTOM DATA TYPE
	typedef void (*particle_spawn_area_func)(OKTransform2<float>, c_ParticleSystemObject&);
	typedef void (*particle_action_func)(c_ParticleSystemObject&);

	typedef std::map<ParticleSpawnArea, particle_spawn_area_func> particle_spawn_area_map;
	typedef std::map<ParticleAction, particle_action_func> particle_action_map;

	// TRANSFORM VARIABLE(s)
	OKTransform2<float> m_Transform;

	// PARTICLE VARIABLE(s)
	std::vector<c_ParticleSystemObject> m_Particles;
	// std::vector<Particle> m_SimulateParticles; // NOTE: This is to push simulating particles from the loaded map

	bool m_IsExecuted = false;

	ParticleSpawnArea m_ParticleSpawnArea;
	ParticleAction m_ParticleAction;

	particle_spawn_area_map m_ParticleAreaMap;
	particle_action_map m_ParticleActionMap;


	// BASE VARIABLE(s)
	unsigned int m_MaxParticleCount;

	// NOTE: For NOT Looping
	float m_ParticleTimer;
	float m_Duration;
	bool m_IsLooping;
	bool m_SimulateGravity; // NOTE: Have it where particles simulate gravity
	float m_SimulationSpeed; // NOTE: Play back speed of the particle simulation

	// EMISSION VARIABLE(s)
	unsigned int m_EmissionRateOverTime; // NOTE: How many particles should be spawned per second
	unsigned int m_EmissionRateOverDistance; // NOTE: How many particles that should be spawned per distance unit

private: // SPAWN AREA VARIABLE(s)

	OKVector2<float> m_RectangleScale{ 5.f, 5.f};
	float m_CircleRadius{ 1.0f };
	OKVector2<float> m_TriangleScale{ 5.f, 5.f};

	OKVector2<float> m_InnerDonutScale{ 1.0f, 1.0f};
	OKVector2<float> m_OuterDonutScale{ 4.0f, 4.0f};

	float m_CapsuleHeight{ 40.0f };
	float m_CapsuleWidth{ 20.0f };

public:

	// CLASS FUNCTION(s)
	ParticleSystem(OKVector2<float> position, float mass, unsigned int maxParticleCount, bool isLooping = true, ParticleSpawnArea particleSpawnArea = PARTICLE_SPAWN_AREA_NONE, ParticleAction particleAction = PARTICLE_ACTION_NONE, float simulationSpeed = 1.f, bool simulateGravity = false);
	~ParticleSystem();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// HELPER FUNCTION(s)

		// NOTE: PARTICLE SPAWN AREA FUNCTION(s)
		static void ProcessSpawnAreaNone(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaHalfCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaRectangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaTriangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaCapsule(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaDonut(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
		static void ProcessSpawnAreaEdge(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);


		// NOTE: PARTICLE ACTION FUNCTION(s)
		void ProcessActionNone(c_ParticleSystemObject& particle_system_object);

		static void ProcessActionBurstOut(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionBurstIn(c_ParticleSystemObject& particle_system_object);

		static void ProcessActionScreen(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionScreenOut(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionScreenIn(c_ParticleSystemObject& particle_system_object);

		static void ProcessActionFall(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionRise(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionRight(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionLeft(c_ParticleSystemObject& particle_system_object);

		static void ProcessActionSpray(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionSpiral(c_ParticleSystemObject& particle_system_object);

		static void ProcessActionFire(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionSmoke(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionSpark(c_ParticleSystemObject& particle_system_object);
		static void ProcessActionWave(c_ParticleSystemObject& particle_system_object);


	// GETTER FUNCTION(s)

		inline OKTransform2<float> GetTransform() const { return m_Transform; }
		inline OKVector2<float> GetPosition() const { return m_Transform.position; }
		inline OKVector2<float> GetScale() const { return m_Transform.scale; }
		inline float GetRotation() const { return m_Transform.rotation; }

		inline unsigned int GetMaxParticleCount() const { return m_MaxParticleCount; }

		inline float GetDuration() const { return m_Duration; }

		inline bool GetLooping() const { return m_IsLooping; }
		//inline float GetStartDelay() const { return m_Particles[0].startDelay; }
		//inline float GetStartLifeTime() const { return m_Particles[0].startLifeTime; }
		//inline float GetStartSpeed() const { return m_Particles[0].startSpeed; }
		//inline OKVector2<float> GetStartSize() const { return m_Particles[0].startSize; }

		//inline OKVector2<float> GetGravity() const { return m_Particles[0].gravity; }
		//inline bool GetSimulateGravity() const { return m_SimulateGravity; }
		//inline float GetSimulationSpeed() const { return m_SimulationSpeed; }

		//inline unsigned int GetEmissionRateOverTime() const { return m_EmissionRateOverTime; }
		//inline unsigned int GetEmissionRateOverDistance() const { return m_EmissionRateOverDistance; }

		//inline OKVector2<float> GetStartingVelocityOverLifeTime() const { return m_Particles[0].startingVelocityOverLifeTime; }
		//inline OKVector2<float> GetEndingVelocityOverLifeTime() const { return m_Particles[0].endingVelocityOverLifeTime; }

		//inline OKVector2<float> GetStartingForceOverLifeTime() const { return m_Particles[0].startingForceOverLifeTime; }
		//inline OKVector2<float> GetEndingForceOverLifeTime() const { return m_Particles[0].endingForceOverLifeTime; }

		//inline OKVector2<float> GetStartingSizeBySpeed() const { return m_Particles[0].startingSizeBySpeed; }
		//inline OKVector2<float> GetEndingSizeBySpeed() const { return m_Particles[0].endingSizeBySpeed; }


	// SETTER FUNCTION(s)

		// BASE FUNCTION(s)
		inline void SetTransform(OKTransform2<float> transform) { m_Transform = transform; }
		inline void SetPosition(OKVector2<float> position) { m_Transform.position = position; }
		inline void SetScale(OKVector2<float> scale) { m_Transform.scale = scale; }
		inline void SetRotation(float rotation) { m_Transform.rotation = rotation; }
			
		// PARTICLE SYSTEM FUNCTION(s)
		inline void SetMaxParticleCount(unsigned int maxParticleCount) { m_MaxParticleCount = maxParticleCount; }
		inline void SetLooping(bool looping) { m_IsLooping = looping; }
		inline void SetSimulateGravity(bool simulateGravity) { m_SimulateGravity = simulateGravity; }
		inline void SetSimulationSpeed(float simulateSpeed) { m_SimulationSpeed = simulateSpeed; }
		inline void SetEmissionRateOverTime(unsigned int emissionRateOverTime) { m_EmissionRateOverTime = emissionRateOverTime; }
		inline void SetEmissionRateOverDistance(unsigned int emissionRateOverDistance) { m_EmissionRateOverDistance = emissionRateOverDistance; }

		//void SetDuration(float duration) 
		//{
		//	// m_Particles.insert(m_Particles.begin(), m_Particles.begin(), m_Particles.end());
		//}
		//inline void SetStartDelay(float startDelay) { m_StartDelay = startDelay; }
		//inline void SetStartLifeTime(float startLifeTime) { m_StartLifeTime = startLifeTime; }
		//inline void SetStartSpeed(float startSpeed) { m_StartSpeed = startSpeed; }
		//inline void SetStartSize(OKVector2<float> startSize) { m_StartSize = startSize; }

		//inline void SetGravity(OKVector2<float> gravity) { m_Gravity = gravity; }

		//inline void SetStartingVelocityOverLifeTime(OKVector2<float> startingVelocityOverLifeTime) { m_StartingVelocityOverLifeTime = startingVelocityOverLifeTime; }
		//inline void SetEndingVelocityOverLifeTime(OKVector2<float> endingVelocityOverLifeTime) { m_EndingVelocityOverLifeTime = endingVelocityOverLifeTime; }

		//inline void SetStartingForceOverLifeTime(OKVector2<float> startingForceOverLifeTime) { m_StartingForceOverLifeTime = startingForceOverLifeTime; }
		//inline void SetEndingForceOverLifeTime(OKVector2<float> endingForceOverLifeTime) { m_EndingForceOverLifeTime = endingForceOverLifeTime; }

		//inline void SetStartingSizeBySpeed(OKVector2<float> startingSizeBySpeed) { m_StartingSizeBySpeed = startingSizeBySpeed; }
		//inline void SetEndingSizeBySpeed(OKVector2<float> endingSizeBySpeed) { m_EndingSizeBySpeed = endingSizeBySpeed; }
};

#endif