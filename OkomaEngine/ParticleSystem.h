#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include <memory>
#include <vector>
#include <utility>
#include <map>
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

class ParticleSystem
{
private:

	// CUSTOM DATA TYPE
	typedef void (*particle_func)(Particle&);
	typedef std::map<ParticleSpawnArea, particle_func> particle_spawn_area_map;
	typedef std::map<ParticleAction, particle_func> particle_action_map;

	// TRANSFORM VARIABLE(s)
	OKTransform2<float> m_Transform;
	OKVector2<float> m_SpawnPosition;

	// PARTICLE VARIABLE(s)
	std::vector<Particle> m_Particles;

	ParticleSpawnArea m_ParticleSpawnArea;
	ParticleAction m_ParticleAction;

	particle_spawn_area_map m_ParticleAreaMap;
	particle_action_map m_ParticleActionMap;


	// BASE VARIABLE(s)
	unsigned int m_MaxParticleCount;
	float m_Duration = { 1.0f };
	bool m_IsLooping{ false };
	float m_StartDelay{ 0.0f }; // NOTE: In Seconds
	float m_StartLifeTime{ 5.0f };
	float m_StartSpeed{ 5.0f };
	OKVector2<float> m_StartSize{ 1.0f, 1.0f };

	OKVector2<float> m_Gravity{ 0.0f, 0.0f };
	bool m_SimulateGravity{ false };
	float m_SimulationSpeed{ 1.0f };


	// EMISSION VARIABLE(s)
	unsigned int m_EmissionRateOverTime{ 5u };
	unsigned int m_EmissionRateOverDistance{ 1u };

	// NOTE: These will overwrite previous variables that were set

	// VELOCITY OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingVelocityOverLifeTime;
	OKVector2<float> m_EndingVelocityOverLifeTime;

	// FORCE OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingForceOverLifeTime;
	OKVector2<float> m_EndingForceOverLifeTime;


	// SIZE OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingSizeOverLifeTime;
	OKVector2<float> m_EndingSizeOverLifeTime;

	// SIZE BY SPEED VARIABLE(s) --> Links to Variables Above
	OKVector2<float> m_StartingSizeBySpeed;
	OKVector2<float> m_EndingSizeBySpeed;

	// COLLISION
	bool m_HasCollision;

public:

	// CLASS FUNCTION(s)
	ParticleSystem(OKTransform2<float> transform, float mass, unsigned int maxParticleCount, ParticleSpawnArea particleSpawnArea = PARTICLE_SPAWN_AREA_NONE, ParticleAction particleAction = PARTICLE_ACTION_NONE);
	~ParticleSystem();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// HELPER FUNCTION(s)

		// NOTE: PARTICLE SPAWN AREA FUNCTION(s)
		static void ProcessSpawnAreaNone(Particle& particle);
		static void ProcessSpawnAreaCircle(Particle& particle);
		static void ProcessSpawnAreaHalfCircle(Particle& particle);
		static void ProcessSpawnAreaRectangle(Particle& particle);
		static void ProcessSpawnAreaTriangle(Particle& particle);
		static void ProcessSpawnAreaCapsule(Particle& particle);
		static void ProcessSpawnAreaDonut(Particle& particle);
		static void ProcessSpawnAreaEdge(Particle& particle);


		// NOTE: PARTICLE ACTION FUNCTION(s)
		static void ProcessActionNone(Particle& particle);

		static void ProcessActionBurstOut(Particle& particle);
		static void ProcessActionBurstIn(Particle& particle);

		static void ProcessActionScreen(Particle& particle);
		static void ProcessActionScreenOut(Particle& particle);
		static void ProcessActionScreenIn(Particle& particle);

		static void ProcessActionFall(Particle& particle);
		static void ProcessActionRise(Particle& particle);
		static void ProcessActionRight(Particle& particle);
		static void ProcessActionLeft(Particle& particle);

		static void ProcessActionSpray(Particle& particle);
		static void ProcessActionSpiral(Particle& particle);

		static void ProcessActionFire(Particle& particle);
		static void ProcessActionSmoke(Particle& particle);
		static void ProcessActionSpark(Particle& particle);
		static void ProcessActionWave(Particle& particle);


	// GETTER FUNCTION(s)

		inline OKTransform2<float> GetTransform() const { return m_Transform; }
		inline OKVector2<float> GetPosition() const { return m_Transform.position; }
		inline OKVector2<float> GetScale() const { return m_Transform.scale; }
		inline float GetRotation() const { return m_Transform.rotation; }

