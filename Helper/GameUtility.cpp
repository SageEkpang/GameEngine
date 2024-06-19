#include "GameUtility.h"
#include "GameScreen.h"
#include "GameObjectManager.h"

namespace GameUtility
{
    namespace Game
    {
        void StartUpContent() 
        {
            m_GameScreen;
        }
    
        void LoadContent(GameScreen* gameScreen, GameObjectManager* gameObjectManager) 
        {
            m_GameScreen = gameScreen;
            m_GameObjectManager = gameObjectManager;
        }
    
        void Process(float deltaTime) 
        {
            m_GameScreen->Update(deltaTime);
            m_GameObjectManager->Process(deltaTime);
        }
        
        void Showcase() 
        {
            Color g_Background = Color{137, 207, 240, 255}; // Light Blue

            BeginDrawing();

            ClearBackground(g_Background);

                BeginMode2D(m_GameScreen->GetCamera2D());

                    m_GameScreen->Draw();
                    m_GameObjectManager->Showcase();

                EndMode2D();

            EndDrawing();
        }

        void Destroy() 
        {
            m_GameObjectManager->Destroy();
            m_GameObjectManager = nullptr;
            // delete m_GameObjectManager;

            m_GameScreen = nullptr;
            // delete m_GameScreen;
        }
    }
}