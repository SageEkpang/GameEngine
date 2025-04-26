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

	OKVector2<float>* startingSizeBySpeed;
	OKVector2<float>* endingSizeBySpeed;
	OKVector2<float> currentSizeBySpeed;

	c_ParticleSystemObject() = default;
	c_ParticleSystemObject(OKTransform2<float> transform, float mass)
	{
		this->transform = transform;
		particle = Particle(&this->transform, mass);

		startDelay = nullptr;
		startLifeTime = nullptr;
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

		startingSizeBySpeed = nullptr;
		endingSizeBySpeed = nullptr;
		currentSizeBySpeed = OKVector2<float>(1.0f, 1.0f);
	}
};

#endif