#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"
#include "ComponentEntity.h"

class RectangleColliderComponent : public ColliderEntity, public ComponentEntity
{
public: // PUBLIC VARIABLE(s)

	OKVector2<float> m_Position;
	OKVector2<float> m_Scale;
	float m_Rotation;

public:

	// CLASS FUNCTION(s)
	RectangleColliderComponent();

	// NOTE: Axis Aligned Constructor
	RectangleColliderComponent(OKVector2<float> position, OKVector2<float> scale);
	RectangleColliderComponent(OKVector2<float> position, float width, float height);

	RectangleColliderComponent(float x, float y, OKVector2<float> scale);
	RectangleColliderComponent(float x, float y, float width, float height);


	// NOTE: Oriented Constructor
	RectangleColliderComponent(OKVector2<float> position, OKVector2<float> scale, float rotation);
	RectangleColliderComponent(OKVector2<float> position, float width, float height, float rotation);

	RectangleColliderComponent(float x, float y, OKVector2<float> scale, float rotation);
	RectangleColliderComponent(float x, float y, float width, float height, float rotation);

	~RectangleColliderComponent();


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;


	// GETTER FUNCTION(s)

	inline OKTransform2<float> GetTransform() { return OKTransform2<float>(m_Position, m_Scale, m_Rotation); }
	inline OKVector2<float> GetPosition() { return m_Position; }
	inline OKVector2<float> GetScale() { return m_Scale; }
	inline float GetRotation() { return m_Rotation; }


	// SETTER FUNCTION(s)
	inline void SetTransform(OKTransform2<float> transform) { m_Position = transform.position; m_Scale = transform.scale; m_Rotation = transform.rotation; }
	inline void SetTransform(OKVector2<float> position, OKVector2<float> scale, float rotation) { m_Position = position; m_Scale = scale; m_Rotation = rotation; }
	inline void SetTransform(float x, float y, float width, float height, float rotation) { m_Position = OKVector2<float>(x, y); m_Scale = OKVector2<float>(width, height); m_Rotation = rotation; }

	inline void SetPosition(OKVector2<float> position) { m_Position = position; }
	inline void SetPosition(float x, float y) { m_Position = OKVector2<float>(x, y); }

	inline void SetScale(OKVector2<float> scale) { m_Scale = scale; }
	inline void SetScale(float width, float height) { m_Scale = OKVector2<float>(width, height); }

	inline void SetRotation(float rotation) { m_Rotation = rotation; }

};

#endif