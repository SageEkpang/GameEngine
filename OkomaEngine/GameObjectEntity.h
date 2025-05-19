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

#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <vector>
#include <memory>
#include <bitset>




// DERIVED COMPONENT CLASSE(s)
//class RectangleColliderComponent;
//class SphereColliderComponent;
//class CapsuleColliderComponent;
//class LineColliderComponent;
//
//class ParticleEffectComponent;
//class Rigidbody2DComponent;
//
//class CameraComponent;

unsigned int constexpr MAX_COMPONENTS = 8u;
std::bitset<MAX_COMPONENTS> EntityBitMask;

using ComponentId = unsigned int;
using Type = std::vector<ComponentId>;
using ArchetypeId = unsigned int;
using EntityId = unsigned int;

// CHECK THIS: May need to change this to a void*
template<typename T = ComponentEntity*>
using Column = std::vector<T>;

struct ArchetypeEdge
{
	Archetype& add;
	Archetype& remove;
};

struct Archetype
{
	Type type;
	ArchetypeId id;
	std::vector<Column<>> components;
	std::unordered_map<ComponentId, Archetype&> addArchetypes;
	std::unordered_map<ComponentId, Archetype&> removeArchetypes;
	std::unordered_map<ComponentId, ArchetypeEdge&> edges;
};

struct ArchetypeRecord
{
	size_t column;
};

struct Record
{
	Archetype& archetype;
	size_t row;
};

// TODO: Bit masking, Entity Mask

class GameObjectEntity
{
private:

	unsigned int m_ComponentIndexer = 0u;

	using ArchetypeMap = std::unordered_map < ArchetypeId, ArchetypeRecord>;
	std::unordered_map<ComponentId, ArchetypeMap> m_ComponentIndex;

	typedef std::unordered_set<ArchetypeId> ArchetypeSet;

	std::unordered_set<ComponentEntity*> m_Components;
	std::unordered_map<EntityId, Record> m_EntityIndex;
	std::unordered_map<Type, Archetype> m_ArchetypeIndex;

	std::shared_ptr<ComponentEntity*> m_SharedComponents;
	std::unique_ptr<ComponentEntity*[MAX_COMPONENTS]> m_UniqueComponents;
	

public:

	// CLASS FUNCTION(s)
	GameObjectEntity();
	~GameObjectEntity();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)
	Archetype& AddToArchetype(Archetype& source, ComponentId id);

	void AddComponent(EntityId entity, ComponentId component);

	void RemoveComponent() { };

	void* GetComponent(EntityId entity, ComponentId component);

	bool HasComponent(EntityId entity, ComponentId component);

	// TODO: Linked List this shit
	template<typename T>
	void AddComponentAlt(ComponentEntity* component)
	{
		m_UniqueComponents[m_ComponentIndexer] = std::make_unique<ComponentEntity*>(component);
	}

	template<typename T>
	T* GetComponentAlt()
	{
		return (T*)m_UniqueComponents.get();
	}


};

#endif