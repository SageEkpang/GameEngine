#include "GameManager.h"

GameManager::GameManager() 
: 
    m_CurrentGameState(GameState::STATE_NONE), 
    m_CurrentScreenState(ScreenState::SCREEN_CURRENT)
{

    // Set up screen for Display
    m_CurrentGameScreen = static_cast<GameScreen*>(m_ScreenVector[0]);
    m_CurrentGameScreen = m_ScreenVector[0];
    m_CurrentGameScreen->ResetScreenToCurrent();

    // Setting checking states
    m_CheckState = m_CurrentGameState;
    m_CheckScreenState = ScreenState::SCREEN_CURRENT;

    m_Delay = 1.0f * 60.0f;
    m_Timer = 0.0f;
}

GameManager::~GameManager() 
{
    // GAME SCREEN DELETE
    if (m_CurrentGameScreen != nullptr)
    { 
        m_CurrentGameScreen = nullptr;
        delete m_CurrentGameScreen;
    }

    // DELETE VECTOR ELEMENTS
    for (size_t i = 0; i < m_ScreenVector.size(); ++i)
    {
        m_ScreenVector[i] = nullptr;
        delete m_ScreenVector[i];
    }
}

void GameManager::Update(float DeltaTime) 
{
    // Game Screen Update Function Call
    // TODO: Pause can be implemented here however, need to check if it is the gameplay screen so they pause can not be used in any state
    // if (m_IsTransitioning == false) 

    if (IsKeyUp(KEY_P))
    {
        m_CurrentGameScreen->Update(DeltaTime); 
    }

    // Check GameState and ScreenState of Game
    m_CurrentGameState = m_CurrentGameScreen->GetGameInfo().State;
    // m_CurrentGameState = m_CurrentGameScreen->GetCopyGame().State;
    m_CurrentScreenState = m_CurrentGameScreen->GetGameInfo().ScState;

    // Switching Game Screen (Screen State)
    if (m_CurrentScreenState != m_CheckScreenState)
    {
        m_IsTransitioning = true;
        // Timer delay to switch screens
        m_Timer += 60.0f * DeltaTime;

        if (m_Timer >= m_Delay)
        {
            // Calculate Switch Index
            int Index = 0;
            Index = (int)m_CurrentGameState + (int)m_CurrentGameScreen->GetGameInfo().ScState;

            // Clear Current Screen and assign new Screen
            // m_CurrentGameScreen = nullptr;
            // delete m_CurrentGameScreen;
            m_CurrentGameScreen = m_ScreenVector[Index - 1];

            // Set current screen state to current
            m_CurrentScreenState = ScreenState::SCREEN_CURRENT;
            m_CurrentGameScreen->ResetScreenToCurrent();
            m_IsTransitioning = false;
            m_Timer = 0.0f;
        }
    }
    
    // Switching Game Screen (Game State)
    if (m_CurrentGameState != m_CheckState)
    {
        m_IsTransitioning = true;
        // Timer delay to switch screens
        m_Timer += 60.0f * DeltaTime;

        if (m_Timer >= m_Delay)
        {
            // Calculate Switch Index
            int Index = 0;
            Index = (int)m_CurrentGameScreen->GetGameInfo().State;

            // Clear Current Screen and assign new Screen
            m_CurrentGameScreen = nullptr;
            delete m_CurrentGameScreen;
            m_CurrentGameScreen = m_ScreenVector[Index - 1];

            // Set check to new screen created
            m_CheckState = m_CurrentGameState;
            m_CurrentGameScreen->ResetScreenToCurrent();
            m_IsTransitioning = false;
            m_Timer = 0.0f;
        }
    }
}

void GameManager::Draw() 
{
    // Game Screen Draw function call
    m_CurrentGameScreen->Draw();
}
