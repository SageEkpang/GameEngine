#ifndef LINE_COLLIDER_COMPONENT_H
#define LINE_COLLIDER_COMPONENT_H

#include "ColliderEntity.h"
#include "ComponentEntity.h"
#include "OKVector2.h"

class LineColliderComponent : public ColliderEntity, public ComponentEntity
{
public:

	OKVector2<float> m_LineStartPosition;
	OKVector2<float> m_LineEndPosition;

public:

	// CLASS FUNCTION(s)
	LineColliderComponent();

	LineColliderComponent(OKVector2<float> lineStartPosition, OKVector2<float> lineEndPosition);
	LineColliderComponent(OKVector2<float> lineStartPosition, float endX, float endY);
	LineColliderComponent(float startX, float startY, OKVector2<float> lineEndPosition);
	LineColliderComponent(float startX, float startY, float endX, float endY);

	~LineColliderComponent();


	// GETTER FUNCTION(s)

	inline OKVector2<float> GetLineStart() const { return m_LineStartPosition; }
	inline OKVector2<float> GetLineEnd() const { return m_LineEndPosition; }

	// SETTER FUNCTION(s)

	inline void SetLineStartPosition(OKVector2<float> lineStartPosition) { m_LineStartPosition = lineStartPosition; }
	inline void SetLineStartPosition(float startX, float startY) { m_LineStartPosition = OKVector2<float>(startX, startY); }

	inline void SetLineEndPosition(OKVector2<float> lineEndPosition) { m_LineEndPosition = lineEndPosition; }
	inline void SetLineEndPosition(float endX, float endY) { m_LineEndPosition = OKVector2<float>(endX, endY); }

};

#endif
