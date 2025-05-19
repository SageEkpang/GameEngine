#include "GameObjectEntity.h"

GameObjectEntity::GameObjectEntity()
{
	m_Components.clear();
}

GameObjectEntity::~GameObjectEntity()
{
	std::unordered_set<ComponentEntity*>::iterator itr;

	for (itr = m_Components.begin(); itr != m_Components.end(); ++itr)
	{
		delete* itr;
		// itr = nullptr;
	}

	m_Components.clear();
}

void GameObjectEntity::Update(const float deltaTime)
{
	if (!m_Components.empty())
	{
		for (auto& c : m_Components)
		{
			c->Update(deltaTime);
		}
	}
}

void GameObjectEntity::Draw()
{
	if (!m_Components.empty())
	{
		for (auto& c : m_Components)
		{
			// c->Draw();
		}
	}
}

Archetype& GameObjectEntity::AddToArchetype(Archetype& source, ComponentId id)
{
	
}

void GameObjectEntity::AddComponent(EntityId entity, ComponentId component)
{
	Record& t_Record = m_EntityIndex[entity];
	Archetype& t_Archetype = t_Record.archetype;
	Archetype& t_NextArchetype = t_Archetype.addArchetypes[component];
	
	// move_entity(t_Archetype, t_Record.row, t_NextArchetype);
}

void* GameObjectEntity::GetComponent(EntityId entity, ComponentId component)
{
	Record& t_Record = m_EntityIndex[entity];
	Archetype& t_Archetype = t_Record.archetype;

	// NOTE: Check if it has the component
	ArchetypeMap t_Archetypes = m_ComponentIndex[component];
	if (t_Archetypes.count(t_Archetype.id) == 0) { return nullptr; }

	// NOTE: If one is in there, iterate through it
	ArchetypeRecord& t_ArchRecord = t_Archetypes[t_Archetype.id];
	return t_Archetype.components[t_ArchRecord.column][t_Record.row];

	return nullptr;
}

bool GameObjectEntity::HasComponent(EntityId entity, ComponentId component)
{
	






	return true;
}