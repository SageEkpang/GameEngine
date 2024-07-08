#include "StartUp.h"

#include "GameScreens/Title.h"
#include "GameScreens/Menu.h"
#include "GameScreens/LevelSelect.h"
#include "GameScreens/Gameplay.h"
#include "GameScreens/End.h"

StartUp::StartUp() 
{
    m_Screens.push_back(Title());
    m_Screens.push_back(Menu());
    m_Screens.push_back(LevelSelect());
    m_Screens.push_back(Gameplay());
    m_Screens.push_back(End());
}