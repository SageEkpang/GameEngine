#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() 
{
    // TODO: Find Camera index and set the index


}

GameObjectManager::~GameObjectManager() 
{
}

void GameObjectManager::Process(float deltaTime) 
{
    ProcessGameObject(deltaTime);
}

void GameObjectManager::Showcase() 
{
    ShowcaseGameObject();
}

void GameObjectManager::AddGameObject(GameObject gameObject) 
{
    m_GameObjects.push_back(&gameObject);
}

void GameObjectManager::Destroy() 
{
    // GAME OBJECT DESTRUCTION
    if (!m_GameObjects.empty())
    {
        std::vector<GameObject*>::iterator itr;
        for (itr = m_GameObjects.begin(); itr != m_GameObjects.end(); ++itr)
        {
            *itr = nullptr;
            delete *itr;
        }
        m_GameObjects.clear();
    }
}


// PRIVATE FUNCTION(s)
void GameObjectManager::ProcessGameObject(float deltaTime) 
{
    for (int i = 0; i < m_GameObjects.size(); ++i) 
    {
        m_GameObjects[i]->Update(deltaTime);
    }
}

void GameObjectManager::ShowcaseGameObject() 
{
    for (int i = 0; i < m_GameObjects.size(); ++i)
    {
        m_GameObjects[i]->Draw();
    }
}

