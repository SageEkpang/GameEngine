#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

// NEEDED INCLUDE(s)
#include "Component.h"

class CollisionComponent; 

class PhysicsComponent : public Component
{
private:

    // COLLISION COMPONENT VARIABLE(s)
    CollisionComponent* m_CollisionComponent;


    // PHYSICS COMPONENT VARIABLE(s)

    bool m_IsLookingLeft;
    bool m_IsMoving;
    float m_Velocity;

    bool m_IsGrounded;
    bool m_IsInAir;
    bool m_IsMoving;


    // FORCES VARIABLES(s)

    Vector2 m_Gravity;
    Vector2 m_Drag;
    Vector2 m_Friction;
    Vector2 m_Impulse;
    Vector2 m_Force;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    PhysicsComponent(CollisionComponent* collisionComponent);

    /// @brief Default Destructor for Class
    ~PhysicsComponent();


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class 
    void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    void Draw() { };



    // GETTER FUNCTION(s)




    // SETTER FUNCTION(s)




};

#endif