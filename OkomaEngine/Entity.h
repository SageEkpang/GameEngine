#ifndef ENTITY_H
#define ENTITY_H

// NOTE: INFORMATION ABOUT ECS (Entity Component System)
// https://github.com/SanderMertens/ecs-faq?tab=readme-ov-file#when-is-something-an-ecs

// Dense ECS or Table Based ECS
// Sparse ECS
// Bitset Based ECS

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include "ComponentEntity.h"

int constexpr MAX_COMPONENTS = 10;

class Entity
{
private: // PRIVATE VARIABLE(s)
	
	std::vector<ComponentEntity*> m_Components;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Entity();
	~Entity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);

	// HELPER FUNCTION(s)
	void AddComponent(ComponentEntity* component);
	void RemoveComponent(ComponentEntity* component);

};

#endif