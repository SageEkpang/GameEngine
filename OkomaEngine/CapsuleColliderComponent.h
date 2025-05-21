#ifndef CAPSULE_COLLIDER_COMPONENT_H
#define CAPSULE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "ComponentEntity.h"
#include "OKTransform2.h"
#include "OKVector2.h"

class CapsuleColliderComponent : public ColliderEntity, public ComponentEntity
{
public:

	OKVector2<float> m_Position;

	float m_Height;
	float m_Width;

	bool m_IsHorizontal;
	float m_Rotation;

public:

	// CLASS FUNCTION(s)
	CapsuleColliderComponent();

	// NOTE: Axis Aligned Constructor
	CapsuleColliderComponent(OKVector2<float> position, OKVector2<float> scale);
	CapsuleColliderComponent(OKVector2<float> position, float width, float height);

	CapsuleColliderComponent(float x, float y, OKVector2<float> scale);
	CapsuleColliderComponent(float x, float y, float width, float height);

	// NOTE: Oriented Constructor

	CapsuleColliderComponent(OKVector2<float> position, OKVector2<float> scale, float rotation);
	CapsuleColliderComponent(OKVector2<float> position, float width, float height, float rotation);

	CapsuleColliderComponent(float x, float y, OKVector2<float> scale, float rotation);
	CapsuleColliderComponent(float x, float y, float width, float height, float rotation);

	~CapsuleColliderComponent();


	// GETTER FUNCTION(s)

	//inline OKTransform2<float> GetTransform() { return OKTransform2<float>(m_Position, m_Scale, m_Rotation); }
	//inline OKVector2<float> GetPosition() { return m_Position; }
	//inline OKVector2<float> GetScale() { return m_Scale; }
	//inline float GetRotation() { return m_Rotation; }


	// SETTER FUNCTION(s)
	//inline void SetTransform(OKTransform2<float> transform) { m_Position = transform.position; m_Scale = transform.scale; m_Rotation = transform.rotation; }
	//inline void SetTransform(OKVector2<float> position, OKVector2<float> scale, float rotation) { m_Position = position; m_Scale = scale; m_Rotation = rotation; }
	//inline void SetTransform(float x, float y, float width, float height, float rotation) { m_Position = OKVector2<float>(x, y); m_Scale = OKVector2<float>(width, height); m_Rotation = rotation; }

	//inline void SetPosition(OKVector2<float> position) { m_Position = position; }
	//inline void SetPosition(float x, float y) { m_Position = OKVector2<float>(x, y); }

	//inline void SetScale(OKVector2<float> scale) { m_Scale = scale; }
	//inline void SetScale(float width, float height) { m_Scale = OKVector2<float>(width, height); }

	//inline void SetRotation(float rotation) { m_Rotation = rotation; }

};

#endif
