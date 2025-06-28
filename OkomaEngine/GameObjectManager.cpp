#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
    // TODO: Find Camera index and set the index
    m_PhysicsManager.SetDrawColliders(true);


}

GameObjectManager::~GameObjectManager()
{
    Destroy();
}

void GameObjectManager::Process(float deltaTime)
{
    ProcessGameObject(deltaTime);
}

void GameObjectManager::Showcase()
{
    ShowcaseGameObject();
}

void GameObjectManager::AddGameObject(GameObjectEntity* gameObject)
{
    // NOTE: Checks if the game object has a physics component on it, so it can simulate physics
    if (gameObject->HasComponent<Rigidbody2DComponent>()) { m_PhysicsManager.AddPhysicsObject(gameObject); return; }





}

void GameObjectManager::RemoveGameObject(GameObjectEntity* gameObject)
{
    // NOTE: If the game object is null, then do not even go into this loop
    // if (gameObject == nullptr) { return; }

}

void GameObjectManager::Destroy()
{
    
}

// PRIVATE FUNCTION(s)
void GameObjectManager::ProcessGameObject(float deltaTime)
{
    m_PhysicsManager.Update(deltaTime);
}

void GameObjectManager::ShowcaseGameObject()
{
    m_PhysicsManager.Draw();
}

