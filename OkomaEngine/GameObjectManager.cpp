#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
    // TODO: Find Camera index and set the index
    m_PhysicsManager.SetDrawColliders(true);
    m_PhysicsManager.SetDrawDebugVelocity(false);


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
    // TODO: Instead of the game object, should take in the components from the game objects
    // NOTE: Checks if the game object has a physics component on it, so it can simulate physics
    if (gameObject->HasComponent<Rigidbody2DComponent>()) { m_PhysicsManager.AddPhysicsObject(gameObject); }
    if (gameObject->HasComponent<RenderComponent>()) { m_RenderManager.AddRenderObject(gameObject); }

    if (gameObject->HasComponent<CameraComponent>()) { m_CurrentCamera; }



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
    m_RenderManager.Update(deltaTime);
    m_PhysicsManager.Update(deltaTime);
}

void GameObjectManager::ShowcaseGameObject()
{
    m_RenderManager.Draw();
    m_PhysicsManager.Draw();
}

