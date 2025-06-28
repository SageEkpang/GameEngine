#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

// GAME OBJECTS(s)
#include "PhysicsManager.h"
#include "GameObjectEntity.h"
#include <vector>

// CHANGE TODO_GLOBAL: This will be used for the registration system  for the ECS when it is fully implemented
//

class GameObjectManager
{
private:

    // PRIVATE VARIABLE(s)
    PhysicsManager m_PhysicsManager;
    std::vector<GameObjectEntity*> m_GameObjects;

    // PRIVATE FUNCTION(s)
    void ProcessGameObject(float deltaTime); // Update / Process Game Object
    void ShowcaseGameObject(); // Render / Showcase Game Object

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameObjectManager();

    /// @brief Default Destructor for Class
    ~GameObjectManager();

    /// @brief Helper Destructor for Class
    void Destroy();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Process(float deltaTime);

    /// @brief Default Draw function for Class
    void Showcase();

    // SETTER FUNCTION(s)
    void AddGameObject(GameObjectEntity* gameObject);
    void RemoveGameObject(GameObjectEntity* gameObject);

};

#endif
