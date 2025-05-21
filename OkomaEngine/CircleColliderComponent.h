#ifndef CIRCLE_COLLIDER_COMPONENT_H
#define CIRCLE_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "ComponentEntity.h"

class CircleColliderComponent : public ColliderEntity, public ComponentEntity
{
public:

	OKVector2<float> m_Position;
	float m_Radius;

public:

	// CLASS FUNCTION(s)
	CircleColliderComponent();

	CircleColliderComponent(OKVector2<float> position, float radius);
	CircleColliderComponent(float x, float y, float radius);

	~CircleColliderComponent();


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;


	// GETTER FUNCTION(s)
	inline OKVector2<float> GetPosition() { return m_Position; }
	inline float GetRadius() { return m_Radius; }


	// SETTER FUNCTION(s)
	inline void SetPosition(OKVector2<float> position) { m_Position = position; }
	inline void SetPosition(float x, float y) { m_Position = OKVector2<float>(x, y); }
	
	inline void SetRadius(float radius) { m_Radius = radius; }

};

#endif