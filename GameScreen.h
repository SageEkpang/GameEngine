#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

// CUSTOM INCLUDE(s)
#include "Structs.h"
#include "Constants.h"

#include "GameUtility.h"

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

class GameScreen
{
protected:

    // DEFAULT SCREEN VARIABLE(s)
    std::string m_ScreenName;
    GameObjectManager* m_GameObjects;

    // CAMERA VARIABLE(s)
    Camera2D m_Camera;

    // GAME INFO VARIABLE(s)
    static GameInfo m_GameCopy;
    GameInfo m_GameInfo;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameScreen(std::string screenName) { m_ScreenName = screenName; }

    /// @brief Default Destructor for Class
    virtual ~GameScreen() {}


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float DeltaTime) { }

    /// @brief Default Draw function for Class
    virtual void Draw() { }


    // GETTER FUNCTION(s)

    /// @brief Getter function for Game Info 
    inline GameInfo GetGameInfo() { return this->m_GameInfo; }

    /// @brief Getter function for Game Copy 
    static GameInfo GetCopyGame() { return m_GameCopy; }

    /// @brief Getter function for Camera 2D Info
    inline Camera2D GetCamera2D() { return this->m_Camera; }

    /// @brief Getter function for Screen Name
    inline std::string GetName() { return this->m_ScreenName; }
};

#endif