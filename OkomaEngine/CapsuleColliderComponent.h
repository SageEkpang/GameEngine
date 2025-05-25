#ifndef CAPSULE_COLLIDER_COMPONENT_H
#define CAPSULE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class CapsuleColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_Offset;

	float m_Height;
	float m_Width;

	bool m_IsHorizontal = false;

public:

	// CLASS FUNCTION(s) (Components)
	CapsuleColliderComponent(OKVector2<float> offset, OKVector2<float> scale);
	CapsuleColliderComponent(OKVector2<float> offset, float width, float height);
	CapsuleColliderComponent(float x, float y, OKVector2<float> scale);
	CapsuleColliderComponent(float x, float y, float width, float height);

	CapsuleColliderComponent(OKVector2<float> scale);
	CapsuleColliderComponent(float width, float height);
	
	// CLASS FUNCTION(s) (General)
	CapsuleColliderComponent();

	void Construct(OKVector2<float> offset, OKVector2<float> scale);
	void Construct(OKVector2<float> offset, float width, float height);
	void Construct(float x, float y, OKVector2<float> scale);
	void Construct(float x, float y, float width, float height);

	void Construct(OKVector2<float> scale);
	void Construct(float width, float height);

	~CapsuleColliderComponent();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif
