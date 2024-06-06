#ifndef RECTANGLE_COLLISION_COMPONENT_H
#define RECTANGLE_COLLISION_COMPONENT_H

// NEEDED INCLUDE(s)
#include "CollisionComponent.h"

class RectangleCollisionComponent : public CollisionComponent
{
private:

    Vector2 m_Max;
    Vector2 m_Min;

    Vector2 m_Extents;
    Vector2 m_HalfExtents;

    Vector2 m_CentrePoint;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    RectangleCollisionComponent() { m_HasCollision = true; };

    /// @brief Default Destructor for Class
    ~RectangleCollisionComponent() { };


    // BASE FUNCTIONS

    /// @brief Default Update function for Class
    void Update(float deltaTime) override { };

    /// @brief Default Draw function for Class
    void Draw() override { };


    // COLLIDER FUNCTION(s)
    virtual bool CollidesWith(CollisionComponent& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(RectangleCollisionComponent& other) override;
    virtual bool CollidesWith(CircleCollisionComponent& other) override;


    // GETTER FUNCTION(s)
    inline Vector2 GetMax() { return m_Max; }
    inline Vector2 GetMin() { return m_Min; }

    inline Vector2 GetExtents() { return m_Extents; }
    inline Vector2 GetHalfExtents() { return m_HalfExtents; }

    inline Vector2 GetCentrePoint() { return m_CentrePoint; }
};

#endif