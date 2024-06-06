#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include "Component.h"

class RenderComponent : public Component
{
private:

    // RENDER COMPONENT VARIABLE(s)
    Texture2D m_SingleImage;
    Texture2D m_SpriteSheetImage;
    Vector2 m_TexturePosition;
    Vector2 m_TextureScale;
    float m_TextureRotation;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    RenderComponent();

    /// @brief Default Destructor for Class
    ~RenderComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() override;


    // GETTER FUNCTION(s)
    Texture2D GetImageSpriteSingle() { return this->m_SingleImage; }
    Texture2D GetImageSpriteSheet() { return this->m_SpriteSheetImage; }

    Vector2 GetImagePosition() { return this->m_TexturePosition; }
    Vector2 GetImageScale() { return this->m_TextureScale; }
    float GetImageRotation() { return this->m_TextureRotation; }
    
    
    // SETTER FUNCTION(s)
    void SetTextureSingleImage(const char* textureName) { this->m_SingleImage = LoadTexture(textureName); }
    void SetTextureSpriteSheetImage(const char* textureSpriteSheetName) { this->m_SpriteSheetImage = LoadTexture(textureSpriteSheetName); }
    void SetTexturePosition(Vector2 texturePosition) { this->m_TexturePosition = texturePosition; }

};

#endif