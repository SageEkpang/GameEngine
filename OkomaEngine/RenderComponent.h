#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

// NOTE: Needed include
#include "HeaderManager.h"
#include "ComponentEntity.h"

class RenderComponent : public ComponentEntity
{
private:

	Texture2D m_Image;
	int m_Width;
	int m_Height;

	bool m_IsAnimation = false;

public:

	// CLASS FUNCTION(s) (General)
	RenderComponent();
	~RenderComponent() override;


	// CLASS FUNCTION(s) (Components)
	void Construct(Texture2D image, int width, int height);


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;


	// GETTER FUNCTION(s) : NOT NEEDED

	// SETTER FUNCTION(s) : NOT NEEDED

};

#endif