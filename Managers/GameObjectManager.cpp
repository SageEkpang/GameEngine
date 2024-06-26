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
    ProcessGameScreen(deltaTime);
    ProcessGameObject(deltaTime);
}

void GameObjectManager::Showcase() 
{
    ShowcaseGameScreen();
    ShowcaseGameObject();
}

void GameObjectManager::IncrementCameraIndex() 
{
    ++m_CameraIndex;
    if (m_CameraIndex > m_Cameras.size() - 1)
    {
        m_CameraIndex = 0;
    }
}

void GameObjectManager::DecrementCameraIndex() 
{
    --m_CameraIndex;
    if (m_CameraIndex < 0)
    {
        m_CameraIndex = m_Cameras.size() - 1;
    }
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

   
    // CAMERA COMPONENT DESTRUCTION
    if (!m_Cameras.empty())
    {
        std::vector<CameraComponent*>::iterator itr;
        for (itr = m_Cameras.begin(); itr != m_Cameras.end(); ++itr)
        {
            *itr = nullptr;
            delete *itr;
        }
        m_Cameras.clear();
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

void GameObjectManager::ProcessComponents(float deltaTime) 
{
    for (int i = 0; i < m_GameObjects.size(); ++i)
    {
        for (int j = 0; j < m_GameObjects[i]->GetComponents().size(); ++j)
        {
            m_GameObjects[i]->GetComponents()[j]->Update(deltaTime);
        }
    }
}

void GameObjectManager::ProcessGameScreen(float deltaTime) 
{
    
}

void GameObjectManager::ShowcaseGameObject() 
{
    
}

void GameObjectManager::ShowcaseGameScreen() 
{
    
}
