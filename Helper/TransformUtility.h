#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Constants.h"
#include "Structs.h"

class TransformUtility
{
private:

    // TRANSFORM VARIABLE(s)
    TransformUtility* m_Parent;
    Vector2 m_Position;
    Vector2 m_Scale;
    float m_Rotation;

public:


    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    TransformUtility();

    /// @brief Default Destructor for Class
    ~TransformUtility();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime);


    // GETTER FUNCTION(s)
    inline TransformUtility* GetParent() { return this->m_Parent; }
    inline Vector2 GetPosition() { return this->m_Position; }
    inline Vector2 GetScale() { return this->m_Scale; }
    inline float GetRotation() { return this->m_Rotation; }


    // SETTER FUNCTION(s)
    inline void SetParent(TransformUtility* parent) { this->m_Parent = parent; }

    inline void SetPosition(Vector2 position) { this->m_Position = position; }
    inline void SetPosition(float x, float y) { this->m_Position = Vector2{x, y}; }
    inline void SetPositionX(float x) { this->m_Position.x = x; }
    inline void SetPositionY(float y) { this->m_Position.y = y; }

    inline void MoveUp(float y) { this->m_Position.y -= y; }
    inline void MoveLeft(float x) { this->m_Position.x -= x; }
    inline void MoveRight(float x) { this->m_Position.x += x; };
    inline void MoveDown(float y) { this->m_Position.y += y; }
    
    inline void SetScale(Vector2 scale) { this->m_Scale = scale; }
    inline void SetScale(float width, float height) { this->m_Scale = Vector2{width, height}; }
    inline void SetScaleX(float x) { this->m_Scale.x = x; }
    inline void SetScaleY(float y) { this->m_Scale.y = y; }

    inline void SetRotation(float rotation) { this->m_Rotation = rotation; }
};

#endif