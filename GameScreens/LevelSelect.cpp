#include "LevelSelect.h"

LevelSelect::LevelSelect() 
{
    m_ScreenName = "Level Select";
    m_Camera.zoom = 1.0f;
    m_GameInfo.State = GameState::STATE_LEVEL_SELECT;
    m_IsLoaded = false;
}

LevelSelect::~LevelSelect() 
{
    // DELETE BUTTONS FROM ARRAY
    // int TempSize = m_LevelSelectButtons.size();
    // for (int i = 0; i < TempSize; ++i)
    // {
    //     m_LevelSelectButtons[i] = nullptr;
    //     delete m_LevelSelectButtons[i];
    // }
}

void LevelSelect::Update(float DeltaTime) 
{
    // LoadContent();

    // // SELECT LEVEL FUNCTION
    // for (size_t i = 0; i < m_LevelSelectButtons.size(); ++i)
    // {
    //     m_LevelSelectButtons[i]->Update(DeltaTime);

    //     if (m_LevelSelectButtons[i]->GetButtonPressed() == true)
    //     {
    //         // m_GameInfo.LevelIndex = m_LevelSelectButtons[i]->GetButtonInfo().Info.LevelIndex;
    //         m_GameCopy.LevelIndex = m_GameInfo.LevelIndex;
    //         m_GameInfo.State = GameState::STATE_GAME;
    //     }
    // }

}

void LevelSelect::Draw() 
{
    // TODO: Create background for buttons
    // if (m_IsLoaded == true)
    // {
    //     for (size_t i = 0; i < m_LevelSelectButtons.size(); ++i)
    //     {
    //         m_LevelSelectButtons[i]->Draw();
    //     }
    // }
}

void LevelSelect::LoadContent() 
{
    // if (m_IsLoaded == false)
    // {
    //     int ChangeY = 0;
    //     int Cycles = 0;
    //     int ButtonSpacingX = 300;
    //     int ButtonSpacingY = 300;
    //     int LevelIndexIncrement = 0;

    //     do
    //     {
    //         for (int i = 0; i < 3; ++i)
    //         {
    //             // FILL BUTTON INFO
    //             ButtonInfo* TempInfo = new ButtonInfo();

    //             ++LevelIndexIncrement;

    //             TempInfo->Info.LevelIndex = LevelIndexIncrement; // IMPORTANT (DO NOT REMOVE)

    //             // BUTTON ACTIVE
    //             TempInfo->ButtonActive = true;

    //             // BUTTON TEXT
    //             TempInfo->ButtonTextSize = 40;
    //             TempInfo->ButtonPadding.x = 70;
    //             TempInfo->ButtonPadding.y = 65;
                
    //             std::string s = std::to_string(LevelIndexIncrement);
    //             const char* c = s.c_str();
    //             TempInfo->ButtonText = c;

    //             // BUTTON POSITION
    //             TempInfo->ButtonRect.x = 350 + (i * ButtonSpacingX);
    //             TempInfo->ButtonRect.y = 40 + ChangeY;

    //             // BUTTON SIZE (TEXTURE)
    //             TempInfo->ButtonRect.width = 160;
    //             TempInfo->ButtonRect.height = 160;

    //             // BUTTON TEXTURE/IMAGE
    //             TempInfo->ButtonTextureName = "Images/Button/LevelSelectButton.png";

    //             // MAKE BUTTON AND PUSH INFO
    //             // Button* TempButton = new Button(*TempInfo);
    //             // m_LevelSelectButtons.push_back(TempButton);

    //             TempInfo = nullptr;
    //             delete TempInfo;

    //             // TempButton = nullptr;
    //             // delete TempButton;
    //         }

    //         ChangeY += ButtonSpacingY;
    //         Cycles += 1;

    //     } while (Cycles < 3);

    //     m_IsLoaded = true;
    // }
}

