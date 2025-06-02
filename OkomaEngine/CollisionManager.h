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
    // Physics Collider (Work on this )
    COLLIDER_TYPE_COLLISIONS_RECTANGLE_TO_RECTANGLE,

    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_CIRCLE_TO_RECTANGLE,

    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_RECTANGLE,
    COLLIDER_TYPE_COLLISIONS_CAPSULE_TO_CAPSULE,

    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_ORIENTED,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_RECTANGLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CIRCLE,
    COLLIDER_TYPE_COLLISIONS_ORIENTED_TO_CAPSULE,

    // HIT SCAN and Collider (Both)
    COLLIDER_TYPE_COLLISIONS_LINE_TO_LINE, // Working 
    COLLIDER_TYPE_COLLISIONS_LINE_TO_CIRCLE, // Need to work on this
    COLLIDER_TYPE_COLLISIONS_LINE_TO_RECTANGLE, // Working
    COLLIDER_TYPE_COLLISIONS_LINE_TO_CAPSULE, // Working 
    COLLIDER_TYPE_COLLISIONS_LINE_TO_ORIENTED, // Working


    // HIT SCAN COLLIDER (Only)
    COLLIDER_TYPE_COLLISIONS_POINT_TO_POINT, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_LINE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CIRCLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_RECTANGLE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_CAPSULE, // Working
    COLLIDER_TYPE_COLLISIONS_POINT_TO_ORIENTED // Working
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
    static OKVector2<float> ProjectPointOntoLine(OKVector2<float> point, OKVector2<float> positionReference, OKVector2<float> lineStart, OKVector2<float> lineEnd, OKVector2<float> offsetLine);
    static bool Multiply(float* out, const float* matA, int aRows, int aCols, const float* matB, int bRows, int bCols);

    // SAT / OBB Testing
    static Interval2D GetOrientedRectangleInterval(GameObjectEntity* orRectA, OKVector2<float>& axis);
    static Interval2D GetRectangleInterval(GameObjectEntity* rectA, OKVector2<float>& axis);
    static bool OverlapOnAxis(GameObjectEntity* rectA, GameObjectEntity* orRectB, OKVector2<float> axis);

