#include "End.h"

End::End(std::string screenName) 
: GameScreen(screenName) 
{
    m_Camera.zoom = 1.0f;
}

End::~End() 
{
    
}

void End::Update(float DeltaTime) 
{
    // if (IsKeyReleased(KEY_SPACE))
    // {
    //     m_GameInfo.State = GameState::STATE_GAME;
    //     // m_GameInfo.ScState = ScreenState::SCREEN_PREVIOUS;
    // }
}

void End::Draw() 
{
    DrawRectangle(0, 0, 50, 50, GREEN);
    DrawText("End", 300, 300, 50, GREEN);
    // DrawText(TextFormat("%d", m_GameInfo.State), 600, 300, 50, BLUE);
}
