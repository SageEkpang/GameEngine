#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "ComponentEntity.h"
#include "OKVector2.h"

class CameraComponent : public ComponentEntity
{
public: // PUBLIC ACCESS VARIABLE(s)

    // Camera Component
    Camera2D m_Camera;

    OKVector2<float> m_Offset;
    OKVector2<float> m_Target;

    // Camera Variables
    float m_Rotation;
    float m_Zoom;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s) (Components)
    CameraComponent();



    // CLASS FUNCTION(s) (General)
    /// @brief Default Destructor for Class
    ~CameraComponent();



    // BASE FUNCTION(s)

    /// @brief Default Update for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw for Class
    void Draw() override;

};

#endif