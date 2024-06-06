#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// CUSTOM INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// NEEDED INCLUDE(s)
#include "TransformUtility.h"

// COMPONENT INCLUDE(s)
#include "Component.h"

class GameObject
{
protected:

    // GAMEOBJECT VARIABLE(s)
    std::string m_Tag;
    TransformUtility* m_Transform;

    // COMPONENT VARIABLE(s)
    std::vector<Component*> m_Components;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    GameObject(std::string tag = "Default");

    /// @brief Default Destructor for Class
    virtual ~GameObject();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float deltaTime);

    /// @brief Defulat Draw function for Class
    virtual void Draw();


    // GETTER FUNCTION(s)
    inline std::string GetTag() { return this->m_Tag; }
    inline virtual TransformUtility* GetTransform() { return this->m_Transform; }
    inline virtual std::vector<Component*> GetComponents() { return m_Components; };

    // SETTER FUNCTION(s)
    inline void SetTag(std::string tag) { this->m_Tag = tag; }
    inline void AddComponent(Component* component) { m_Components.push_back(component); }

    inline virtual void SetPosition(Vector2 position) { m_Transform->SetPosition(position); }
    inline virtual void SetScale(Vector2 scale) { m_Transform->SetScale(scale); }
    inline virtual void SetRotation(float rotation) { m_Transform->SetRotation(rotation); }
};

#endif