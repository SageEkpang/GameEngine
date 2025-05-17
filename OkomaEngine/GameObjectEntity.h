#ifndef GAME_OBJECT_ENTITY_H
#define GAME_OBJECT_ENTITY_H

// NOTE: INFORMATION ABOUT ECS (Entity Component System)
// https://github.com/SanderMertens/ecs-faq?tab=readme-ov-file#when-is-something-an-ecs

// Dense ECS or Table Based ECS
// Sparse ECS
// Bitset Based ECS

#include "HeaderManager.h"
#include "ComponentEntity.h"

#include <optional>
#include <vector>

unsigned int constexpr MAX_COMPONENTS = 10u;

class GameObjectEntity
{
private:

	std::vector<ComponentEntity*> m_Components;

public:

	// CLASS FUNCTION(s)
	GameObjectEntity();
	~GameObjectEntity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// HELPER FUNCTION(s)
	void AddComponent();
	void RemoveComponent();
	bool HasComponent();

};

#endif