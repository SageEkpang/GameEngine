#include "GameUtility.h"
#include "GameManager.h"

int main()
{
    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);

    StartUp* content = new StartUp();
    GameUtility::Game::StartUpContent(content);

    while(!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        GameUtility::Game::Process(deltaTime);
        GameUtility::Game::Showcase();
    }

    GameUtility::Game::Destroy();

    return 0;
}