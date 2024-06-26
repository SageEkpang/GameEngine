// #include "Helper/GameUtility.h"
#include "Managers/StartUp.h"

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
    InitAudioDevice();

    StartUp* content = new StartUp();
    // GameUtility::Game::StartUpContent(content);

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        // float deltaTime = GetFrameTime();

        // GameUtility::Game::Process(deltaTime);
        // GameUtility::Game::Showcase();
    }

    // GameUtility::Game::Destroy();
    content = nullptr;
    delete content;

    CloseAudioDevice();
    CloseWindow();
    
    return 0; // Return to Operator
}