#ifndef START_UP_H
#define START_UP_H

#include "Helper/Structs.h"
#include "Helper/Constants.h"

#include "GameScreens/GameScreen.h"

// class GameScreen;
class Title;
class Menu;
class LevelSelect;
class Gameplay;
class End;

class StartUp
{
private:

    // Private Variables

    std::vector<GameScreen> m_Screens;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    StartUp();

    /// @brief Default Destructor for Class
    ~StartUp() { }


    // BASE FUNCTION(s)

    /// @brief Getter function for Screen Array
    std::vector<GameScreen> GetScreenVector() { return m_Screens; }

};


#endif