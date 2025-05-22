#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#include "PhysicsEntity.h"
#include "ParticleEffectObjectEntity.h"
#include "ComponentEntity.h"
#include "OKVector3.h"

#include "OKMaths.h"
#include <memory>
#include <utility>
#include <map>
#include <cmath>
#include <random>
#include <map>

// NOTE: In the collab project, rendering will have to be included here as well

enum ParticleSpawnArea
{
	PARTICLE_SPAWN_AREA_NONE,
	PARTICLE_SPAWN_AREA_CIRCLE,
	PARTICLE_SPAWN_AREA_RECTANGLE,
	PARTICLE_SPAWN_AREA_CAPSULE,
	PARTICLE_SPAWN_AREA_SPRAY,
	PARTICLE_SPAWN_AREA_DONUT,
	PARTICLE_SPAWN_AREA_EDGE,
	PARTICLE_SPAWN_AREA_CUSTOM
};

// TODO: Change this to the prefab actions instead of action functions
enum ParticleAction
{
	PARTICLE_ACTION_NONE,
	PARTICLE_ACTION_BURST_OUT,
	PARTICLE_ACTION_BURST_IN,

	PARTICLE_ACTION_FALL,
	PARTICLE_ACTION_RISE,
	PARTICLE_ACTION_RIGHT,
	PARTICLE_ACTION_LEFT,

	PARTICLE_ACTION_SPRAY,

	PARTICLE_ACTION_CUSTOM
};

enum ParticleEmitterType
{
	PARTICLE_EMITTER_TYPE_SINGLE,
	PARTICLE_EMITTER_TYPE_MULTIPLE
};

enum ParticleResize
{
	PARTICLE_RESIZE_NONE,
	PARTICLE_RESIZE_OVER_LIFETIME,
	PARTICLE_RESIZE_VELOCITY
};

enum ParticlePhysicsOverLifeTime
{
	PARTICLE_PHYSICS_NONE,
	PARTICLE_PHYSICS_FORCE_OVER_LIFETIME,
	PARTICLE_PHYSICS_VELOCITY_OVER_LIFETIME
};

enum ParticleColourOverLifeTime
{
	PARTICLE_COLOUR_NONE,
	PARTICLE_COLOUR_OVER_LIFE_TIME,
	PARTICLE_COLOUR_VELOCITY_OVER_LIFE_TIME
};

class ParticleEffectComponent : public ComponentEntity
{
private:

	// NOTE: PTR TYPEDEF FOR FUNCTION(s)

	typedef void (ParticleEffectComponent::* CheckParticleActionFunctionPtr)(ParticleEffectObjectEntity&);
	std::map<ParticleAction, CheckParticleActionFunctionPtr> m_ParticleActionMap;

	typedef void (ParticleEffectComponent::* CheckParticleSpawnFunctionPtr)(OKTransform2<float>, ParticleEffectObjectEntity&);
	std::map<ParticleSpawnArea, CheckParticleSpawnFunctionPtr> m_ParticleSpawnMap;

	typedef void (ParticleEffectComponent::* CheckParticleResizeFunctionPtr)(ParticleEffectObjectEntity&, float);
	std::map<ParticleResize, CheckParticleResizeFunctionPtr> m_ParticleResizeMap;

	typedef void (ParticleEffectComponent::* CheckParticlePhysicsFunctionPtr)(ParticleEffectObjectEntity&, float);
	std::map<ParticlePhysicsOverLifeTime, CheckParticlePhysicsFunctionPtr> m_ParticlePhysicsOverTimeMap;

	typedef void (ParticleEffectComponent::* CheckParticleColourFunctionPtr)(ParticleEffectObjectEntity&, float);
	std::map<ParticleColourOverLifeTime, CheckParticleColourFunctionPtr> m_ParticleColourOverTimerMap;

	// CUSTOM DATA TYPE
	void (*m_CustomParticleActionFunctionPtr)() = nullptr;
	void (*m_CustomParticleSpawnAreaFunctionPtr)() = nullptr;

	void (ParticleEffectComponent::* m_CheckParticleActionFunctionPtr)(ParticleEffectObjectEntity&) = nullptr;
	void (ParticleEffectComponent::* m_CheckParticleSpawnFunctionPtr)(OKTransform2<float>, ParticleEffectObjectEntity&) = nullptr;
	void (ParticleEffectComponent::* m_CheckParticleResizingFunctionPtr)(ParticleEffectObjectEntity&, float) = nullptr;
	void (ParticleEffectComponent::* m_CheckParticlePhysicsOverTimeFunctionPtr)(ParticleEffectObjectEntity&, float) = nullptr;
	void (ParticleEffectComponent::* m_CheckParticleColourOverTimerFunctionPtr)(ParticleEffectObjectEntity&, float);

	// TRANSFORM VARIABLE(s)
	OKTransform2<float> m_Transform;
	OKVector2<float> m_EmitterPositionOffset;

	// PARTICLE VARIABLE(s)
	ParticleEffectObjectEntity* m_DefaultParticle;
	std::vector<ParticleEffectObjectEntity> m_SimulatingParticles;
	unsigned int m_ParticleIndexIncrement;

