#ifndef TEST_SCENE_H
#define TEST_SCENE_H

#include "GameObjectEntity.h"
#include "PhysicsManager.h"

// NOTE: Base Class
#include "SceneEntity.h"

class TestScene : public SceneEntity
{
private:

	GameObjectEntity CircleObjectTwo;
	GameObjectEntity m_Floor;
	PhysicsManager m_PhyMana;

public:

	// CLASS FUNCTION(s)
	TestScene();
	~TestScene() override;

	// BASE FUNCTION(s)
	void Update(const float deltaTime) override;
	void Draw() override;

};

#endif

