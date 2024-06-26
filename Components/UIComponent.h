#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include "Component.h"

class UIComponent : public Component
{
private:

    // UI COMPONENT VARIABLE(s)
    Vector2Utility m_CanvasPosition;
    Vector2Utility m_CanvasScale;
    Vector2Utility m_AnchorPoint;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Contructor for Class
    UIComponent();

    /// @brief Default Destructor for Class
    ~UIComponent();



    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw();



    // GETTER FUNCTION(s)
    Rectangle GetCanvas() { Rectangle{m_CanvasPosition.x, m_CanvasPosition.y, m_CanvasScale.x, m_CanvasScale.y}; }
    Vector2Utility GetCanvasPosition() { this->m_CanvasPosition; }
    Vector2Utility GetCanvasScale() { this->m_CanvasScale; }
    Vector2Utility GetAnchorPoint() { this->m_AnchorPoint; }


    // SETTER FUNCTION(s)
    void SetCanvas(Rectangle canvas) {
        m_CanvasPosition.x = canvas.x; 
        m_CanvasPosition.y = canvas.y;
        m_CanvasScale.x = canvas.width; 
        m_CanvasScale.y = canvas.height;
    }

    void SetPosition(Vector2Utility position) {m_CanvasPosition = position; }
    void SetScale(Vector2Utility scale) { m_CanvasScale = scale; }
    void SetAnchor(Vector2Utility anchor) { m_AnchorPoint = anchor; }

};

#endif