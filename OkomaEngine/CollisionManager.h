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

// TODO: Make sure to add the collision offset to the position of the transform when doing the collider calculations
enum Collider_Type_Collisions
{
    COLLIDER_TYPE_COLLISIONS_RECTANGLE_TO_RECTANGLE, // fix 

    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_RECTANGLE, // fix

    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CIRCLE, // fix
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_RECTANGLE, // fix
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CAPSULE,

    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_ORIENTED,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CAPSULE,

    COLLIDER_TYPE_COLLISIONS_POINT_TO_POINT, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_LINE, // Working // fix
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CIRCLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_RECTANGLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CAPSULE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_ORIENTED, // DO LATER (Maybe)

    COLLIDER_TYPE_COLLISIONS_LINE_TO_LINE, // Working // fix 
    COLLIDER_TYPE_COLLISIONS_LINE_TO_CIRCLE, // Working // fix
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
    Interval2D GetOrientedRectangleInterval(GameObjectEntity* orRectA, OKVector2<float>& axis);
    Interval2D GetRectangleInterval(GameObjectEntity* rectA, OKVector2<float>& axis);
    bool OverlapOnAxis(GameObjectEntity* rectA, GameObjectEntity* orRectB, OKVector2<float> axis);


private: // PRIVATE FUNCTION(s)

    // Closest point checks functions here, need to make them






public:

    // TODO: Make these functions static
    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager();

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

public: // EXTRA COLLISION FUNCTION(s) (ALTERNATIVES)

    // RECTANGLE (STATIC)
    
    static CollisionManifold S_RectangleToRectangle(OKVector2<float> recPositionA, OKVector2<float> recScaleA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_RectangleToRectangle(float recXA, float recYA, float recWidthA, float recHeightA, float recXB, float recYB, float recWidthB, float recHeightB);

    // CIRCLE (STATIC)
    static CollisionManifold S_CircleToCircle(OKVector2<float> circPositionA, float circRadiusA, OKVector2<float> circPositionB, float circRadiusB);
    static CollisionManifold S_CircleToCircle(float circXA, float circYA, float circRadiusA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_CircleToRectangle(OKVector2<float> circPositionA, float circRadiusA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_CircleToRectangle(float circXA, float circYA, float circRadiusA, float recXB, float recYB, float recWidthB, float recHeightB);

    // CAPSULE (STATIC)
    static CollisionManifold S_CapsuleToCircle(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> circPositionB, float circRadiusB);
    static CollisionManifold S_CapsuleToCircle(float capXA, float capYA, float capWidthA, float capHeightA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_CapsuleToRectangle(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_CapsuleToRectangle(float capXA, float capYA, float capWidthA, float capHeightA, float recXB, float recYB, float recWidthB, float recHeightB);

    static CollisionManifold S_CapsuleToCapsule();
    // static CollisionManifold S_CapsuleToCapsule();


    // ORIENTED RECTANGLE (STATIC)
    static CollisionManifold S_OrientedRectangleToOrientedRectangle();
    static CollisionManifold S_OrientedRectangleToRectangle();

    static CollisionManifold S_OrientedRectangleToCircle();
    static CollisionManifold S_OrientedRectangleToCapsule();

    // POINT (STATIC)
    static CollisionManifold S_PointToPoint(OKVector2<float> pointPositionA, float pointRadiusA, OKVector2<float> pointPositionB, float pointRadiusB);
    static CollisionManifold S_PointToPoint(float pointXA, float pointYA, float pointWidthA, float pointHeightA, float pointXB, float pointYB, float pointWidthB, float pointHeightB);

    static CollisionManifold S_PointToLine(OKVector2<float> pointPositionA, float pointRadiusA, OKVector2<float> lineStartPositionB, OKVector2<float> lineEndPositionB);
    static CollisionManifold S_PointToLine(float pointXA, float pointYA, float pointRadiusA, float lineStartXB, float lineStartYB, float lineEndXB, float lineEndYB);

    static CollisionManifold S_PointToCircle(OKVector2<float> pointPositionA, float pointRadiusA, OKVector2<float> circPositionB, OKVector2<float> circRadiusB);
    static CollisionManifold S_PointToCircle(float pointXA, float pointYA, float pointRadiusA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_PointToRectangle(OKVector2<float> pointPositionA, float pointRadiusA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_PointToRectangle(float pointXA, float pointYA, float pointRadiusA, float recXB, float recYB, float recWidthB, float recHeightB);

    static CollisionManifold S_PointToCapsule();
    static CollisionManifold S_PointToOrientedRectangle();

    // LINE (STATIC)
    static CollisionManifold S_LineToLine();
    static CollisionManifold S_LineToCircle();
    static CollisionManifold S_LineToRectangle();
    static CollisionManifold S_LineToOrientedRectangle();
    static CollisionManifold S_LineToCapsule();
};

#endif