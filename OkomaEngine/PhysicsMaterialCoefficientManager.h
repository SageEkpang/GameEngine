#ifndef PHYSICS_MATERIAL_COEFFICIENT_MANAGER_H
#define PHYSICS_MATERIAL_COEFFICIENT_MANAGER_H

#include <utility>
#include <map>

enum PhysicsMaterialTypes
{
	PHYSICS_MATERIAL_TYPE_ROCK,
	PHYSICS_MATERIAL_TYPE_GRASS,
	PHYSICS_MATERIAL_TYPE_METAL,
	PHYSICS_MATERIAL_TYPE_ICE,
	PHYSICS_MATERIAL_TYPE_WORM
};

class PhysicsMaterialCoefficientManager
{
private:

	typedef std::pair<PhysicsMaterialTypes, PhysicsMaterialTypes> MaterialTypePair;
	typedef std::map<MaterialTypePair, float> MaterialMapping;

	MaterialMapping m_PhysicsMaterialMapping;
	float m_Multiplier = 1.f;

public:

	// CLASS FUNCTION(s)
	PhysicsMaterialCoefficientManager();
	~PhysicsMaterialCoefficientManager();

	// BASE FUNCTION(s)
	float CheckMaterialPairs(PhysicsMaterialTypes materialA, PhysicsMaterialTypes materialB);
};

#endif

