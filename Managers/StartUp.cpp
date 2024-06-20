#include "StartUp.h"

#include "Title.h"
#include "Menu.h"
#include "LevelSelect.h"
#include "Gameplay.h"
#include "End.h"

StartUp::StartUp() 
{
    m_Screens.push_back(Title());
    m_Screens.push_back(Menu());
    m_Screens.push_back(LevelSelect());
    m_Screens.push_back(Gameplay());
    m_Screens.push_back(End());
}