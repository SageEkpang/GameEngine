#include "GameManager.h"
#include "StartUp.h"

float GameManager::m_Timer = 0.0f;

GameManager::GameManager(StartUp* startContent) 
{
    m_CurrentGameState = GameState::STATE_NONE;
    m_CurrentScreenState = ScreenState::SCREEN_CURRENT;

    m_TransitionTime = 1.0f * 60.0f;
    m_Timer = 0.0f;

    for (size_t i = 0; i < startContent->GetScreenVector().size(); ++i)
    {
        m_Screens.push_back(startContent->GetScreenVector()[i]);
    }

    m_GameScreen = &m_Screens[0];
}

void GameManager::LoadContent(GameObjectManager* gameObjectManager) 
{
    m_GameObjectManager = gameObjectManager;
}

GameManager::~GameManager() 
{
    Destroy();
}

void GameManager::Process(float deltaTime) 
{
    m_GameScreen->Update(deltaTime);
    m_GameObjectManager->Process(deltaTime);
}

void GameManager::Showcase() 
{
    Color g_Background = Color{137, 207, 240, 255}; // Light Blue

    BeginDrawing();

    ClearBackground(g_Background);

        BeginMode2D(m_GameScreen->GetCamera2D()); // FIXME: Works for now however, it means that the camera component will not work later on, so change this to the camera component within the gameobject manager

            m_GameScreen->Draw();
            m_GameObjectManager->Showcase();

        EndMode2D();

    EndDrawing();
}

void GameManager::PlaySound(const char* sound, float volume, bool looping) 
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

void GameManager::TransitionScreen(GameState state, float deltaTime) 
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

void GameManager::TransitionScreen(ScreenState state, float deltaTime) 
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


void GameManager::Destroy() 
{
    m_GameObjectManager->Destroy();
    m_GameObjectManager = nullptr;

    m_GameScreen = nullptr;
}
