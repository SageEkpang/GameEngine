#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H

#include "GameObjectEntity.h"
#include "ColliderEntity.h"
#include "CollisionManifold.h"
#include <utility>
#include <map>

class RectangleColliderComponent;
class CircleColliderComponent;
class LineColliderComponent;
class CapsuleColliderComponent;
class ComplexColliderComponent;


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
    Interval2D GetOrientedRectangleInterval(RectangleColliderComponent* orRectA, OKVector2<float>& axis);
    Interval2D GetRectangleInterval(RectangleColliderComponent* rectA, OKVector2<float>& axis);
    bool OverlapOnAxis(GameObjectEntity* rectA, GameObjectEntity* orRectB, OKVector2<float> axis);

public:

    // CLASS FUNCTION(s)
    CollisionManager() { };
    ~CollisionManager() { };

    // BASE FUNCTION(s)
    void Update(float deltaTime) {};
    void Draw() {};

    CollisionManifold CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB);

    // COLLIDER FUNCTION(s)

    // RECTANGLE
    CollisionManifold RectangleToRectangle(GameObjectEntity* rectA, GameObjectEntity* rectB);

    // CIRCLE
    CollisionManifold CircleToCircle(GameObjectEntity* circA, GameObjectEntity* circB);
    CollisionManifold CircleToRectangle(GameObjectEntity* circA, GameObjectEntity* rectB);

    // CAPSULE
    CollisionManifold CapsuleToCircle(GameObjectEntity* capsuleA, GameObjectEntity* circB);
    CollisionManifold CapsuleToRectangle(GameObjectEntity* capsuleA, GameObjectEntity* rectB);
    CollisionManifold CapsuleToCapsule(GameObjectEntity* capsuleA, GameObjectEntity* capsuleB);

    // ORIENTED RECTANGLE 
    CollisionManifold OrientedRectangleToOrientedRectangle(GameObjectEntity* OrRectA, GameObjectEntity* OrRectB);
    CollisionManifold OrientedRectangleToRectangle(GameObjectEntity* OrRectA, GameObjectEntity* rectB);

    CollisionManifold OrientedRectangleToCircle(GameObjectEntity* OrRectA, GameObjectEntity* circB);
    CollisionManifold OrientedRectangleToCapsule(GameObjectEntity* OrRectA, GameObjectEntity* capsuleB);

    // POINT
    CollisionManifold PointToPoint(GameObjectEntity* pointA, GameObjectEntity* pointB);
    CollisionManifold PointToLine(GameObjectEntity* pointA, GameObjectEntity* lineB);
    CollisionManifold PointToCircle(GameObjectEntity* pointA, GameObjectEntity* circleB);
    CollisionManifold PointToRectangle(GameObjectEntity* pointA, GameObjectEntity* rectB);
    CollisionManifold PointToCapsule(GameObjectEntity* pointA, GameObjectEntity* capsuleB);
    CollisionManifold PointToOrientedRectangle(GameObjectEntity* pointA, GameObjectEntity* OrRectB);

    // LINE
    CollisionManifold LineToLine(GameObjectEntity* lineA, GameObjectEntity* lineB);
    CollisionManifold LineToCircle(GameObjectEntity* lineA, GameObjectEntity* circB);
    CollisionManifold LineToRectangle(GameObjectEntity* lineA, GameObjectEntity* rectB);
    CollisionManifold LineToOrientedRectangle(GameObjectEntity* lineA, GameObjectEntity* OrRectB);
    CollisionManifold LineToCapsule(GameObjectEntity* lineA, GameObjectEntity* capsuleB);

};

#endif