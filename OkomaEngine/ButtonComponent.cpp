#include "ButtonComponent.h"

ButtonComponent::ButtonComponent()
{
    // m_ID = "Button";
    m_MouseRec.x = 0.0f;
    m_MouseRec.y = 0.0f;
    m_MouseRec.width = 1.0f;
    m_MouseRec.height = 1.0f;

    // BUTTON DEFAULT INIT
    m_Text = " ";
    m_TextSize = 0.0f;
    m_TextureName = " ";
    m_Image = LoadTexture("Images/Tile/Default.png");

    m_Rectangle.x = 0.0f;
    m_Rectangle.y = 0.0f;
    m_Rectangle.width = 0.0f;
    m_Rectangle.height = 0.0f;

    m_Padding.x = 0.0f;
    m_Padding.y = 0.0f;

    m_Active = false;
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::Update(float deltaTime)
{
    //if (!m_Active) return;

    //// Update Mouse Position
    //if (IsMouseButtonUp(3))
    //{
    //    m_MouseRec.x = (float)GetMouseX();
    //    m_MouseRec.y = (float)GetMouseY();
    //}

    //if (IsMouseButtonDown(3))
    //{
    //    if (CheckCollisionRecs(m_Rectangle, m_MouseRec))
    //    {
    //        m_ButtonPressed = true;
    //    }
    //}
    //else
    //{
    //    m_ButtonPressed = false;
    //}

    //// IDLE
    //DrawTexture(
    //    m_Image,
    //    m_Rectangle.x,
    //    m_Rectangle.y,
    //    m_IdleColour
    //);

    //// HOVER
    //if (CheckCollisionRecs(m_Rectangle, m_MouseRec))
    //{
    //    DrawTexture(
    //        m_Image,
    //        m_Rectangle.x,
    //        m_Rectangle.y,
    //        m_HoverColour
    //    );
    //}

    //// CLICKED
    //if (m_ButtonPressed)
    //{
    //    DrawTexture(
    //        m_Image,
    //        m_Rectangle.x,
    //        m_Rectangle.y,
    //        m_ClickedColour
    //    );
    //}

    //// TEXT WITHIN THE BUTTON
    //DrawText(
    //    m_Text,
    //    m_Rectangle.x + m_Padding.x,
    //    m_Rectangle.y + m_Padding.y,
    //    m_TextSize,
    //    WHITE
    //);



}