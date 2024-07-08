#include "Title.h"

// Start Up

Title::Title(std::string screenName) 
: GameScreen(screenName) 
{
    m_Camera.target = Vector2{0.0f, 0.0f};
    m_Camera.zoom = 1.0f;
}

Title::~Title() 
{
    
}

void Title::Update(float DeltaTime) 
{
    // m_GameObjects->Process(DeltaTime);

    // if (IsKeyReleased(KEY_SPACE))
    // {
    //     GameUtility::Game::TransitionScreen(ScreenState::SCREEN_NEXT, DeltaTime);
    // }
}

void Title::Draw() 
{
    // DrawRectangle(0, 0, 50, 50, RED);
    // DrawText("Title", 300, 300, 50, RED);
    // DrawText(TextFormat("%d", m_GameInfo.State), 600, 300, 50, BLUE);
}
