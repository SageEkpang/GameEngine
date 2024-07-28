// #include "GameManager.h"
// #include "GameUtility.h"
// #include "StartUp.h"
#include "Structs.h"
#include "Constants.h"

int main()
{
    // Init Main Window and Audio Device
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
    InitAudioDevice();

    // Load in Start Up Content
    // StartUp* content = new StartUp();
    // GameManager* game = new GameManager(content);

    SetTargetFPS(DESIRED_FPS);

    // Run Game Processes and Showcases
    while(!WindowShouldClose())
    {
        // float deltaTime = GetFrameTime();

        // game->Process(deltaTime);
        // game->Showcase();
    }

    // Delete Game Data 
    // content = nullptr;
    // delete content;

    // game = nullptr;
    // delete game;

    // Close Audio and Window Contexts
    CloseAudioDevice();
    CloseWindow();
    
    return 0; // Return to Operator
}