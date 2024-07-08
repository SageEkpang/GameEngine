#ifndef RECTANGLE_COLLISION_COMPONENT_H
#define RECTANGLE_COLLISION_COMPONENT_H

// NEEDED INCLUDE(s)
#include "CollisionComponent.h"

class RectangleCollisionComponent : public CollisionComponent
{
private:

    Vector2Utility m_Max;
    Vector2Utility m_Min;

    Vector2Utility m_Extents;
    Vector2Utility m_HalfExtents;

    Vector2Utility m_CentrePoint;

public:

    // CLASS FUNCTION(s)

    /// @brief Default Constructor for Class
    RectangleCollisionComponent() { m_HasCollision = true; }

    /// @brief Default Destructor for Class
    ~RectangleCollisionComponent() { }


    // BASE FUNCTIONS

    /// @brief Default Update function for Class
    void Update(float deltaTime) override { }

    /// @brief Default Draw function for Class
    void Draw() override { }


    // COLLIDER FUNCTION(s)
    virtual bool CollidesWith(CollisionComponent& other) override { return other.CollidesWith(*this); }
    virtual bool CollidesWith(RectangleCollisionComponent& other) override;
    virtual bool CollidesWith(CircleCollisionComponent& other) override;


    // GETTER FUNCTION(s)
    inline Vector2Utility GetMax() { return m_Max; }
    inline Vector2Utility GetMin() { return m_Min; }

    inline Vector2Utility GetExtents() { return m_Extents; }
    inline Vector2Utility GetHalfExtents() { return m_HalfExtents; }

    inline Vector2Utility GetCentrePoint() { return m_CentrePoint; }
};

#endif