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
class CapsuleColliderComponent;
class ComplexColliderComponent;
class LineColliderComponent;
class RectangleColliderComponent;
class SphereColliderComponent;

class ParticleEffectComponent;
class Rigidbody2DComponent;

class CameraComponent;
// ---------------------------------

class GameObjectEntity
{
private:

	// NOTE: BASE VARIABLE(s)
	OKTransform2<float> m_Transform;

	// COMPONENT VARIABLE(s)
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
	template<std::derived_from<ComponentEntity> T>
	void AddComponent();

	template<std::derived_from<ComponentEntity> T>
	void RemoveComponent();

	template<typename T>
	T* FindChildComponent();

	template<std::derived_from<ComponentEntity> T>
	T* GetComponent();

	template<std::derived_from<ComponentEntity> T>
	bool HasComponent();

};

/// <summary>
/// Add the component to the component map, if it is derived from the component entity
/// </summary>
/// <typeparam name="T"></typeparam>
template<std::derived_from<ComponentEntity> T>
inline void GameObjectEntity::AddComponent()
{
	try
	{
		++m_ComponentIndex;
		if (m_ComponentIndex > MAX_COMPONENTS)
		{
			m_ComponentIndex = MAX_COMPONENTS;
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

/// <summary>
/// Remove the component from the component list
/// </summary>
/// <typeparam name="T"></typeparam>
template<std::derived_from<ComponentEntity> T>
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

/// <summary>
/// Find the Component from Parent Component
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline T* GameObjectEntity::FindChildComponent()
{
	T* t_Result = nullptr;
	for (auto& [ComponentId, ComponentType] : m_Components)
	{
		t_Result = dynamic_cast<T*>(ComponentType);
		if (t_Result) { break; }
	}

	return t_Result;
}

/// <summary>
/// Get the Component currently in the Components map
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<std::derived_from<ComponentEntity> T>
inline T* GameObjectEntity::GetComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? nullptr : static_cast<T*>(t_Index->second);
}

/// <summary>
/// Check if the game object has said component
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<std::derived_from<ComponentEntity> T>
inline bool GameObjectEntity::HasComponent()
{
	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	return t_Index == m_Components.end() ? false : true;
}

#endif

