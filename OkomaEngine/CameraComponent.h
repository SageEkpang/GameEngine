#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "ComponentEntity.h"

#include "OKVector2.h"

class OKCameraComponent : public ComponentEntity
{
private:

    // Camera Component
    Camera2D* m_Camera;

    OKVector2<float> m_Offset;
    OKVector2<float> m_Target;

    // Camera Variables
    float m_Rotation;
    float m_Zoom;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    OKCameraComponent();

    /// @brief Default Destructor for Class
    ~OKCameraComponent();



    // BASE FUNCTION(s)

    /// @brief Default Update for Class
    void Update(float deltaTime) override;

    /// @brief Default Draw for Class
    // void Draw() override;



    // GETTER FUNCTION(s)
    Camera2D GetCamera2D() { return *this->m_Camera; }
    OKVector2<float> GetCameraOffset() { return this->m_Offset; }
    OKVector2<float> GetCameraTarget() { return this->m_Target; }
    float GetCameraRotation() { return this->m_Rotation; }
    float GetCameraZoom() { return this->m_Zoom; }


    // SETTER FUNCTION(s)
    void SetCamera2D(Camera2D* camera) { this->m_Camera = camera; }
    void SetCameraOffset(OKVector2<float> offset) { this->m_Offset = offset; }
    void SetCameraTarget(OKVector2<float> target) { this->m_Target = target; }
    void SetCameraRotation(float rotation) { this->m_Rotation = rotation; }
    void SetCameraZoom(float zoom) { this->m_Zoom = zoom; }
};

#endif