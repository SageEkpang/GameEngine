
/*
    #include "GameScreenComponent.h"
*/

#include "GameObjectManager.h"

// ANIMATION CLASS

// TEXTURE VARIABLE(s)
// Texture2D m_CharacterSpriteSheet;
// Texture2D m_SingleSprite;
// int m_SpriteSheetHeight;
// int m_SpriteSheetWidth;

// SPRITE SHEET ANIMATION ORDER
// Idle - 4 Frames
// Running - 4 Frames
// Jumping - 1 Frames (Mario 64 Like Jump)
// Death - 4 Frames

namespace GameUtility
{
    GameObjectManager* m_GameObjectManager;
    // GameScreen
    // TODO: Add a game screen for here
    // TODO: Create script component using function pointer and call back functionality

    // GAME FUNCTION(s)
    namespace Game
    {
        void LoadContent(); // For the Construnction of Everything (In Main File)
        void Process(float deltaTime); // Update / Process Game Utility (In Main File)
        void Showcase(); // Render / Showcase Game Utility (In Main File)
        void Destroy(); // Destroy Game / Assets

        void AddGameObjectManager(GameObjectManager* gameObjectManager); // Game Manager
    }

    // UI FUNCTION(s)
    namespace UI
    {
        void AddGameScreen();

        void TransitionGameScreen(); // Takes in Game Screen to transition to (Most likely a Enum variable)
    }
};