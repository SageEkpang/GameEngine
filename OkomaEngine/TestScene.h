#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "GameObjectEntity.h"
#include "PhysicsManager.h"

// NOTE: Base Class
#include "SceneEntity.h"

class TestScene : public SceneEntity
{
private:

	GameObjectEntity m_OtherObject;
	GameObjectEntity m_CircleObjectTwo;
	GameObjectEntity m_ExtraObject;
	GameObjectEntity m_Floor;

public:

	// CLASS FUNCTION(s)
	TestScene();
	~TestScene() override;

	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;

};

#endif

