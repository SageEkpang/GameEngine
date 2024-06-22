#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// CUSTOM INCLUDE(s)
#include "Constants.h"
#include "Structs.h"

// COMPONENT INCLUDE(s)
#include "Component.h"

class GameObject
{
protected:

    // GAMEOBJECT VARIABLE(s)
    std::string m_Tag;
    Transform2Utility* m_Transform;

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
    inline virtual Transform2Utility* GetTransform() { return this->m_Transform; }
    inline virtual std::vector<Component*> GetComponents() { return m_Components; }

    template<typename T>
    T GetComponent();

    // SETTER FUNCTION(s)
    inline void SetTag(std::string tag) { this->m_Tag = tag; }
    inline void AddComponent(Component* component) { m_Components.push_back(component); }

    inline virtual void SetPosition(Vector2Utility position) { m_Transform->position = position; }
    inline virtual void SetScale(Vector2Utility scale) { m_Transform->scale = scale; }
    inline virtual void SetRotation(float rotation) { m_Transform->rotation = rotation; }
};

#endif