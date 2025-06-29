#ifndef COLLIDER_ENTITY_H
#define COLLIDER_ENTITY_H

#include "ComponentEntity.h"
#include <iostream>
#include <unordered_set>
#include <functional>

class GameObjectEntity;

// NOTE: Depericate way but may need to revisite
//enum class collidertype : std::int8_t
//{
//    collider_type_none,
//    collider_type_point,
//    collider_type_rectangle,
//    collider_type_circle,
//    collider_type_capsule,
//    collider_type_oriented_rectangle,
//    collider_type_complex,
//    collider_type_line,
//};

enum class TriggerAreaState : std::int8_t
{
    TRIGGER_AREA_STATE_ENTERED,
    TRIGGER_AREA_STATE_STAYED,
    TRIGGER_AREA_STATE_EXITED,
    TRIGGER_AREA_STATE_NONE
};

class ColliderEntity : public ComponentEntity
{
private: // PRIVATE VARIABLE(s)

    std::function<void()> m_TriggerEnteredLambda = nullptr;
    std::function<void()> m_TriggerStayedLambda = nullptr;
    std::function<void()> m_TriggerExitedLambda = nullptr;

    std::unordered_set<GameObjectEntity*> m_ObjectList;

public: // PUBLIC VARIABLE(s)

    // BASE VARIABLE(s)
    bool m_HasCollided = false;
    bool m_IsTrigger;

    bool m_IsActivated;
    bool m_Quered = false;

    // TRIGGER AREA VARIABLE(s)
    TriggerAreaState m_TriggerState;

    // COLLIDER VARIABLE(s)
    // ColliderType m_ColliderType;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    ColliderEntity();
    virtual ~ColliderEntity();

    // HELPER FUNCTION(s)
    void TriggerQuery(GameObjectEntity* gameObject);
    void TriggerEnteredExecute(std::function<void()> func = nullptr);
    void TriggerStayedExecute(std::function<void()> func = nullptr);
    void TriggerExitedExecute(std::function<void()> func = nullptr);
    void TriggerQueryExecute();

    // GETTER FUNCTION(s)
    inline std::unordered_set<GameObjectEntity*> GetObjects() { return m_ObjectList; }
    inline int GetObjectCount() { return (int)m_ObjectList.size(); }

    // SETTER FUNCTION(s)

};

#endif