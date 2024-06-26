#ifndef COMPONENT_H
#define COMPONENT_H

// CUSTOM INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

class Component
{
private:

    bool m_Active = true;

protected:

    Transform2Utility* m_Transform;
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

    inline virtual Transform2Utility* GetTransform() {return m_Transform; }


    // SETTER FUNCTION(s)
    inline virtual void SetActiveState(bool active) { m_Active = active; }
    inline virtual void SetTransform(Transform2Utility* transform) { m_Transform = transform; }
    inline virtual void SetPosition(Vector2Utility position) { m_Transform->position = position;}
    inline virtual void SetScale(Vector2Utility scale) { m_Transform->scale = scale; }
    inline virtual void SetRotation(float rotation) { m_Transform->rotation = rotation; }
};

#endif