	// PARTICLE EXCUTE ONCE
	// NOTE: This assumes to be used with the "NOT" looping
	bool m_ExecuteOnce = false;

	ParticleSpawnArea m_ParticleSpawnArea;
	ParticleAction m_ParticleAction;
	ParticleEmitterType m_ParticleEmitterType;

	// BASE VARIABLE(s)
	unsigned int m_MaxParticleCount;

	// NOTE: Setting Variable(s)
	float m_StartDelay;
	float m_StartLifeTime;
	float m_StartSpeed;
	OKVector2<float> m_StartSize;


	// NOTE: For NOT Looping
	float m_ParticleTimer;
	float m_ParticleSimulationDuration;
	bool m_IsLooping;

	OKVector2<float> m_Gravity;
	bool m_SimulateGravity;
	float m_SimulationSpeed;

	// EMISSION VARIABLE(s)
	float m_EmissionTimer = 0.0f;
	unsigned int m_EmissionRateOverTime;

public:

	// TODO: Move Variables here some way, some how




public: // PARTICLE OVERTIME VARIABLE(s)

	#pragma region PARTICLE OVERTIME VARIABLE(s)

	OKVector2<float> m_StartingVelocityOverLifeTime;
	OKVector2<float> m_EndingVelocityOverLifeTime;

	OKVector2<float> m_StartingForceOverLifeTime;
	OKVector2<float> m_EndingForceOverLifeTime;

	OKVector2<float> m_StartingSizeOverLifeTime;
	OKVector2<float> m_EndingSizeOverLifeTime;

	OKVector2<float> m_StartingSizeByVelocity;
	OKVector2<float> m_EndingSizeByVelocity;

	float m_MaxVelocityBySize;
	float m_MinVelocityBySize;

	OKVector3<unsigned int> m_StartingColourOverLifeTime;
	OKVector3<unsigned int> m_EndingColourOverLifeTime;

	float m_MaxVelocityByColour;
	float m_MinVelocityByColour;

	#pragma endregion

private: // SPAWN AREA VARIABLE(s)

	#pragma region PRIVATE SPAWN AREA VARIABLE(s)

	float m_CircleRadius = 0.0f;
	OKVector2<float> m_RectangleScale{ 0.f, 0.f};

	float m_InnerDonutScale = 0.0f;
	float m_OuterDonutScale = 0.0f;

	float m_CapsuleHeight = 0.0f;
	float m_CapsuleWidth = 0.0f;

	float m_EdgeLength = 0.0f;

	float m_SprayAngle = 0.0f;
	float m_SprayLength = 0.0f;
	OKVector2<float> m_SprayDirection{0.f, -1.0f};

	#pragma endregion

private: // PRIVATE FUNCTION(s)

	#pragma region PRIVATE PROCESS FUNCTIONS

	// LOCAL MATHS FUNCTION(s)
	float lerp(float a, float b, float f) { return (a * (1.0f - f)) + (b * f); }
	float remap(float value, float sourceMin, float sourceMax, float destMin = 0, float destMax = 1) { return destMin + ((value - sourceMin) / (sourceMax - sourceMin)) * (destMax - destMin); }

	// NOTE: PARTICLE CHECKING FUNCTION(s) (See what the particle can do)		
	void CheckParticleLifeTime(ParticleEffectObjectEntity& particle_system_object, float deltaTime);

