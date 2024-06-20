#include "Structs.h"
#include "Constants.h"
#include "GameObjectManager.h"

class StartUp;
class GameScreen;

namespace GameUtility
{
    // Screens
    GameScreen* m_GameScreen;
    std::vector<GameScreen> m_Screens;


    // Objects
    GameObjectManager* m_GameObjectManager;


    // Transition States
    GameState m_CurrentGameState;
    ScreenState m_CurrentScreenState;

    float m_TransitionTime;
    float m_Timer;

    // TODO: Create script component using function pointer and call back functionality

    // GAME FUNCTION(s)
    namespace Game
    {
        void StartUpContent(StartUp* startContent);
        void LoadContent(GameObjectManager* gameObjectManager); // For the Construnction of Everything (In Main File)
        void Process(float deltaTime); // Update / Process Game Utility (In Main File)
        void Showcase(); // Render / Showcase Game Utility (In Main File)
        void Destroy(); // Destroy Game / Assets

        void TransitionTime(float time);
        void TransitionScreen(GameState state, float deltaTime);
        void TransitionScreen(ScreenState state, float deltaTime);
    }
};