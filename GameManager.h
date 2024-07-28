#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Structs.h"
#include "Constants.h"
#include "GameObjectManager.h"
#include "GameScreen.h"

class StartUp;

class GameManager
{
private:

    // AUDIO VARIABLE(s)
    std::vector<Sound> m_Sounds;

    // SCREEN VARIABLE(s)
    GameScreen* m_GameScreen;
    std::vector<GameScreen> m_Screens;

    GameState m_CurrentGameState;
    ScreenState m_CurrentScreenState;

    float m_TransitionTime;
    static float m_Timer;

    // Objects
    GameObjectManager* m_GameObjectManager;

    /// @brief Default Destroy function for Class
    void Destroy();

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameManager(StartUp* startContent);

    /// @brief Default Load Content for Class
    void LoadContent(GameObjectManager* gameObjectManager);

    /// @brief Default Destructor for Class
    ~GameManager();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Process(float deltaTime);

    /// @brief Default Draw function for Class
    void Showcase();


    // EXTRA FUNCTION(s)

    // SOUND

    /// @brief Extra function to play sound
    void PlaySound(const char* sound, float volume = 0, bool looping = false);


    // SCREEN TRANSITION

    void TransitionTime(float time) { m_TransitionTime = time; }
    void TransitionScreen(GameState state, float deltaTime);
    void TransitionScreen(ScreenState state, float deltaTime);

};

#endif