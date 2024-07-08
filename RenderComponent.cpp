#include "RenderComponent.h"

RenderComponent::RenderComponent() 
{
    m_ID = "Render";
    m_SingleImage = Texture2D();
    m_SpriteSheetImage = Texture2D();
    m_TexturePosition = Vector2Utility();
    m_TextureScale = Vector2Utility();
    m_TextureRotation = 0;
}

RenderComponent::~RenderComponent() 
{
    
}

void RenderComponent::Update(float deltaTime) 
{
    
}

void RenderComponent::Draw() 
{
    
}
