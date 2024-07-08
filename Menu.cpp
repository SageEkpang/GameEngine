#include "Menu.h"

Menu::Menu(std::string screenName) 
: GameScreen(screenName)
{
    m_Camera.zoom = 1.0f;
}

Menu::~Menu() 
{
}

void Menu::Update(float DeltaTime) 
{
    // if (IsKeyReleased(KEY_SPACE))
    // {
    //     // m_GameInfo.State = GameState::STATE_LEVEL_SELECT;
    //     // m_GameInfo.ScState = ScreenState::SCREEN_NEXT;
    // }
}

void Menu::Draw() 
{
    DrawRectangle(0, 0, 50, 50, BLUE);
    DrawText("Menu", 300, 300, 50, BLUE);
    // DrawText(TextFormat("%d", m_GameInfo.State), 600, 300, 50, BLUE);
}
