#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

#include "ComponentEntity.h"
#include <iostream>
#include <unordered_set>

class GameObjectEntity;

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

class ColliderEntity : public ComponentEntity
{
public: // PROTECTED VARIABLE(s)

    // BASE VARIABLE(s)
    bool m_HasCollided;
    bool m_IsActivated;
    bool m_IsTrigger;

    // TRIGGER AREA VARIABLE(s)
    bool m_HasEntered = false;
    bool m_HasStayed = false;
    bool m_HasExited = false;

    std::unordered_set<GameObjectEntity*> m_ObjectList;

    // COLLIDER VARIABLE(s)
    ColliderType m_ColliderType;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    ColliderEntity();

    // DESTRUCTOR
    ~ColliderEntity();


    // TRIGGER AREA FUNCTION(s)
    void TriggerEntered(GameObjectEntity* gameObject, void(*func)() = nullptr);
    void TriggerStayed(GameObjectEntity* gameObject, void(*func)() = nullptr);
    void TriggerExited(GameObjectEntity* gameObject, void(*func)() = nullptr);


    // GETTER FUNCTION(s)
    inline ColliderType GetColliderType() const { return m_ColliderType; }
    inline bool GetActivated() const { return m_IsActivated; }
    inline std::unordered_set<GameObjectEntity*>& GetObjects() { return m_ObjectList; }

    // SETTER FUNCTION(s)
    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }
    inline void SetActived(bool activated) { m_IsActivated = activated; }
    inline void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
};

#endif