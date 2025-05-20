#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include "CollisionManifold.h"
#include "OKTransform2.h"
#include <vector>

// PARENT INCLUDE(s)
#include "ComponentEntity.h"

enum ColliderType
{
    COLLIDER_TYPE_NONE,
    COLLIDER_TYPE_POINT,
    COLLIDER_TYPE_RECTANGLE,
    COLLIDER_TYPE_CIRCLE,
    COLLIDER_TYPE_CAPSULE,
    COLLIDER_TYPE_ORIENTED_RECTANGLE,
    COLLIDER_TYPE_COMPLEX,
    COLLIDER_TYPE_LINE,
};

class ColliderEntity
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
    virtual void Update(const float deltaTime) = 0;
    virtual void Draw() = 0;

    // GETTER FUNCTION(s)
    inline ColliderType GetColliderType() const { return m_ColliderType; }

    // SETTER FUNCTION(s)
    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }

    // POLYGONE FUNCTION(s)
    float PolygonArea();
};

// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

#endif