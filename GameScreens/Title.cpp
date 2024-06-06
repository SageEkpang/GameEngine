#include "Title.h"

Title::Title() 
{
    m_ScreenName = "Title";
    m_Camera.zoom = 1.0f;
    m_GameInfo.State = GameState::STATE_TITLE;
}

Title::~Title() 
{
    
}

void Title::Update(float DeltaTime) 
{
    if (IsKeyReleased(KEY_SPACE))
    {
        m_GameInfo.LevelIndex = 1;

        

        m_GameCopy.LevelIndex = m_GameInfo.LevelIndex;
        m_GameInfo.State = GameState::STATE_MENU;
    }
}

void Title::Draw() 
{
    DrawRectangle(0, 0, 50, 50, RED);
    DrawText("Title", 300, 300, 50, RED);
    DrawText(TextFormat("%d", m_GameInfo.State), 600, 300, 50, BLUE);
}
