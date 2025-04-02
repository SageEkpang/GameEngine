#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "Particle.h"
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




public:

	// CLASS FUNCTION(s)
	ParticleSystem();
	~ParticleSystem();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// GETTER FUNCTION(s)


	// SETTER FUNCTION(s)

	ParticleSystem* GetInstance() { return this; }

};

#endif