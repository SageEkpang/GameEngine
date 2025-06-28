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

// DERIVED COMPONENT CLASSE(s)
#include "RectangleColliderComponent.h"
#include "CircleColliderComponent.h"
#include "CapsuleColliderComponent.h"

#include "PointColliderComponent.h"
#include "LineColliderComponent.h"
#include "ComplexColliderComponent.h"

#include "ParticleEffectComponent.h"
#include "Rigidbody2DComponent.h"
#include "RenderComponent.h"

#include "InputComponent.h"
#include "CameraComponent.h"

#include <queue>
#include <list>

unsigned int constexpr MAX_COMPONENTS = 8u;

class GameObjectEntity
{
private:

	// COMPONENT VARIABLE(s)
	unsigned int m_ComponentIndex = 0u;
	std::bitset<MAX_COMPONENTS> m_ComponentBitMask;

	// COMPONENT ARRAY(s)
	std::unordered_map<std::type_index, ComponentEntity*> m_Components;

public:

	// NOTE: BASE VARIABLE(s)
	OKTransform2<float> m_Transform;

	// TODO: Find out how to make this work
	GameObjectEntity* m_Parent;
	std::list<GameObjectEntity*> m_Children;

public:

	// CLASS FUNCTION(s)
	GameObjectEntity();
	~GameObjectEntity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();


	// PARENT & CHILDREN FUNCTION(s)

		// PARENT FUNCTION(s)

		// NOTE: Set the Parent
		inline void Parent(GameObjectEntity* parent) { m_Parent = parent; }

		// NOTE: Get the Parent of the current game object, if not null
		inline GameObjectEntity* const GetParent() 
		{ 
			if (m_Parent == nullptr) { return nullptr; }
			return m_Parent; 
		}

		// NOTE: Get the Grand Parent of the current parent, if not null
		inline GameObjectEntity* const GetGrandParent()
		{
			if (m_Parent->m_Parent == nullptr) { return nullptr; }
			return m_Parent->m_Parent;
		}


		// CHILD FUNCTION(s)

		// NOTE: Set the Child
		inline void Child(GameObjectEntity* child) { m_Children.push_back(child); }

		// NOTE: By default it will get the first child on the parent
		GameObjectEntity* GetChild(int index = 0);

		// NOTE: Get the amount of childern are in the list
		inline int GetChildCount() const { return (int)m_Children.size(); }


	// HELPER FUNCTION(s)
	template<std::derived_from<ComponentEntity> T>
	T* AddComponent();

	template<std::derived_from<ComponentEntity> T>
	void RemoveComponent();

	template<typename T>
	T* FindChildComponent();

	template<typename T>
	std::type_index FindChildComponentID();

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
inline T* GameObjectEntity::AddComponent()
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
		return nullptr;
	}
	
	m_Components[std::type_index(typeid(T))] = new T();

	auto t_Index = m_Components.find(std::type_index(typeid(T)));
	t_Index->second->m_Owner = this;
	// t_Index->second->m_ID;

	return t_Index == m_Components.end() ? nullptr : static_cast<T*>(t_Index->second);
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
/// Find the Component from Parent Class
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
/// Find the ID from Parent Id
/// </summary>
/// <typeparam name="T"></typeparam>
/// <returns></returns>
template<typename T>
inline std::type_index GameObjectEntity::FindChildComponentID()
{
	T* t_Result = nullptr;
	for (auto& [ComponentId, ComponentType] : m_Components)
	{
		t_Result = dynamic_cast<T*>(ComponentType);
		if (t_Result) 
		{ 
			return ComponentId;
		}
	}

	return std::type_index(typeid(0));
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

