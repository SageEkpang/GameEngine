#ifndef PARTICLE_SYSTEM_OBJECT_H
#define PARTICLE_SYSTEM_OBJECT_H

#include "Particle.h"
#include "OKVector3.h"

class c_ParticleSystemObject : public Particle
{
public:

	// NOTE: Both
	float* m_StartDelay; // NOTE: In Seconds
	float* m_StartLifeTime;
	float m_CurrentLifeTime;
	float* m_StartSpeed;
	float m_Theta;

	OKVector3<unsigned int> m_Colour;

	OKVector2<float>* m_StartSize;

	OKVector2<float>* m_StartingVelocityOverLifeTime;
	OKVector2<float>* m_EndingVelocityOverLifeTime;
	float m_CurrentVelocityOverLifeTimer; // NOTE: Used for Calculation above

	OKVector2<float>* m_StartingForceOverLifeTime;
	OKVector2<float>* m_EndingForceOverLifeTime;
	float m_CurrentForceOverLifeTimer;

	OKVector2<float>* m_StartingSizeOverLifeTime;
	OKVector2<float>* m_EndingSizeOverLifeTime;
	float m_CurrentSizeOverLifeTimer;

	OKVector2<float>* m_StartingSizeByVelocity;
	OKVector2<float>* m_EndingSizeByVelocity;
	float m_CurrentSizeByVelocity;

	OKVector3<unsigned int>* m_StartingColourOverLifeTime;
	OKVector3<unsigned int>* m_EndingColourOverLifeTime;
	float m_CurrentColourOverLifeTimer;

	// CLASS FUNCTION(s)
	c_ParticleSystemObject() = default;
	c_ParticleSystemObject(OKTransform2<float>* transform, float mass);
	~c_ParticleSystemObject();


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;

	// GETTER FUNCTION(s) : NOTE NEEDED 

	// SETTER FUNCTION(s) : NOT NEEDED

};

#endif