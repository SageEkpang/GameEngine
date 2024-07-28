#ifndef COLLISION_COMPONENT_H
#define COLLISION_COMPONENT_H

// NEEDED INCLUDE(s)
#include "Component.h"

class RectangleCollisionComponent;
class CircleCollisionComponent;

class CollisionComponent : public Component
{
protected:

    bool m_HasCollided = false;
    bool m_HasCollision = false;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    CollisionComponent();
    

    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    virtual void Update(float deltaTime) override;

    /// @brief Default Draw function for Class
    virtual void Draw() override;


    // BASE COLLISION FUNCTION(s)
    virtual bool CollidesWith(CollisionComponent& other) = 0;
    virtual bool CollidesWith(CircleCollisionComponent& other) = 0;
    virtual bool CollidesWith(RectangleCollisionComponent& other) = 0;


    // GETTER FUNCTION(s)
    bool GetHasCollided() { return m_HasCollided; }
    bool GetHasCollision() { return m_HasCollision; }
};

#endif