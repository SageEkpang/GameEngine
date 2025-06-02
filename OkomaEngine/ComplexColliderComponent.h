#ifndef COMPLEX_COLLIDER_COMPONENT_H
#define COMPLEX_COLLIDER_COMPONENT_H

// PARENT INCLUDE(s)
#include "ColliderEntity.h"

// NOTE: File Loading
#include "OKVector2.h"
#include <fstream>
#include <vector>

// NOTE: Resource notes
// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

// TODO: NEED TO FINISH THIS CLASS
class ComplexColliderComponent : public ColliderEntity
{
public:

	// BASE VARIABLE(s)
	OKVector2<float> m_Offset;
	OKVector2<float> m_Scale;
	float m_Rotation;

	// FILE VARIABLE(s)
	const char* m_FileName;
	std::vector<OKVector2<float>> m_Vertices;

public:

	// CLASS FUNCTION(s) (General)
	ComplexColliderComponent(const char* fileName);
	ComplexColliderComponent(const char* fileName, float sizeOffset);
	ComplexColliderComponent(const char* fileName, OKVector2<float> offset);
	ComplexColliderComponent(const char* fileName, OKVector2<float> offset, float sizeOffset);

	// CLASS FUNCTION(s) (Components)
	ComplexColliderComponent();

	void Construct(const char* fileName);
	void Construct(const char* fileName, float sizeOffset);
	void Construct(const char* fileName, OKVector2<float> offset);
	void Construct(const char* fileName, OKVector2<float> offset, float sizeOffset);

	~ComplexColliderComponent() override;

	// BASE FUNCTION(s)
	float PolygonArea();

	// GETTER FUNCTION(s) // NOT NEEDED

	// SETTER FUNCTION(s) // NOT NEEDED

};

#endif