	// NOTE: PARTICLE SPAWN AREA FUNCTION(s)
	void ProcessSpawnAreaNone(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaCircle(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaRectangle(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaCapsule(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaDonut(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaEdge(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaCustom(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);
	void ProcessSpawnAreaSpray(OKTransform2<float> transform, ParticleEffectObjectEntity& particle_system_object);

	// NOTE: PARTICLE RESIZE FUNCTION(s)
	void ProcessResizeNone(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessResizeOverLifeTime(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessResizeVelocity(ParticleEffectObjectEntity& particle_system_object, float deltaTime);

	// NOTE: PARTICLE PHYSICS OVER TIME FUNCTION(s)
	void ProcessPhysicsOverLifeTimeNone(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessPhysicsOverLifeTimeForce(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessPhysicsOverLifeTimeVelocity(ParticleEffectObjectEntity& particle_system_object, float deltaTime);

	// NOTE: PARTICLE COLOUR OVER TIME FUNCTION(s) 
	void ProcessColourNone(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessColourOverLifeTime(ParticleEffectObjectEntity& particle_system_object, float deltaTime);
	void ProcessColourOverVelocity(ParticleEffectObjectEntity& particle_system_object, float deltaTime);


	// NOTE: PARTICLE ACTION FUNCTION(s)
	void ProcessActionNone(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)

	void ProcessActionBurstOut(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)
	void ProcessActionBurstIn(ParticleEffectObjectEntity& particle_system_object);

	// NOTE: Reverse these values when it comes to the game engine project
	void ProcessActionFall(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)
	void ProcessActionRise(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)
	void ProcessActionRight(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)
	void ProcessActionLeft(ParticleEffectObjectEntity& particle_system_object); // Update Type: Once (Done)

	void ProcessActionSpray(ParticleEffectObjectEntity& particle_system_object); // TODO

	void ProcessActionCustom(ParticleEffectObjectEntity& particle_system_object); // Update Type: Constant (Done)

	#pragma endregion

public:

	// CLASS FUNCTION(s)
	ParticleEffectComponent() { }
	void Construct(OKVector2<float> position, unsigned int maxParticleCount, ParticleEmitterType particleEmitterType = PARTICLE_EMITTER_TYPE_SINGLE, ParticleSpawnArea particleSpawnArea = PARTICLE_SPAWN_AREA_NONE, ParticleAction particleAction = PARTICLE_ACTION_NONE, float mass = 1.f, bool isLooping = false, float simulationSpeed = 1.f, bool simulateGravity = false);
	
	~ParticleEffectComponent();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)

		// NOTE: Prefab Particle Effects
		void PrefabFire();
		void PrefabSmoke();
		void PrefabSmokeScreen();
		void PrefabSmokeScreenOut();
		void PrefabWaterFall();

		// NOTE: Process the Particles
		void ProcessParticleToSimulatingParticles();

		// NOTE: PARTICLE CREATION FUNCTION(s)
		void CreateParticleSpawnArea(void (*particle_spawn_area_lambda)());
		void CreateParticleAction(void (*particle_action_lamda)());


		// NOTE: ASSIGN SPAWN AREA
		void AssignParticleSpawnAreaNone();
		void AssignParticleSpawnAreaCircle(float radius);
		void AssignParticleSpawnAreaRectangle(float width, float height);
		void AssignParticleSpawnAreaRectangle(OKVector2<float> scale);
		void AssignParticleSpawnAreaCapsule(float width, float height);
		void AssignParticleSpawnAreaCapsule(OKVector2<float> scale);
		void AssignParticleSpawnAreaDonut(float outer_circle_radius, float inner_circle_radius);
		void AssignParticleSpawnAreaEdge(float m_edge_length);
		void AssignParticleSpawnAreaSpray(float spray_angle, float spray_length, OKVector2<float> spray_direction);
		void AssignParticleSpawnAreaCustom();


		// NOTE: ASSIGN PARTICLE ACTION
		void AssignParticleAction(ParticleAction particle_action);

		// NOTE: ASSIGN PARTICLE PHYSICS OVER LIFE TIME
		void AssignVelocityOverLifeTime(OKVector2<float> starting_velocity_over_lifetime, OKVector2<float> ending_velocity_over_lifetime);
		void AssignForceOverLifeTime(OKVector2<float> starting_force_over_lifetime, OKVector2<float> ending_force_over_lifetime);
		
		// NOTE: ASSIGN PARTICLE RESIZE
		void AssignResizeOverLifeTime(OKVector2<float> starting_resize_over_lifetime, OKVector2<float> ending_resize_over_lifetime);
		void AssignResizeByVelocityOverLifeTime(OKVector2<float> starting_resize_velocity_over_lifetime, OKVector2<float> ending_resize_velocity_over_lifetime, float max_velocity_by_size, float min_velocity_by_size);

		// NOTE: ASSIGN PARTICLE COLOUR
		void AssignColourOverLifeTime(OKVector3<unsigned int> starting_colour_over_lifetime, OKVector3<unsigned int> ending_colour_over_lifetime);
		void AssignColourVelocityOverLifeTime(OKVector3<unsigned int> starting_colour_over_lifetime, OKVector3<unsigned int> ending_colour_over_lifetime, float max_velocity_by_colour, float min_velocity_by_colour);


		// NOTE: ASSIGN PARTICLE TYPE
		void AssignParticleEmitterType(ParticleEmitterType particle_emitter_type);


	// GETTER FUNCTION(s)

	#pragma region Getter Functions

		inline OKTransform2<float> GetTransform() const { return m_Transform; }
		inline OKVector2<float> GetPosition() const { return m_Transform.position; }
		inline OKVector2<float> GetScale() const { return m_Transform.scale; }
		inline float GetRotation() const { return m_Transform.rotation; }

		inline unsigned int GetMaxParticleCount() const { return m_MaxParticleCount; }
		
		inline bool GetExecuteOnce() const { return m_ExecuteOnce; }

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

	#pragma endregion


	// SETTER FUNCTION(s)

	#pragma region Setter Functions

		// BASE FUNCTION(s)
		inline void SetTransform(OKTransform2<float> transform) { m_Transform = transform; }
		inline void SetEmitterOffset(OKVector2<float> emitter_position_offset) { m_EmitterPositionOffset = emitter_position_offset; }
		inline void SetPosition(OKVector2<float> position) { m_Transform.position = position; }
		inline void SetScale(OKVector2<float> scale) { m_Transform.scale = scale; }
		inline void SetRotation(float rotation) { m_Transform.rotation = rotation; }
			
		// PARTICLE SYSTEM FUNCTION(s)
		inline void SetMaxParticleCount(unsigned int maxParticleCount) { m_MaxParticleCount = maxParticleCount; }
		inline void SetExecuteOnce(bool executeOnce) { m_ExecuteOnce = executeOnce; }
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

	#pragma endregion

};

#endif