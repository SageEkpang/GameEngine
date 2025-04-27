#ifndef PARTICLE_SYSTEM_OBJECT_H
#define PARTICLE_SYSTEM_OBJECT_H

#include "Particle.h"

struct c_ParticleSystemObject
{
	Particle particle;
	OKTransform2<float> transform;

	// NOTE: Both
	float* startDelay; // NOTE: In Seconds
	float* startLifeTime;
	float currentLifeTime;
	float* startSpeed;
	float theta;

	OKVector2<float>* startSize;
	OKVector2<float>* gravity;

	OKVector2<float>* startingVelocityOverLifeTime;
	OKVector2<float>* endingVelocityOverLifeTime;
	float currentVelocityOverLifeTimer; // NOTE: Used for Calculation above

	OKVector2<float>* startingForceOverLifeTime;
	OKVector2<float>* endingForceOverLifeTime;
	float currentForceOverLifeTimer;

	OKVector2<float>* startingSizeOverLifeTime;
	OKVector2<float>* endingSizeOverLifeTime;
	float currentSizeOverLifeTimer;

	OKVector2<float>* startingSizeByVelocity;
	OKVector2<float>* endingSizeByVelocity;
	float currentSizeByVelocity;

	c_ParticleSystemObject() = default;
	c_ParticleSystemObject(OKTransform2<float> transform, float mass)
	{
		this->transform = transform;
		particle = Particle(&this->transform, mass);

		startDelay = nullptr;
		startLifeTime = nullptr;
		currentLifeTime = 0.0f;
		startSpeed = nullptr;
		theta = 0.f;

		startSize = nullptr;
		gravity = nullptr;

		startingVelocityOverLifeTime = nullptr;
		endingVelocityOverLifeTime = nullptr;
		currentVelocityOverLifeTimer = 0.0f;

		startingForceOverLifeTime = nullptr;
		endingForceOverLifeTime = nullptr;
		currentForceOverLifeTimer = 0.0f;

		startingSizeOverLifeTime = nullptr;
		endingSizeOverLifeTime = nullptr;
		currentSizeOverLifeTimer = 0.0f;

		startingSizeByVelocity = nullptr;
		endingSizeByVelocity = nullptr;
		currentSizeByVelocity = 0.0f;
	}
};

#endif