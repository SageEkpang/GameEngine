#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include "ParticleSystemObject.h"

#include <memory>
#include <vector>
#include <utility>
#include <map>
#include <cmath>
#include <random>
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
	PARTICLE_SPAWN_AREA_RECTANGLE,
	PARTICLE_SPAWN_AREA_CAPSULE,
	PARTICLE_SPAWN_AREA_DONUT,
	PARTICLE_SPAWN_AREA_EDGE,
	PARTICLE_SPAWN_AREA_CUSTOM
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
	PARTICLE_ACTION_WAVE,

	PARTICLE_ACTION_CUSTOM
};

enum ParticleType
{
	PARTICLE_TYPE_EMISSIVE,
	PARTICLE_TYPE_AREA
};

enum ParticleResize
{
	PARTICLE_RESIZE_NONE,
	PARTICLE_RESIZE_OVER_LIFETIME,
	PARTICLE_RESIZE_VELOCITY
};

class ParticleSystem
{
private:

	// NOTE: PTR TYPEDEF FOR FUNCTION(s)

	typedef void (ParticleSystem::* CheckParticleActionFunctionPtr)(c_ParticleSystemObject&);
	std::map<ParticleAction, CheckParticleActionFunctionPtr> m_ParticleActionMap;

	typedef void (ParticleSystem::* CheckParticleSpawnFunctionPtr)(OKTransform2<float>, c_ParticleSystemObject&);
	std::map<ParticleSpawnArea, CheckParticleSpawnFunctionPtr> m_ParticleSpawnMap;

	typedef void (ParticleSystem::* CheckParticleResizeFunctionPtr)(c_ParticleSystemObject&, float);
	std::map<ParticleResize, CheckParticleResizeFunctionPtr> m_ParticleResizeMap;

	// CUSTOM DATA TYPE
	void (*m_CustomParticleActionFunctionPtr)() = nullptr;
	void (*m_CustomParticleSpawnAreaFunctionPtr)() = nullptr;

	void (ParticleSystem::* m_CheckParticleActionFunctionPtr)(c_ParticleSystemObject&) = nullptr;
	void (ParticleSystem::* m_CheckParticleSpawnFunctionPtr)(OKTransform2<float>, c_ParticleSystemObject&) = nullptr;
	void (ParticleSystem::* m_CheckParticleResizingFunctionPtr)(c_ParticleSystemObject&, float) = nullptr;


	// TRANSFORM VARIABLE(s)
	OKTransform2<float> m_Transform; // USED

	// PARTICLE VARIABLE(s)
	// May be able to convert to a single variable
	std::vector<c_ParticleSystemObject*> m_Particles; // USED
	std::vector<c_ParticleSystemObject> m_SimulatingParticles; // NOTE: This is to push simulating particles from the loaded map
	unsigned int m_ParticleIndexIncrement;

	bool m_IsExecuted = false;

	ParticleSpawnArea m_ParticleSpawnArea; // USED
	ParticleAction m_ParticleAction; // USED
	ParticleType m_ParticleType; // USED


	// BASE VARIABLE(s)
	unsigned int m_MaxParticleCount;
	bool m_SpawnAllAtOnce = false;

	// NOTE: Setting Variable(s)
	float m_StartDelay;
	float m_StartLifeTime;
	float m_StartSpeed;
	OKVector2<float> m_StartSize;

	OKVector2<float> m_StartingVelocityOverLifeTime;
	OKVector2<float> m_EndingVelocityOverLifeTime;

	OKVector2<float> m_StartingForceOverLifeTime;
	OKVector2<float> m_EndingForceOverLifeTime;

	OKVector2<float> m_StartingSizeOverLifeTime;
	OKVector2<float> m_EndingSizeOverLifeTime;

	OKVector2<float> m_StartingSizeByVelocity;
	OKVector2<float> m_EndingSizeByVelocity;

	// NOTE: For NOT Looping
	float m_ParticleTimer; // USED
	float m_ParticleSimulationDuration; // USED
	bool m_IsLooping; // USED
	OKVector2<float> m_Gravity;
	bool m_SimulateGravity; // NOTE: Have it where particles simulate gravity // USED
	float m_SimulationSpeed; // NOTE: Play back speed of the particle simulation // USED

	// EMISSION VARIABLE(s)
	float m_EmissionTimer = 0.0f; // USED
	unsigned int m_EmissionRateOverTime; // NOTE: How many particles should be spawned per second // USED

private: // SPAWN AREA VARIABLE(s)

	#pragma region PRIVATE SPAWN AREA VARIABLE(s)

	float m_CircleRadius = 0.0f;
	OKVector2<float> m_RectangleScale{ 1.f, 1.f};

