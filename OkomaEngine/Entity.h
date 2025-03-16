#ifndef ENTITY_H
#define ENTITY_H

// NOTE: INFORMATION ABOUT ECS (Entity Component System)
// https://github.com/SanderMertens/ecs-faq?tab=readme-ov-file#when-is-something-an-ecs

// Dense ECS or Table Based ECS
// Sparse ECS
// Bitset Based ECS

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include "Component.h"

class Entity
{
private: // PRIVATE VARIABLE(s)
	
	std::vector<Component*> m_Components;

public: // PUBLIC FUNCTION(s)

	// CLASS FUNCTION(s)
	Entity();
	~Entity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);

	void addComponent(Component* component);
	void removeComponent(Component* component);

};

#endif