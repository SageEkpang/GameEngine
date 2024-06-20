#include "Title.h"

// Start Up

Title::Title() 
{
    // GameUtility::Game::LoadContent();
    m_ScreenName = "Title";
    m_Camera.zoom = 1.0f;
    m_GameInfo.State = GameState::STATE_TITLE;

    GameUtility::Game::TransitionTime(5.0f);
    GameUtility::Game::LoadContent(m_GameObjects);
}

Title::~Title() 
{
    
}

void Title::Update(float DeltaTime) 
{
    m_GameObjects->Process(DeltaTime);

    if (IsKeyReleased(KEY_SPACE))
    {
        GameUtility::Game::TransitionScreen(ScreenState::SCREEN_NEXT, DeltaTime);
    }
}

void Title::Draw() 
{
    DrawRectangle(0, 0, 50, 50, RED);
    DrawText("Title", 300, 300, 50, RED);
    DrawText(TextFormat("%d", m_GameInfo.State), 600, 300, 50, BLUE);
}
