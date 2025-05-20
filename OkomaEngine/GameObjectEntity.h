#ifndef GAME_OBJECT_ENTITY_H
#define GAME_OBJECT_ENTITY_H

// NOTE: INFORMATION ABOUT ECS (Entity Component System)
// https://github.com/SanderMertens/ecs-faq?tab=readme-ov-file#when-is-something-an-ecs

// Dense ECS or Table Based ECS
// Sparse ECS
// Bitset Based ECS

#include "HeaderManager.h"
#include "ComponentEntity.h"
#include "OKTransform2.h"

#include <unordered_map>
#include <bitset>
#include <typeindex>
#include <typeinfo>

unsigned int constexpr MAX_COMPONENTS = 8u;

// DERIVED COMPONENT CLASSE(s)
class RectangleColliderComponent;
class SphereColliderComponent;
class CapsuleColliderComponent;
class LineColliderComponent;

class ParticleEffectComponent;
class Rigidbody2DComponent;

class CameraComponent;
// ---------------------------------

class GameObjectEntity
{
private:

	// BASE COMPONENT VARIABLE(s)
	unsigned int m_ComponentIndex = 0u;
	std::bitset<MAX_COMPONENTS> m_ComponentBitMask;

	// COMPONENT ARRAY(s)
	std::unordered_map<std::type_index, ComponentEntity*> m_Components;

public:

	// CLASS FUNCTION(s)
	GameObjectEntity();
	~GameObjectEntity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)

	template<typename T>
	void AddComponent();

	template<typename T>
	void RemoveComponent();

	template<typename T>
	T* GetComponent();

	template<typename T>
	bool HasComponent();

};

template<typename T>
inline void GameObjectEntity::AddComponent()
{
	try
	{
		++m_ComponentIndex;
		if (m_ComponentIndex > MAX_COMPONENTS)
		{
			m_Components = MAX_COMPONENTS;
			throw;
		}
	}
	catch (...)
	{
		printf("Max Component count has been reached");
		return;
	}
	
	m_Components[std::type_index(typeid(T))] = new T();
}

template<typename T>
inline void GameObjectEntity::RemoveComponent()
{
	try
	{
		--m_ComponentIndex;
		if (m_ComponentIndex < 0u)
		{
			m_ComponentIndex = 0u;
			throw;
		}
	}
	catch (...)
	{
		printf("No Component is on this Game Object");
		return;
	}

	m_Components.erase(std::type_index(typeid(T)));
}

template<typename T>
inline T* GameObjectEntity::GetComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? nullptr : static_cast<T*>(t_Index->second);
}

template<typename T>
inline bool GameObjectEntity::HasComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? false : true;
}

#endif

