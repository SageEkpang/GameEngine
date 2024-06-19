#include "Structs.h"
#include "Constants.h"
#include "GameObjectManager.h"
#include "StartUp.h"

class GameScreen;

namespace GameUtility
{
    GameObjectManager* m_GameObjectManager;
    GameScreen* m_GameScreen;

    // TODO: Create script component using function pointer and call back functionality

    // GAME FUNCTION(s)
    namespace Game
    {
        void StartUpContent(StartUp startContent);
        void LoadContent(GameScreen* gameScreen, GameObjectManager* gameObjectManager); // For the Construnction of Everything (In Main File)
        void Process(float deltaTime); // Update / Process Game Utility (In Main File)
        void Showcase(); // Render / Showcase Game Utility (In Main File)
        void Destroy(); // Destroy Game / Assets
    }
};