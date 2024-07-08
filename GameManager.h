#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "GameScreen.h"

class GameManager
{
private:

    // SCREEN VARIABLE(s)    
    GameScreen* m_CurrentGameScreen;

    GameState m_CurrentGameState;
    GameState m_CheckState;

    ScreenState m_CurrentScreenState;
    ScreenState m_CheckScreenState;

    // SCREEN TRANSITION VARIABLE(s)
    float m_Delay;
    float m_Timer;
    bool m_IsTransitioning;

    // SCREEN ARRAY VARIABLE(s)
    std::vector<GameScreen*> m_ScreenVector;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameManager();

    /// @brief Default Destructor for Class
    ~GameManager();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float DeltaTime);

    /// @brief Default Draw function for Class
    void Draw();


    // GETTER FUNCTION(s)
    Camera2D GetCamera2D() { return m_CurrentGameScreen->GetCamera2D(); }

};

#endif