#include "UIComponent.h"

UIComponent::UIComponent() 
{
    m_ID = "UI";
    m_CanvasPosition = Vector2Utility();
    m_CanvasScale = Vector2Utility();
    m_AnchorPoint = Vector2Utility();
}

UIComponent::~UIComponent() 
{
}

void UIComponent::Update(float deltaTime) 
{
    

}

void UIComponent::Draw() 
{
    

}
