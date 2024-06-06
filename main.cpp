#include "Constants.h"
#include "GameManager.h"
#include "Structs.h"

#include "GameUtility.h"

void Update(float DeltaTime, GameManager* game);
void Draw(Camera2D camera, GameManager* game);

int main()
{
    SetTargetFPS(60);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);

    GameUtility::Game::LoadContent();

    GameManager* Game = new GameManager();

    while(!WindowShouldClose())
    {
        float DeltaTime = GetFrameTime();

        GameUtility::Game::Process(DeltaTime);
        GameUtility::Game::Showcase();

        Update(DeltaTime, Game);
        Draw(Game->GetCamera2D(), Game);
    }

    GameUtility::Game::Destroy();

    return 0;
}