	float m_InnerDonutScale = 0.0f;
	float m_OuterDonutScale = 0.0f;

	float m_CapsuleHeight = 0.0f;
	float m_CapsuleWidth = 0.0f;

	#pragma endregion


private: // PRIVATE FUNCTION(s)

	#pragma region PRIVATE PROCESS FUNCTIONS

	// LOCAL MATHS FUNCTION(s)
	float lerp(float a, float b, float f) { return (a * (1.0 - f)) + (b * f); }
	float remap(float value, float sourceMin, float sourceMax, float destMin = 0, float destMax = 1) { return destMin + ((value - sourceMin) / (sourceMax - sourceMin)) * (destMax - destMin); }


	// NOTE: PARTICLE CHECKING FUNCTION(s) (See what the particle can do)		
	void CheckParticleLifeTime(c_ParticleSystemObject& particle_system_object, float deltaTime);

	// NOTE: PARTICLE SPAWN AREA FUNCTION(s)
	void ProcessSpawnAreaNone(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaCircle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaRectangle(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaCapsule(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaDonut(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaEdge(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);
	void ProcessSpawnAreaCustom(OKTransform2<float> transform, c_ParticleSystemObject& particle_system_object);

	// NOTE: PARTICLE RESIZE FUNCTION(s)
	void ProcessResizeNone(c_ParticleSystemObject& particle_system_object, float deltaTime);
	void ProcessResizeOverLifeTime(c_ParticleSystemObject& particle_system_object, float deltaTime);
	void ProcessResizeVelocity(c_ParticleSystemObject& particle_system_object, float deltaTime);

	// NOTE: PARTICLE ACTION FUNCTION(s)
	void ProcessActionNone(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)

	void ProcessActionBurstOut(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)
	void ProcessActionBurstIn(c_ParticleSystemObject& particle_system_object);

	void ProcessActionScreen(c_ParticleSystemObject& particle_system_object); // Update Type: Constant (Done)
	void ProcessActionScreenOut(c_ParticleSystemObject& particle_system_object); // Update Type: Constant (Done)
	void ProcessActionScreenIn(c_ParticleSystemObject& particle_system_object); // Update Type: Constant (Done)

	// NOTE: Reverse these values when it comes to the game engine project
	void ProcessActionFall(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)
	void ProcessActionRise(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)
	void ProcessActionRight(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)
	void ProcessActionLeft(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)

	void ProcessActionSpray(c_ParticleSystemObject& particle_system_object); // TODO
	void ProcessActionSpiral(c_ParticleSystemObject& particle_system_object); // TODO

	void ProcessActionFire(c_ParticleSystemObject& particle_system_object); // Update Type: Constant (REWORK)
	void ProcessActionSmoke(c_ParticleSystemObject& particle_system_object); // Update Type: Once (REWORK)
	void ProcessActionSpark(c_ParticleSystemObject& particle_system_object); // Update Type: Once (Done)
	void ProcessActionWave(c_ParticleSystemObject& particle_system_object); // TODO

	void ProcessActionCustom(c_ParticleSystemObject& particle_system_object); // Update Type: Constant (Done)

	#pragma endregion

public:

	// CLASS FUNCTION(s)
	ParticleSystem() = default;
	ParticleSystem(OKVector2<float> position, float mass, unsigned int maxParticleCount, bool isLooping = true, ParticleType particleType = PARTICLE_TYPE_EMISSIVE, ParticleSpawnArea particleSpawnArea = PARTICLE_SPAWN_AREA_NONE, ParticleAction particleAction = PARTICLE_ACTION_NONE, float simulationSpeed = 1.f, bool simulateGravity = false);
	~ParticleSystem();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)

		// NOTE: PARTICLE CREATION FUNCTION(s)
		void CreateParticleSpawnArea(void (*particle_spawn_area_lambda)());
		void CreateParticleAction(void (*particle_action_lamda)());


		// NOTE: ASSIGN SPAWN AREA
		void AssignSpawnAreaNone();
		void AssignSpawnAreaCircle(float radius);
		void AssignSpawnAreaRectangle(float width, float height);
		void AssignSpawnAreaRectangle(OKVector2<float> scale);
		void AssignSpawnAreaCapsule(float width, float height);
		void AssignSpawnAreaCapsule(OKVector2<float> scale);
		void AssignSpawnAreaDonut(float outer_circle_radius, float inner_circle_radius);
		void AssignSpawnAreaCustom();


		// NOTE: ASSIGN PARTICLE ACTION
		void AssignParticleAction(ParticleAction particle_action);


		// NOTE: ASSIGN PARTICLE RESIZE
		void AssignVelocityOverLifeTime(OKVector2<float> starting_velocity_over_lifetime, OKVector2<float> ending_velocity_over_lifetime);
		void AssignForceOverLifeTime(OKVector2<float> starting_force_over_lifetime, OKVector2<float> ending_force_over_lifetime);
		void AssignResizeOverLifeTime(OKVector2<float> starting_resize_over_lifetime, OKVector2<float> ending_resize_over_lifetime);
		void AssignResizeByVelocityOverLifeTime(OKVector2<float> starting_resize_velocity_over_lifetime, OKVector2<float> ending_resize_velocity_over_lifetime);


		// NOTE: ASSIGN PARTICLE TYPE
		void AssignParticleType(ParticleType particle_type);


	// GETTER FUNCTION(s)

		inline OKTransform2<float> GetTransform() const { return m_Transform; }
		inline OKVector2<float> GetPosition() const { return m_Transform.position; }
		inline OKVector2<float> GetScale() const { return m_Transform.scale; }
		inline float GetRotation() const { return m_Transform.rotation; }

		inline unsigned int GetMaxParticleCount() const { return m_MaxParticleCount; }
		
		/// <summary> Getter function for the Particle Simulation Duration, 
		/// NOTE: Does not apply when Looping is TRUE 
		/// </summary>
		inline float GetParticleSimulationDuration() const { return m_ParticleSimulationDuration; }

		inline bool GetLooping() const { return m_IsLooping; }

		inline float GetStartDelay() const { return m_StartDelay; }
		inline float GetStartLifeTime() const { return m_StartLifeTime; }
		inline float GetStartSpeed() const { return m_StartSpeed; }
		inline OKVector2<float> GetStartSize() const { return m_StartSize; }

		inline OKVector2<float> GetGravity() const { return m_Gravity; }
		inline bool GetSimulateGravity() const { return m_SimulateGravity; }
		inline float GetSimulationSpeed() const { return m_SimulationSpeed; }

		inline unsigned int GetEmissionRateOverTime() const { return m_EmissionRateOverTime; }

		inline OKVector2<float> GetStartingVelocityOverLifeTime() const { return m_StartingVelocityOverLifeTime; }
		inline OKVector2<float> GetEndingVelocityOverLifeTime() const { return m_EndingVelocityOverLifeTime; }

		inline OKVector2<float> GetStartingForceOverLifeTime() const { return m_StartingForceOverLifeTime; }
		inline OKVector2<float> GetEndingForceOverLifeTime() const { return m_EndingForceOverLifeTime; }

		inline OKVector2<float> GetStartingSizeBySpeed() const { return m_StartingSizeByVelocity; }
		inline OKVector2<float> GetEndingSizeBySpeed() const { return m_EndingSizeByVelocity; }


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

		inline void SetDuration(float duration) { m_ParticleSimulationDuration = duration; }
		inline void SetStartDelay(float startDelay) { m_StartDelay = startDelay; }
		inline void SetStartLifeTime(float startLifeTime) { m_StartLifeTime = startLifeTime; }
		inline void SetStartSpeed(float startSpeed) { m_StartSpeed = startSpeed; }
		inline void SetStartSize(OKVector2<float> startSize) { m_StartSize = startSize; }

		inline void SetGravity(OKVector2<float> gravity) { m_Gravity = gravity; }

		
		inline void SetStartingVelocityOverLifeTime(OKVector2<float> startingVelocityOverLifeTime) { m_StartingVelocityOverLifeTime = startingVelocityOverLifeTime; }
		inline void SetEndingVelocityOverLifeTime(OKVector2<float> endingVelocityOverLifeTime) { m_EndingVelocityOverLifeTime = endingVelocityOverLifeTime; }

		
		inline void SetStartingForceOverLifeTime(OKVector2<float> startingForceOverLifeTime) { m_StartingForceOverLifeTime = startingForceOverLifeTime; }
		inline void SetEndingForceOverLifeTime(OKVector2<float> endingForceOverLifeTime) { m_EndingForceOverLifeTime = endingForceOverLifeTime; }

		
		inline void SetStartingSizeOverLifeTime(OKVector2<float> startingSizeOverLifeTime) { m_StartingSizeOverLifeTime = startingSizeOverLifeTime; }
		inline void SetEndingSizeOverLifeTime(OKVector2<float> endingSizeOverLifeTime) { m_EndingForceOverLifeTime = endingSizeOverLifeTime; }

		
		inline void SetStartingSizeBySpeed(OKVector2<float> startingSizeByVelocity) { m_StartingSizeByVelocity = startingSizeByVelocity; }
		inline void SetEndingSizeBySpeed(OKVector2<float> endingSizeByVelocity) { m_EndingSizeByVelocity = endingSizeByVelocity; }
};

#endif