#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H

#include "Collider.h"
#include "CollisionManifold.h"
#include <utility>
#include <map>

enum Collider_Type_Collisions
{
    RECTANGLE_TO_RECTANGLE,

    CIRCLE_TO_CIRCLE,
    CIRCLE_TO_RECTANGLE,

    CAPSULE_TO_CIRCLE,
    CAPSULE_TO_RECTANGLE,
    CAPSULE_TO_CAPSULE,

    ORIENTED_TO_ORIENTED,
    ORIENTED_TO_RECTANGLE,
    ORIENTED_TO_CIRCLE,
    ORIENTED_TO_CAPSULE
};

struct Interval2D
{
    OKVector2<float> max;
    OKVector2<float> min;
};

class ColliderManager
{
private:

    int m_CollisionDelta = 0;

    // Collider Typedef Pairs
    typedef std::pair<ColliderType, ColliderType> col_type_pair;
    typedef std::map<col_type_pair, Collider_Type_Collisions> col_mapping;

    col_mapping m_CollisionMapping;

    // NOTE: This is for the Rectangle Collision Code
    OKVector2<float> ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine);
    bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols);


    // SAT / OBB Testing
    Interval2D GetOrientedRectangleInterval(Collider* orRectA, OKVector2<float>& axis);
    Interval2D GetRectangleInterval(Collider* rectA, OKVector2<float>& axis);
    bool OverlapOnAxis(Collider* rectA, Collider* orRectB, OKVector2<float> axis);

public:

    // CLASS FUNCTION(s)
    ColliderManager();
    ~ColliderManager() {};

    // BASE FUNCTION(s)
    void Update(float deltaTime) {};
    void Draw() {};

    CollisionManifold CheckCollisions(Collider* colliderA, Collider* colliderB);

    // COLLIDER FUNCTION(s)

    // RECTANGLE
    CollisionManifold RectangleToRectangle(Collider* rectA, Collider* rectB);

    // CIRCLE
    CollisionManifold CircleToCircle(Collider* circA, Collider* circB);
    CollisionManifold CircleToRectangle(Collider* circA, Collider* rectB);

    // CAPSULE
    CollisionManifold CapsuleToCircle(Collider* capsuleA, Collider* circB);
    CollisionManifold CapsuleToRectangle(Collider* capsuleA, Collider* rectB);
    CollisionManifold CapsuleToCapsule(Collider* capsuleA, Collider* capsuleB);

    // ORIENTED RECTANGLE 
    CollisionManifold OrientedRectangleToOrientedRectangle(Collider* OrRectA, Collider* OrRectB);
    CollisionManifold OrientedRectangleToRectangle(Collider* OrRectA, Collider* rectB);

    CollisionManifold OrientedRectangleToCircle(Collider* OrRectA, Collider* circB);
    CollisionManifold OrientedRectangleToCapsule(Collider* OrRectA, Collider* capsuleB);

};

#endif