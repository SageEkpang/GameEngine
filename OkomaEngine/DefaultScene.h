#ifndef DEFAULT_SCENE_H
#define DEFAULT_SCENE_H

// NOTE: Base Class
#include "SceneEntity.h"

class DefaultScene : public SceneEntity
{
private:


public:

	// CLASS FUNCTION(s)
	DefaultScene();
	~DefaultScene();


	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;

};

#endif