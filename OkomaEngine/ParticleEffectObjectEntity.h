#ifndef PARTICLE_EFFECT_OBJECT_ENTITY_H
#define PARTICLE_EFFECT_OBJECT_ENTITY_H

#include "HeaderManager.h"
#include "OKVector4.h"
#include "OKVector2.h"
#include "GravityConstants.h"

class ParticleEffectObjectEntity
{
public:

	// NOTE: Force Effect
	float m_Mass;
	mutable OKVector2<float> m_Gravity; 

	OKVector2<float> m_NetForce{};
	OKVector2<float> m_Acceleration{};
	OKVector2<float> m_Velocity{};

	bool m_SimulateGravity = false;

	// NOTE: Particle Effect Object Specific Variables
	float* m_StartDelay; // NOTE: In Seconds
	float* m_StartLifeTime;
	float m_CurrentLifeTime;
	float* m_StartSpeed;
	float m_Theta;

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;
	float m_Rotation;

	OKVector4<unsigned int> m_Colour;

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

	OKVector4<unsigned int>* m_StartingColourOverLifeTime;
	OKVector4<unsigned int>* m_EndingColourOverLifeTime;
	float m_CurrentColourOverLifeTimer;

	// CLASS FUNCTION(s)
	ParticleEffectObjectEntity() = default;
	ParticleEffectObjectEntity(OKVector2<float> position, float mass);
	~ParticleEffectObjectEntity();


	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw() { };

	// PHYSICS FUNCTION(s)
	void ApplyImpulse(OKVector2<float> impulse) { m_Velocity += impulse; }
	void ApplyImpulse(float x, float y) { m_Velocity += OKVector2<float>(x, y); };

	void ApplyImpulseX(float impulseX) { m_Velocity += OKVector2<float>(impulseX, 0.0f); }
	void ApplyImpulseY(float impulseY) { m_Velocity += OKVector2<float>(0.0f, impulseY); }

	void ApplyForce(OKVector2<float> force) { m_NetForce += force; }
	void ApplyForce(float x, float y) { m_NetForce += OKVector2<float>(x, y); }

	void ApplyAcceleration(OKVector2<float> acceleration) { m_Acceleration += acceleration; }
	void ApplyAcceleration(float x, float y) { m_Acceleration += OKVector2<float>(x, y); }

	void CalculateAcceleration(const float deltaTime);

	// GETTER FUNCTION(s) : NOTE NEEDED 

	// SETTER FUNCTION(s) : NOT NEEDED

};

#endif