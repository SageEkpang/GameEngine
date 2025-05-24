#ifndef COLLIDER_MANAGER_H
#define COLLIDER_MANAGER_H

#include "GameObjectEntity.h"
#include "ColliderEntity.h"
#include "CollisionManifold.h"
#include <utility>
#include <map>

#include <typeindex>
#include <typeinfo>

class RectangleColliderComponent;
class OrientedRectangleColliderComponent;
class CircleColliderComponent;
class LineColliderComponent;
class CapsuleColliderComponent;
class ComplexColliderComponent;
class PointColliderComponent;

enum Collider_Type_Collisions
{
    COLLIDER_TYPE_COLLISIONS_RECTANGLE_TO_RECTANGLE,

    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_RECTANGLE,

    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CAPSULE,
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_RECTANGLE,
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CIRCLE,

    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_ORIENTED,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CAPSULE,

    COLLIDER_TYPE_COLLISIONS_POINT_TO_POINT, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_LINE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CIRCLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_RECTANGLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CAPSULE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_ORIENTED, // DO LATER (Maybe)

    COLLIDER_TYPE_COLLISIONS_LINE_TO_LINE, // Working
    COLLIDER_TYPE_COLLISIONS_LINE_TO_CIRCLE, // Working
    COLLIDER_TYPE_COLLISIONS_LINE_TO_RECTANGLE, // Working
    COLLIDER_TYPE_COLLISIONS_LINE_TO_CAPSULE, // Do Later
    COLLIDER_TYPE_COLLISIONS_LINE_TO_ORIENTED // Do Later
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
    typedef std::pair<std::type_index, std::type_index> col_type_pair;
    std::map<col_type_pair, Collider_Type_Collisions> m_CollisionMapping;

    // NOTE: This is for the Rectangle Collision Code
    OKVector2<float> ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine);
    bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols);

    // SAT / OBB Testing
    Interval2D GetOrientedRectangleInterval(OrientedRectangleColliderComponent* orRectA, OKVector2<float>& axis);
    Interval2D GetRectangleInterval(RectangleColliderComponent* rectA, OKVector2<float>& axis);
    bool OverlapOnAxis(RectangleColliderComponent* rectA, OrientedRectangleColliderComponent* orRectB, OKVector2<float> axis);

public:

    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager();

    CollisionManifold CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB);

    // COLLIDER FUNCTION(s)

    // RECTANGLE
    CollisionManifold RectangleToRectangle(RectangleColliderComponent* rectA, RectangleColliderComponent* rectB);

    // CIRCLE
    CollisionManifold CircleToCircle(CircleColliderComponent* circA, CircleColliderComponent* circB);
    CollisionManifold CircleToRectangle(CircleColliderComponent* circA, RectangleColliderComponent* rectB);

    // CAPSULE
    CollisionManifold CapsuleToCircle(CapsuleColliderComponent* capsuleA, CircleColliderComponent* circB);
    CollisionManifold CapsuleToRectangle(CapsuleColliderComponent* capsuleA, RectangleColliderComponent* rectB);
    CollisionManifold CapsuleToCapsule(CapsuleColliderComponent* capsuleA, CapsuleColliderComponent* capsuleB);

    // ORIENTED RECTANGLE 
    CollisionManifold OrientedRectangleToOrientedRectangle(OrientedRectangleColliderComponent* OrRectA, OrientedRectangleColliderComponent* OrRectB);
    CollisionManifold OrientedRectangleToRectangle(OrientedRectangleColliderComponent* OrRectA, RectangleColliderComponent* rectB);

    CollisionManifold OrientedRectangleToCircle(OrientedRectangleColliderComponent* OrRectA, CircleColliderComponent* circB);
    CollisionManifold OrientedRectangleToCapsule(OrientedRectangleColliderComponent* OrRectA, CapsuleColliderComponent* capsuleB);

    // FIX THESE
    // POINT
    CollisionManifold PointToPoint(PointColliderComponent* pointA, PointColliderComponent* pointB);
    CollisionManifold PointToLine(PointColliderComponent* pointA, LineColliderComponent* lineB);
    CollisionManifold PointToCircle(PointColliderComponent* pointA, CircleColliderComponent* circleB);
    CollisionManifold PointToRectangle(PointColliderComponent* pointA, RectangleColliderComponent* rectB);
    CollisionManifold PointToCapsule(PointColliderComponent* pointA, CapsuleColliderComponent* capsuleB);
    CollisionManifold PointToOrientedRectangle(PointColliderComponent* pointA, OrientedRectangleColliderComponent* OrRectB);

    // LINE
    CollisionManifold LineToLine(LineColliderComponent* lineA, LineColliderComponent* lineB);
    CollisionManifold LineToCircle(LineColliderComponent* lineA, CircleColliderComponent* circB);
    CollisionManifold LineToRectangle(LineColliderComponent* lineA, RectangleColliderComponent* rectB);
    CollisionManifold LineToOrientedRectangle(LineColliderComponent* lineA, OrientedRectangleColliderComponent* OrRectB);
    CollisionManifold LineToCapsule(LineColliderComponent* lineA, CapsuleColliderComponent* capsuleB);

public: // EXTRA COLLISION FUNCTION(s) (ALTERNATIVES)







};

#endif