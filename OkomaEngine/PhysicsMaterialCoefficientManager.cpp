#include "PhysicsMaterialCoefficientManager.h"

PhysicsMaterialCoefficientManager::PhysicsMaterialCoefficientManager()
{
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK)] = 0.6f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS)] = 0.35f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL)] = 0.5f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE)] = 0.02f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ROCK, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM)] = 0.8f * m_Multiplier;

	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS)] = 0.7f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL)] = 0.8f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE)] = 0.02f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_GRASS, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM)] = 0.6f * m_Multiplier;

	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL)] = 0.5f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE)] = 0.2f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_METAL, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM)] = 0.7f * m_Multiplier;

	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE)] = 0.02f * m_Multiplier;
	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_ICE, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM)] = 0.1f * m_Multiplier;

	m_PhysicsMaterialMapping[std::make_pair(PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM, PhysicsMaterialTypes::PHYSICS_MATERIAL_TYPE_WORM)] = 0.4f * m_Multiplier;
}

PhysicsMaterialCoefficientManager::~PhysicsMaterialCoefficientManager()
{
	m_PhysicsMaterialMapping.clear();
}

float PhysicsMaterialCoefficientManager::CheckMaterialPairs(PhysicsMaterialTypes materialA, PhysicsMaterialTypes materialB)
{
	auto PhysicsMaterialMadePair = std::make_pair(materialA, materialB);

	if (m_PhysicsMaterialMapping.count(PhysicsMaterialMadePair) == 0) { std::swap(PhysicsMaterialMadePair.first, PhysicsMaterialMadePair.second); }

	return m_PhysicsMaterialMapping[PhysicsMaterialMadePair];
}
