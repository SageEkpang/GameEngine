#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

// NOTE: Needed include
#include "HeaderManager.h"
#include "ComponentEntity.h"
#include "OKVector2.h"
#include "OKVector4.h"

class RenderComponent : public ComponentEntity
{
private:

	Texture2D m_Image;

public:

	OKVector2<float> m_Offset = OKVector2<float>();

	float m_Width;
	float m_Height;

	bool m_IsAnimation = false;

	OKVector4<unsigned int> m_ColourTint = OKVector4<unsigned int>(255u, 255u, 255u, 255u);

public:

	// CLASS FUNCTION(s) (General)
	RenderComponent();
	~RenderComponent() override;


	// CLASS FUNCTION(s) (Components)
	void Construct();
	void Construct(int width, int height);

	void Construct(const char* imageName);
	void Construct(const char* imageName, int width, int height);


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;


	// GETTER FUNCTION(s) : NOT NEEDED

	// SETTER FUNCTION(s) : NOT NEEDED

};

#endif