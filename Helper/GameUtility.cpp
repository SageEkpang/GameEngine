#include "GameUtility.h"

namespace GameUtility
{
    namespace Game
    {
        void LoadContent() 
        {
            
        }

        void Process(float deltaTime) 
        {
            m_GameObjectManager->Process(deltaTime);
        }
        
        void Showcase() 
        {
            Color g_Background = Color{137, 207, 240, 255}; // Light Blue

            BeginDrawing();

            ClearBackground(g_Background);

                BeginMode2D(m_GameObjectManager->GetCurrentCamera());

                m_GameObjectManager->Showcase();

                EndMode2D();

            EndDrawing();
        }

        void Destroy() 
        {
            m_GameObjectManager->Destroy();
            m_GameObjectManager = nullptr;
            delete m_GameObjectManager;
        }
        
        void AddGameObjectManager(GameObjectManager* gameObjectManager) 
        {
            m_GameObjectManager = gameObjectManager;
        }
    }
    
    namespace UI
    {
        
        void AddGameScreen() 
        {
            
        }
        
        void TransitionGameScreen() 
        {
            
        }

    }
}