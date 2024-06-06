#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"

class CameraComponent : public Component
{
private:

    // Camera Component
    Camera2D* m_Camera;

    // Camera Variables
    Vector2 m_Offset;
    Vector2 m_Target;
    float m_Rotation;
    float m_Zoom;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    CameraComponent();

    /// @brief Default Destructor for Class
    ~CameraComponent();



    // BASE FUNCTION(s)

    /// @brief Default Update for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw for Class
    void Draw() override;



    // GETTER FUNCTION(s)
    Camera2D GetCamera2D() { return *this->m_Camera; }
    Vector2 GetCameraOffset() { return this->m_Offset; }
    Vector2 GetCameraTarget() { return this->m_Target; }
    float GetCameraRotation() { return this->m_Rotation; }
    float GetCameraZoom() { return this->m_Zoom; }


    // SETTER FUNCTION(s)
    void SetCamera2D(Camera2D* camera) { this->m_Camera = camera; }
    Vector2 SetCameraOffset(Vector2 offset) { this->m_Offset = offset; }
    Vector2 SetCameraTarget(Vector2 target) { this->m_Target = target; }
    float SetCameraRotation(float rotation) { this->m_Rotation = rotation; }
    float SetCameraZoom(float zoom) { this->m_Zoom = zoom; }
};

#endif