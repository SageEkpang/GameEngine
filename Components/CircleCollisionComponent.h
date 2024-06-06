#ifndef CIRCLE_COLLISION_COMPONENT_H
#define CIRCLE_COLLISION_COMPONENT_H

// NEEDED INCLUDE(s)
#include "CollisionComponent.h"

class CircleCollisionComponent : public CollisionComponent
{
private:

    float m_Radius = 0.0f;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    CircleCollisionComponent() { m_HasCollision = true; };

    /// @brief Default Destructor for Class
    ~CircleCollisionComponent() { };


    // BASE FUNCTION(s)

    /// @brief Default Update function for Class
    void Update(float deltaTime) override { };

    /// @brief Default Draw function for Class
    void Draw() override { };


    // COLLIDER FUNCTION(s)
    virtual bool CollidesWith(CollisionComponent& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(RectangleCollisionComponent& other) override;
    virtual bool CollidesWith(CircleCollisionComponent& other) override;


    // GETTER FUNCTION(s)
    inline float GetRadius() const { return m_Radius; }

};

#endif