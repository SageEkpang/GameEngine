#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H

// DIRECTORY INCLUDES
#include "Component.h"

class ButtonComponent : public Component
{
private:

    // BASE VARIABLE(s)
    Rectangle m_MouseRec;
    bool m_ButtonPressed = false;


    // BUTTON COMPONENT VARIABLE(s)
    const char* m_Text;
    const char* m_TextureName;

    Texture2D m_Image;
    Rectangle m_Rectangle;
    Vector2 m_Padding;

    bool m_Active;
    float m_TextSize;

    // GameInfo m_Info;

    // BUTTON COLOR
    Color m_IdleColour = Color{220, 220, 220, 255};
    Color m_HoverColour = Color{255, 255, 255, 255};
    Color m_ClickedColour = Color{200, 200, 200, 255};

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    ButtonComponent(); // TODO: Add UI Component reference here

    /// @brief Default Destructor for Class
    ~ButtonComponent();



    // BASE FUNCTION(s)

    ///@brief Default Update function for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // GETTER FUNCTION(s)
    bool GetButtonPressed() { return m_ButtonPressed; }
    const char* GetText() { return this->m_Text; }
    float GetTextSize() { return this->m_TextSize; }
    const char* GetTextureName() { return this->m_TextureName; }
    Texture2D GetImage() { return this->m_Image; }
    Rectangle GetRectangle() { return this->m_Rectangle; }
    Vector2 GetPadding() { return this->m_Padding; }
    bool GetActive() { return this->m_Active; }


    // SETTER FUNCTION(s)
    void SetText(const char* text) { this->m_Text = text; }
    void SetTextSize(float textSize) { this->m_TextSize = textSize; }
    void SetTextureName(const char* textureName) { this->m_Image = LoadTexture(textureName); }
    void SetRectangle(Rectangle rectangle) { this->m_Rectangle = rectangle; }
    void SetImageWidthHeight(int width, int height) { this->m_Image.width = width; this->m_Image.height = height; }
    void SetPadding(Vector2 padding) { this->m_Padding = padding; }
    void SetActive(bool active) { this->m_Active = active; }
};

#endif