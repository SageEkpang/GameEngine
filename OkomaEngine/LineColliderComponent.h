#ifndef LINE_COLLIDER_COMPONENT_H
#define LINE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "OKVector2.h"

class LineColliderComponent : public ColliderEntity
{
public:

	OKVector2<float> m_LineStartPosition;
	OKVector2<float> m_LineEndPosition;

public:

	// CLASS FUNCTION(s) (General)
	LineColliderComponent(OKVector2<float> lineStartPosition, OKVector2<float> lineEndPosition);
	LineColliderComponent(OKVector2<float> lineStartPosition, float endX, float endY);
	LineColliderComponent(float startX, float startY, OKVector2<float> lineEndPosition);
	LineColliderComponent(float startX, float startY, float endX, float endY);

	// CLASS FUNCTION(s) (Components)
	LineColliderComponent();

	void Construct(OKVector2<float> lineStartPosition, OKVector2<float> lineEndPosition);
	void Construct(OKVector2<float> lineStartPosition, float endX, float endY);
	void Construct(float startX, float startY, OKVector2<float> lineEndPosition);
	void Construct(float startX, float startY, float endX, float endY);

	~LineColliderComponent();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif
