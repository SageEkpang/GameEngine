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
    COLLIDER_RECTANGLE,
    COLLIDER_CIRCLE,
    COLLIDER_CAPSULE,
    COLLIDER_ORIENTED_RECTANGLE,
    COLLIDER_COMPLEX
};

class Collider : public Component
{
protected: // PROTECTED VARIABLE(s)

    // BASE VARIABLE(s)
    char* m_Tag;
    OKTransform2<float>* m_Transform;
    float m_Radius{};

    // COLLIDER VARIABLE(s)
    ColliderType m_ColliderType;
    std::vector<OKVector2<float>> m_Vertices;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)

    // RECTANGLE
    /// @brief Rectangle Collider Constructor
    Collider(const char* tag, OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true); // REFACT: bool solveRotation

    // CIRCLE
    /// @brief Circle Collider Constructor
    Collider(const char* tag, OKTransform2<float>* transform, float radius);

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
    inline const char* GetTag() { return m_Tag; }
    inline OKTransform2<float>* GetTransform() { return m_Transform; }
    inline OKVector2<float> GetPosition() { return m_Transform->position; }
    inline OKVector2<float> GetScale() { return m_Transform->scale; }
    inline float GetRotation() { return m_Transform->rotation; }

    inline ColliderType GetColliderType() const { return m_ColliderType; }

    inline float GetRadius() const { return m_Radius; }

    // SETTER FUNCTION(s)
    inline void SetTag(char* tag) { strcpy_s(m_Tag, strlen(tag), tag); }
    inline void SetTransform(OKTransform2<float>* transform) { m_Transform = transform; }

    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }


    // POLYGONE FUNCTION(s)
    float PolygonArea();

};

// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

#endif