public:

    // TODO: Make these functions static
    // CLASS FUNCTION(s)
    CollisionManager();
    ~CollisionManager();

    CollisionManifold CheckCollisions(GameObjectEntity* colliderA, GameObjectEntity* colliderB);

    // COLLIDER FUNCTION(s)

    // RECTANGLE
    static CollisionManifold RectangleToRectangle(GameObjectEntity* rectA, GameObjectEntity* rectB);

    // CIRCLE
    static CollisionManifold CircleToCircle(GameObjectEntity* circA, GameObjectEntity* circB);
    static CollisionManifold CircleToRectangle(GameObjectEntity* circA, GameObjectEntity* rectB);

    // CAPSULE
    static CollisionManifold CapsuleToCircle(GameObjectEntity* capsuleA, GameObjectEntity* circB);
    static CollisionManifold CapsuleToRectangle(GameObjectEntity* capsuleA, GameObjectEntity* rectB);
    static CollisionManifold CapsuleToCapsule(GameObjectEntity* capsuleA, GameObjectEntity* capsuleB);

    // ORIENTED RECTANGLE 
    static CollisionManifold OrientedRectangleToOrientedRectangle(GameObjectEntity* OrRectA, GameObjectEntity* OrRectB);
    static CollisionManifold OrientedRectangleToRectangle(GameObjectEntity* OrRectA, GameObjectEntity* rectB);

    static CollisionManifold OrientedRectangleToCircle(GameObjectEntity* OrRectA, GameObjectEntity* circB);
    static CollisionManifold OrientedRectangleToCapsule(GameObjectEntity* OrRectA, GameObjectEntity* capsuleB);

    // POINT
    static CollisionManifold PointToPoint(GameObjectEntity* pointA, GameObjectEntity* pointB);
    static CollisionManifold PointToLine(GameObjectEntity* pointA, GameObjectEntity* lineB);
    static CollisionManifold PointToCircle(GameObjectEntity* pointA, GameObjectEntity* circleB);
    static CollisionManifold PointToRectangle(GameObjectEntity* pointA, GameObjectEntity* rectB);
    static CollisionManifold PointToCapsule(GameObjectEntity* pointA, GameObjectEntity* capsuleB);
    static CollisionManifold PointToOrientedRectangle(GameObjectEntity* pointA, GameObjectEntity* OrRectB);

    // LINE
    static CollisionManifold LineToLine(GameObjectEntity* lineA, GameObjectEntity* lineB);
    static CollisionManifold LineToCircle(GameObjectEntity* lineA, GameObjectEntity* circB);
    static CollisionManifold LineToRectangle(GameObjectEntity* lineA, GameObjectEntity* rectB);
    static CollisionManifold LineToOrientedRectangle(GameObjectEntity* lineA, GameObjectEntity* OrRectB);
    static CollisionManifold LineToCapsule(GameObjectEntity* lineA, GameObjectEntity* capsuleB);

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

    static CollisionManifold S_CapsuleToCapsule(OKVector2<float> capPositionA, float capWidthA, float capHeightA, OKVector2<float> capPositionB, float capWidthB, float capHeightB);
    static CollisionManifold S_CapsuleToCapsule(float capXA, float capYA, float capWidthA, float capHeightA, float capXB, float capYB, float capWidthB, float capHeightB);

    // ORIENTED RECTANGLE (STATIC)
    static CollisionManifold S_OrientedRectangleToOrientedRectangle(OKVector2<float> orRecPositionA, OKVector2<float> orRecScaleA, float rotationA, OKVector2<float> orRecPositionB, OKVector2<float> orRecScaleB, float rotationB);
    static CollisionManifold S_OrientedRectangleToOrientedRectangle(float orRecXA, float orRecYA, float orRecWidthA, float orRecHeightA, float rotationA, float orRecXB, float orRecYB, float orRecWidthB, float orRecHeightB, float rotationB);

    static CollisionManifold S_OrientedRectangleToRectangle(OKVector2<float> orRecPositionA, OKVector2<float> orRecScaleA, float rotationA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_OrientedRectangleToRectangle(float orRecXA, float orRecYA, float orRecWidthA, float orRecHeightA, float rotationA, float recXB, float recYB, float recWidthB, float recHeightB);

    static CollisionManifold S_OrientedRectangleToCircle(OKVector2<float> orRecPositionA, OKVector2<float> orRecScaleA, float rotationA, OKVector2<float> circPositionB, float circRadiusB);
    static CollisionManifold S_OrientedRectangleToCircle(float orRecXA, float orRecYA, float orRecWidthA, float orRecHeightA, float rotationA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_OrientedRectangleToCapsule(OKVector2<float> orRecPositionA, OKVector2<float> orRecScaleA, float rotationA, OKVector2<float> capPositionB, float capWidthB, float capHeightB);
    static CollisionManifold S_OrientedRectangleToCapsule(float orRecXA, float orRecYA, float orRecWidthA, float orRecHeightA, float rotationA, float capXB, float capYB, float capWidthB, float capHeightB);

    // POINT (STATIC)
    static CollisionManifold S_PointToPoint(OKVector2<float> pointPositionA, OKVector2<float> pointPositionB);
    static CollisionManifold S_PointToPoint(float pointXA, float pointYA, float pointXB, float pointYB);

    static CollisionManifold S_PointToLine(OKVector2<float> pointPositionA, OKVector2<float> lineStartPositionB, OKVector2<float> lineEndPositionB);
    static CollisionManifold S_PointToLine(float pointXA, float pointYA, float lineStartXB, float lineStartYB, float lineEndXB, float lineEndYB);

    static CollisionManifold S_PointToCircle(OKVector2<float> pointPositionA, OKVector2<float> circPositionB, float circRadiusB);
    static CollisionManifold S_PointToCircle(float pointXA, float pointYA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_PointToRectangle(OKVector2<float> pointPositionA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_PointToRectangle(float pointXA, float pointYA, float recXB, float recYB, float recWidthB, float recHeightB);

    static CollisionManifold S_PointToCapsule(OKVector2<float> pointPositionA, OKVector2<float> capPositionB, float capWidthB, float capHeightB);
    static CollisionManifold S_PointToCapsule(float pointXA, float pointYA, float capXB, float capYB, float capWidthB, float capHeightB);

    static CollisionManifold S_PointToOrientedRectangle(OKVector2<float> pointPositionA, float pointRadiusA, OKVector2<float> orRecPositionB, OKVector2<float> orRecScaleB, float rotationB);
    static CollisionManifold S_PointToOrientedRectangle(float pointXA, float pointYA, float pointRadiusA, float orRecXB, float orRecYB, float orRecWidthB, float orRecHeightB, float rotationB);

    // LINE (STATIC)
    static CollisionManifold S_LineToLine(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> lineStartPositionB, OKVector2<float> lineEndPositionB);
    static CollisionManifold S_LineToLine(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float lineStartXB, float lineStartYB, float lineEndXB, float lineEndYB);

    static CollisionManifold S_LineToCircle(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> circPositionB, float circRadiusB);
    static CollisionManifold S_LineToCircle(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float circXB, float circYB, float circRadiusB);

    static CollisionManifold S_LineToRectangle(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> recPositionB, OKVector2<float> recScaleB);
    static CollisionManifold S_LineToRectangle(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float recXB, float recYB, float recWidthB, float recHeightB);

    static CollisionManifold S_LineToOrientedRectangle(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> orRecPositionB, OKVector2<float> orRecScaleB, float rotationB);
    static CollisionManifold S_LineToOrientedRectangle(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float orRecXB, float orRecYB, float orRecWidthB, float orRecHeightB, float rotationB);

    static CollisionManifold S_LineToCapsule(OKVector2<float> lineStartPositionA, OKVector2<float> lineEndPositionA, OKVector2<float> capPositionB, float capWidthB, float capHeightB);
    static CollisionManifold S_LineToCapsule(float lineStartXA, float lineStartYA, float lineEndXA, float lineEndYA, float capXB, float capYB, float capWidthB, float capHeightB);
};

#endif