		inline unsigned int GetMaxParticleCount() const { return m_MaxParticleCount; }
		inline float GetDuration() const { return m_Duration; }
		inline bool GetLooping() const { return m_IsLooping; }
		inline float GetStartDelay() const { return m_StartDelay; }
		inline float GetStartLifeTime() const { return m_StartLifeTime; }
		inline float GetStartSpeed() const { return m_StartSpeed; }
		inline OKVector2<float> GetStartSize() const { return m_StartSize; }

		inline OKVector2<float> GetGravity() const { return m_Gravity; }
		inline bool GetSimulateGravity() const { return m_SimulateGravity; }
		inline float GetSimulationSpeed() const { return m_SimulationSpeed; }

		inline unsigned int GetEmissionRateOverTime() const { return m_EmissionRateOverTime; }
		inline unsigned int GetEmissionRateOverDistance() const { return m_EmissionRateOverDistance; }

		inline OKVector2<float> GetStartingVelocityOverLifeTime() const { return m_StartingVelocityOverLifeTime; }
		inline OKVector2<float> GetEndingVelocityOverLifeTime() const { return m_EndingVelocityOverLifeTime; }

		inline OKVector2<float> GetStartingForceOverLifeTime() const { return m_StartingForceOverLifeTime; }
		inline OKVector2<float> GetEndingForceOverLifeTime() const { return m_EndingForceOverLifeTime; }

		inline OKVector2<float> GetStartingSizeBySpeed() const { return m_StartingSizeBySpeed; }
		inline OKVector2<float> GetEndingSizeBySpeed() const { return m_EndingSizeBySpeed; }


	// SETTER FUNCTION(s)

		inline void SetTransform(OKTransform2<float> transform) { m_Transform = transform; }
		inline void SetPosition(OKVector2<float> position) { m_Transform.position = position; }
		inline void SetScale(OKVector2<float> scale) { m_Transform.scale = scale; }
		inline void SetRotation(float rotation) { m_Transform.rotation = rotation; }


		inline void SetMaxParticleCount(unsigned int maxParticleCount) { m_MaxParticleCount = maxParticleCount; }
		inline void SetDuration(float duration) { m_Duration = duration; }
		inline void SetLooping(bool looping) { m_IsLooping = looping; }
		inline void SetStartDelay(float startDelay) { m_StartDelay = startDelay; }
		inline void SetStartLifeTime(float startLifeTime) { m_StartLifeTime = startLifeTime; }
		inline void SetStartSpeed(float startSpeed) { m_StartSpeed = startSpeed; }
		inline void SetStartSize(OKVector2<float> startSize) { m_StartSize = startSize; }

		inline void SetGravity(OKVector2<float> gravity) { m_Gravity = gravity; }
		inline void SetSimulateGravity(bool simulateGravity) { m_SimulateGravity = simulateGravity; }
		inline void SetSimulationSpeed(float simulateSpeed) { m_SimulationSpeed = simulateSpeed; }

		inline void SetEmissionRateOverTime(unsigned int emissionRateOverTime) { m_EmissionRateOverTime = emissionRateOverTime; }
		inline void SetEmissionRateOverDistance(unsigned int emissionRateOverDistance) { m_EmissionRateOverDistance = emissionRateOverDistance; }

		inline void SetStartingVelocityOverLifeTime(OKVector2<float> startingVelocityOverLifeTime) { m_StartingVelocityOverLifeTime = startingVelocityOverLifeTime; }
		inline void SetEndingVelocityOverLifeTime(OKVector2<float> endingVelocityOverLifeTime) { m_EndingVelocityOverLifeTime = endingVelocityOverLifeTime; }

		inline void SetStartingForceOverLifeTime(OKVector2<float> startingForceOverLifeTime) { m_StartingForceOverLifeTime = startingForceOverLifeTime; }
		inline void SetEndingForceOverLifeTime(OKVector2<float> endingForceOverLifeTime) { m_EndingForceOverLifeTime = endingForceOverLifeTime; }

		inline void SetStartingSizeBySpeed(OKVector2<float> startingSizeBySpeed) { m_StartingSizeBySpeed = startingSizeBySpeed; }
		inline void SetEndingSizeBySpeed(OKVector2<float> endingSizeBySpeed) { m_EndingSizeBySpeed = endingSizeBySpeed; }
};

#endif