#ifndef STRUCTS_H
#define STRUCTS_H

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <array>

using namespace std;

// GAME STATE ENUMS
enum GameState{ // TODO:: Need a way to handle the screen exiting out of application
    STATE_NONE = 0,
    STATE_TITLE = 1,
    STATE_MENU  = 2,
    STATE_LEVEL_SELECT = 3,
    STATE_GAME = 4,
    STATE_END = 5
};

// GAME CURRENT SCREEN STATE ENUMS
enum ScreenState
{
    SCREEN_NEXT = 1,
    SCREEN_CURRENT = 0,
    SCREEN_PREVIOUS = -1
};

typedef struct Tile
{
    std::string tag;
    Vector2 position;
    Texture2D texture;

    Tile(std::string tag = " ", Vector2 position = Vector2(), Texture2D texture = Texture2D())
    {
        this->tag = tag;
        this->position = position;
        this->texture = texture;
    }

} Tile2D;

typedef struct Transform2D
{
    Vector2 position;
    Vector2 size;
    float rotation;

    Transform2D(Vector2 position = Vector2(), Vector2 size = Vector2(), float rotation = 0)
    {
        this->position = position;
        this->size = size;
        this->rotation = rotation;
    }

} Transform2D;

typedef struct GameInfo
{
    GameState State;
    ScreenState ScState;
    int LevelIndex;

    GameInfo() = default;

    GameInfo(GameState State, ScreenState ScState, int levelIndex)
    {
        this->State = State;
        this->ScState = ScState;
        this->LevelIndex = levelIndex;
    }

} GameInfo;

typedef struct ButtonInfo
{
    const char* ButtonText;
    std::string ButtonTextureName;

    Texture2D ButtonImage;
    Rectangle ButtonRect;
    Vector2 ButtonPadding;

    bool ButtonActive;
    float ButtonTextSize;
    GameInfo Info;

    ButtonInfo()
    {
        ButtonText = "";
        ButtonTextureName = "";
        ButtonImage = Texture2D();
        ButtonRect.x = 0;
        ButtonRect.y = 0;
        ButtonRect.width = 0;
        ButtonRect.height = 0;
        ButtonPadding.x = 0;
        ButtonPadding.y = 0;
        ButtonActive = false;
        ButtonTextSize = 0;
    }

} ButtonInfo;

#endif