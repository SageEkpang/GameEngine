#ifndef COLLIDER_H
#define COLLIDER_H

// NEEDED INCLUDE(s)
#include "HeaderManager.h"
#include "CollisionManifold.h"
#include "OKTransform2.h"

// PARENT INCLUDE(s)
#include "Component.h"

enum ColliderType
{
    COLLIDER_POINT,
    COLLIDER_RECTANGLE,
    COLLIDER_CIRCLE,
    COLLIDER_CAPSULE,
    COLLIDER_ORIENTED_RECTANGLE,
    COLLIDER_COMPLEX,
    COLLIDER_LINE
};

class Collider : public Component
{
protected: // PROTECTED VARIABLE(s)

    // BASE VARIABLE(s)
    OKTransform2<float>* m_Transform = nullptr;
    float m_Radius{};

    // LINE VARIABLE(s)
    OKVector2<float> m_LineStartPosition;
    OKVector2<float> m_LineEndPosition;

    // COLLIDER VARIABLE(s)
    ColliderType m_ColliderType;
    std::vector<OKVector2<float>> m_Vertices;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)

    Collider();

    // RECTANGLE
    /// @brief Rectangle Collider Constructor
    Collider(OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true); // REFACT: bool solveRotation

    // CIRCLE
    /// @brief Circle Collider Constructor
    Collider(OKTransform2<float>* transform, float radius, bool isPoint = false);

    // LINE
    // @brief Line Collider Constructor
    Collider(OKTransform2<float>* transform, OKVector2<float> start_position, OKVector2<float> end_position);

    // COMPLEX
    /// @brief Complex Collider Constructor 
    // Collider(const char* tag, OKTransform2<float> transform);

    // DESTRUCTOR
    ~Collider();


    // BASE FUNCTION(s)
    void Update(const float deltaTime);
    void Draw();

    // NOTE: Check if it is an absolute enter or a partial enter


    // GETTER FUNCTION(s)
    inline OKTransform2<float>* GetTransform() { return m_Transform; }
    inline OKVector2<float> GetPosition() { return m_Transform->position; }
    inline OKVector2<float> GetScale() { return m_Transform->scale; }
    inline float GetRotation() { return m_Transform->rotation; }

    inline ColliderType GetColliderType() const { return m_ColliderType; }

    inline float GetRadius() const { return m_Radius; }
    inline OKVector2<float> GetLineStart() const { return m_LineStartPosition; }
    inline OKVector2<float> GetLineEnd() const { return m_LineEndPosition; }

    // SETTER FUNCTION(s)
    inline void SetTransform(OKTransform2<float>* transform) { m_Transform = transform; }
    inline void SetPosition(OKVector2<float> position) { m_Transform->position = position; }
    inline void SetScale(OKVector2<float> scale) { m_Transform->scale = scale; }
    inline void SetRotation(float rotation) { m_Transform->rotation = rotation; }

    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }

    inline void SetRadius(float radius) { m_Radius = radius; }
    inline void SetLineStartPosition(OKVector2<float> lineStartPosition) { m_LineStartPosition = lineStartPosition; }
    inline void SetLineEndPosition(OKVector2<float> lineEndPosition) { m_LineEndPosition = lineEndPosition; }


    // POLYGONE FUNCTION(s)
    float PolygonArea();

};

// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

#endif