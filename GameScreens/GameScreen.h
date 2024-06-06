#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

// CUSTOM INCLUDE(s)
#include "Structs.h"
#include "Constants.h"

// NEEDED INCLUDE(s)
#include "Component.h"

class GameScreen : public Component
{
protected:

    // CAMERA VARIABLE(s)
    Camera2D m_Camera;

    // SCREEN VARIABLE(s)
    std::string m_ScreenName;

    // GAME INFO VARIABLE(s)
    static GameInfo m_GameCopy;
    GameInfo m_GameInfo;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameScreen() {};

    /// @brief Default Destructor for Class
    virtual ~GameScreen() {};


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float DeltaTime) = 0;

    /// @brief Default Draw function for Class
    virtual void Draw() = 0;


    // GETTER FUNCTION(s)

    /// @brief Getter function for Game Info 
    inline GameInfo GetGameInfo() { return this->m_GameInfo; }

    /// @brief Getter function for Game Copy 
    static GameInfo GetCopyGame() { return m_GameCopy; }

    /// @brief Getter function for Camera 2D Info
    inline Camera2D GetCamera2D() { return this->m_Camera; }

    /// @brief Getter function for Tag Info 
    inline std::string GetName() { return this->m_ScreenName; }


    // SETTER FUNCTION()

    /// @brief Setter function for Setteing Specific Game Info
    void SetGameInfo(GameInfo NewGameInfo) { this->m_GameInfo = NewGameInfo; }

    /// @brief Setter function for Setting the Screen Info to Current
    void ResetScreenToCurrent() { this->m_GameInfo.ScState = ScreenState::SCREEN_CURRENT; }

};

#endif