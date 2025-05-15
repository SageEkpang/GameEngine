#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H

#include "ColliderEntity.h"
#include "CollisionManifold.h"
#include <utility>
#include <map>

// TODO: Pre-fix collision
enum Collider_Type_Collisions
{
    RECTANGLE_TO_RECTANGLE,

    CIRCLE_TO_CIRCLE,
    CIRCLE_TO_RECTANGLE,

    CAPSULE_TO_CAPSULE,
    CAPSULE_TO_RECTANGLE,
    CAPSULE_TO_CIRCLE,

    ORIENTED_TO_ORIENTED,
    ORIENTED_TO_RECTANGLE,
    ORIENTED_TO_CIRCLE,
    ORIENTED_TO_CAPSULE,

    POINT_TO_POINT, // Working
    POINT_TO_LINE, // Working
    POINT_TO_CIRCLE, // Working
    POINT_TO_RECTANGLE, // Working
    POINT_TO_CAPSULE, // Working
    POINT_TO_ORIENTED, // DO LATER (Maybe)

    LINE_TO_LINE, // Working
    LINE_TO_CIRCLE, // Working
    LINE_TO_RECTANGLE, // Working
    LINE_TO_CAPSULE, // Do Later
    LINE_TO_ORIENTED // Do Later

};

struct Interval2D
{
    OKVector2<float> max;
    OKVector2<float> min;
};

class CollisionManager
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
    Interval2D GetOrientedRectangleInterval(ColliderEntity* orRectA, OKVector2<float>& axis);
    Interval2D GetRectangleInterval(ColliderEntity* rectA, OKVector2<float>& axis);
    bool OverlapOnAxis(ColliderEntity* rectA, ColliderEntity* orRectB, OKVector2<float> axis);

public:

    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager() {};

    // BASE FUNCTION(s)
    void Update(float deltaTime) {};
    void Draw() {};

    CollisionManifold CheckCollisions(ColliderEntity* colliderA, ColliderEntity* colliderB);

    // COLLIDER FUNCTION(s)

    // RECTANGLE
    CollisionManifold RectangleToRectangle(ColliderEntity* rectA, ColliderEntity* rectB);

    // CIRCLE
    CollisionManifold CircleToCircle(ColliderEntity* circA, ColliderEntity* circB);
    CollisionManifold CircleToRectangle(ColliderEntity* circA, ColliderEntity* rectB);

    // CAPSULE
    CollisionManifold CapsuleToCircle(ColliderEntity* capsuleA, ColliderEntity* circB);
    CollisionManifold CapsuleToRectangle(ColliderEntity* capsuleA, ColliderEntity* rectB);
    CollisionManifold CapsuleToCapsule(ColliderEntity* capsuleA, ColliderEntity* capsuleB);

    // ORIENTED RECTANGLE 
    CollisionManifold OrientedRectangleToOrientedRectangle(ColliderEntity* OrRectA, ColliderEntity* OrRectB);
    CollisionManifold OrientedRectangleToRectangle(ColliderEntity* OrRectA, ColliderEntity* rectB);

    CollisionManifold OrientedRectangleToCircle(ColliderEntity* OrRectA, ColliderEntity* circB);
    CollisionManifold OrientedRectangleToCapsule(ColliderEntity* OrRectA, ColliderEntity* capsuleB);

    // POINT
    CollisionManifold PointToPoint(ColliderEntity* pointA, ColliderEntity* pointB);
    CollisionManifold PointToLine(ColliderEntity* pointA, ColliderEntity* lineB);
    CollisionManifold PointToCircle(ColliderEntity* pointA, ColliderEntity* circleB);
    CollisionManifold PointToRectangle(ColliderEntity* pointA, ColliderEntity* rectB);
    CollisionManifold PointToCapsule(ColliderEntity* pointA, ColliderEntity* capsuleB);
    CollisionManifold PointToOrientedRectangle(ColliderEntity* pointA, ColliderEntity* OrRectB);

    // LINE
    CollisionManifold LineToLine(ColliderEntity* lineA, ColliderEntity* lineB);
    CollisionManifold LineToCircle(ColliderEntity* lineA, ColliderEntity* circB);
    CollisionManifold LineToRectangle(ColliderEntity* lineA, ColliderEntity* rectB);
    CollisionManifold LineToOrientedRectangle(ColliderEntity* lineA, ColliderEntity* OrRectB);
    CollisionManifold LineToCapsule(ColliderEntity* lineA, ColliderEntity* capsuleB);

};

#endif