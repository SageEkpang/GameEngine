#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include "CollisionManifold.h"
#include "OKTransform2.h"

// PARENT INCLUDE(s)
#include "ComponentEntity.h"

// TODO: Prefix-fix with name of enum
enum ColliderType
{
    COLLIDER_POINT,
    COLLIDER_RECTANGLE,
    COLLIDER_CIRCLE,
    COLLIDER_CAPSULE,
    COLLIDER_ORIENTED_RECTANGLE,
    COLLIDER_COMPLEX,
    COLLIDER_LINE,
};

class ColliderEntity : public ComponentEntity
{
protected: // PROTECTED VARIABLE(s)

    // BASE VARIABLE(s)
    bool m_HasCollided;
    bool m_IsActivated;

    // COLLIDER VARIABLE(s)
    ColliderType m_ColliderType;

    // TODO: Complex collision class needed
    std::vector<OKVector2<float>> m_Vertices;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    ColliderEntity();

    // DESTRUCTOR
    ~ColliderEntity();

    // BASE FUNCTION(s)
    void Update(const float deltaTime) { };
    void Draw();

    // NOTE: Check if it is an absolute enter or a partial enter


    // GETTER FUNCTION(s)
    inline ColliderType GetColliderType() const { return m_ColliderType; }


    // SETTER FUNCTION(s)
    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }

    // POLYGONE FUNCTION(s)
    float PolygonArea();
};

// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

#endif