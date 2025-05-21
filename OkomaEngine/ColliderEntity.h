#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

#include <iostream>

enum class ColliderType : std::int8_t
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
public: // PROTECTED VARIABLE(s)

    // BASE VARIABLE(s)
    bool m_HasCollided;
    bool m_IsActivated;
    bool m_IsTrigger;

    // COLLIDER VARIABLE(s)
    ColliderType m_ColliderType;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    ColliderEntity() 
        : m_HasCollided(false), m_IsActivated(true), m_IsTrigger(false), m_ColliderType(ColliderType::COLLIDER_TYPE_NONE) { }

    // DESTRUCTOR
    ~ColliderEntity() { };

    // GETTER FUNCTION(s)
    inline ColliderType GetColliderType() const { return m_ColliderType; }

    // SETTER FUNCTION(s)
    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }

};

#endif