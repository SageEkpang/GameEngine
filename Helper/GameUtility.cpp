#include "GameUtility.h"
#include "GameScreen.h"
#include "StartUp.h"

namespace GameUtility
{
    namespace Game
    {
        void StartUpContent(StartUp* startContent) 
        {

            // Screen Transitioning Variables
            m_CurrentGameState = GameState::STATE_NONE;
            m_CurrentScreenState = ScreenState::SCREEN_CURRENT;

            m_TransitionTime = 1.0f * 60.0f;
            m_Timer = 0.0f;

            // Set Up Game Screens
            for (size_t i = 0; i < startContent->GetScreenVector().size(); ++i)
            {
                m_Screens.push_back(startContent->GetScreenVector()[i]);
            }

            m_GameScreen = &m_Screens[0];
        }
    
        void LoadContent(GameObjectManager* gameObjectManager) 
        {
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

        void TransitionTime(float time) 
        {
            m_TransitionTime = time;
        }
        
        void PlaySound(const char* sound, float volume, bool looping) 
        {
            // Sound Loading Functionality
            static bool HasLoaded;
            Sound tempSound;
            bool tempLoop = looping;

            if (HasLoaded == false) { tempSound = LoadSound(sound); HasLoaded = true; }

            float tempVol = volume;
            SetSoundVolume(tempSound, tempVol);

            // Play Sound Functionality
            static bool HasSoundPlayed;
            if (tempLoop == false)
            {
                // Play Sound (Once)
                if (!IsSoundPlaying(tempSound) && HasSoundPlayed == false)
                {
                    PlaySoundMulti(tempSound);
                    HasSoundPlayed = true;
                }
            }
            else if (tempLoop == true)
            {
                // Play Sound (Looping)
                if (!IsSoundPlaying(tempSound))
                {
                    PlaySoundMulti(tempSound);
                }
            }
        }
        
        void TransitionScreen(GameState state, float deltaTime) 
        {
            m_Timer += 60.0f * deltaTime;

            if (m_Timer >= m_TransitionTime)
            {
                int Index = 0;
                Index = (int)state;

                m_GameScreen = nullptr;
                m_GameScreen = &m_Screens[Index - 1];
                m_Timer = 0.0f;
            }
        }

        void TransitionScreen(ScreenState state, float deltaTime) 
        {
            m_Timer += 60.0f * deltaTime;

            if (m_Timer >= m_TransitionTime)
            {
                int Index = 0;
                Index = (int)m_CurrentGameState + (int)state;

                m_GameScreen = nullptr;
                m_GameScreen = &m_Screens[Index - 1];
                m_CurrentScreenState = ScreenState::SCREEN_CURRENT;
                m_Timer = 0.0f;
            }
        }
    }
}