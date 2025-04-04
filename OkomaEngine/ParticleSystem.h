#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
#include <memory>
#include <vector>
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
	PARTICLE_SPAWN_HALF_CIRCLE,
	PARTICLE_SPAWN_AREA_RECTANGLE,
	PARTICLE_SPAWN_AREA_TRIANGLE,
	PARTICLE_SPAWN_AREA_CAPSULE,
	PARTICLE_SPAWN_AREA_DONUT,
	PARTICLE_SPAWN_AREA_EDGE,
};

enum ParticleAction
{
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

	// PARTICLE VARIABLE(s)
	std::vector<Particle> m_Particles;

	// BASE VARIABLE(s)
	unsigned int m_MaxParticleCount;
	float m_Duration = { 1.0f };
	bool m_IsLooping{ false };
	float m_StartDelay{ 0.0f }; // NOTE: In Seconds
	float m_StartLiftTime{ 5.0f };
	float m_StartSpeed{ 5.0f };
	float m_StartSize{ 1.0f };
	OKVector2<float> m_Gravity{ 0.0f, 0.0f };
	bool m_SimulateGravity{ false };
	float m_SimulationSpeed{ 1.0f };


	// EMISSION VARIABLE(s)
	unsigned int m_RateOverTimer{ 5.0 };
	unsigned int m_RateOverDistance{ 1.0 };


	// SHAPE VARIABE(s)
	ParticleSpawnArea m_ParticleSpawnArea;

	// NOTE: These will overwrite previous variables that were set

	// VELOCITY OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingVelocityOverLiftTime;
	OKVector2<float> m_EndingVelocityOverLiftTime;

	// FORCE OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingForceOverLifeTime;
	OKVector2<float> m_EndingForceOverLifeTime;


	// SIZE OVER LIFE TIME VARIABLE(s)
	OKVector2<float> m_StartingSizeOverLiftTime;
	OKVector2<float> m_EndingSizeOverLiftTime;

	// SIZE BY SPEED VARIABLE(s) --> Links to Variables Above
	float m_StartingSizeBySpeed;
	float m_EndingSizeBySpeed;

	// COLLISION
	bool m_HasCollision;

public:

	// CLASS FUNCTION(s)
	ParticleSystem(int maxParticleCount);
	~ParticleSystem();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// GETTER FUNCTION(s)


	// SETTER FUNCTION(s)

	//ParticleSystem* GetInstance() { return this; }

};

#endif