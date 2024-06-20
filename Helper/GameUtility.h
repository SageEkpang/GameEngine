#include "Structs.h"
#include "Constants.h"
#include "GameObjectManager.h"

class StartUp;
class GameScreen;

namespace GameUtility
{
    // AUDIO VARIABLES
    std::vector<Sound> m_Sounds;

    // SCREEN VARIABLE(s)
    GameScreen* m_GameScreen;
    std::vector<GameScreen> m_Screens;
    GameState m_CurrentGameState;
    ScreenState m_CurrentScreenState;

    float m_TransitionTime;
    float m_Timer;


    // Objects
    GameObjectManager* m_GameObjectManager;



    // TODO: Create script component using function pointer and call back functionality

    // GAME FUNCTION(s)
    namespace Game
    {
        void StartUpContent(StartUp* startContent);
        void LoadContent(GameObjectManager* gameObjectManager); // For the Construnction of Everything (In Main File)
        void Process(float deltaTime); // Update / Process Game Utility (In Main File)
        void Showcase(); // Render / Showcase Game Utility (In Main File)
        void Destroy(); // Destroy Game / Assets

        void PlaySound(const char* sound, float volume = 0, bool looping = false);


        void TransitionTime(float time);
        void TransitionScreen(GameState state, float deltaTime);
        void TransitionScreen(ScreenState state, float deltaTime);
    }

};