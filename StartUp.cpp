#include "StartUp.h"

#include "Title.h"
#include "Menu.h"
#include "LevelSelect.h"
#include "Gameplay.h"
#include "End.h"

StartUp::StartUp() 
{
    m_Screens.push_back(Title("Title"));
    m_Screens.push_back(Menu("Menu"));
    m_Screens.push_back(LevelSelect("LevelSelect"));
    m_Screens.push_back(Gameplay("Gameplay"));
    m_Screens.push_back(End("End"));
}