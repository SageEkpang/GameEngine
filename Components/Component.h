#ifndef COMPONENT_H
#define COMPONENT_H

// CUSTOM INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// NEEDED INCLUDE(s)
#include "TransformUtility.h"

class Component
{
private:

    bool m_Active = false;

protected:

    TransformUtility* m_Transform;
    const char* m_ID;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    Component() { m_ID = "Default"; };

    /// @brief Default Destructor for Class
    virtual ~Component() { };


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float deltaTime) = 0;

    /// @brief Default Draw function for Class
    virtual void Draw() = 0;


    // GETTER FUNCTION(s)
    inline virtual const char* GetID() {return this->m_ID; }
    inline virtual bool GetActiveState() { return m_Active; }

    inline virtual TransformUtility* GetTransform() {return m_Transform; }


    // SETTER FUNCTION(s)
    inline virtual void SetActiveState(bool active) { m_Active = active; }
    inline virtual void SetPosition(Vector2 position) { m_Transform->SetPosition(position);};
    inline virtual void SetPosition(float x, float y) { m_Transform->SetPosition(Vector2{x, y}); }

    inline virtual void SetScale(Vector2 scale) { m_Transform->SetScale(scale); };
    inline virtual void SetScale(float width, float height) { m_Transform->SetScale(Vector2{width, height}); }

    inline virtual void SetRotation(float rotation) { m_Transform->SetRotation(rotation); };
};

#endif