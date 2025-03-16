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
    bool m_IsCollidable = false;
    bool m_IsTrigger = false;
    bool m_AbsoluteEnter = false; // NOTE: This would be for the trigger box, potentially its own child class

    // typedef std::pair<ColliderType, ColliderType> Col2;
    // typedef CollisionManifold (*CollFunc)(Collider*, Collider*, CollisionManifold&);
    // std::unordered_map<ColliderType, CollFunc> m_MapColliderFunction;

    // TO THINK: This is either going to be for a GJK and EPA algo because of how points are constructed
    // I do not know how like 2D collisions work like this but hey ho

    std::vector<OKVector2<float>> m_Vertices;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)

    // RECTANGLE
    /// @brief Rectangle Collider Constructor
    Collider(const char* tag, OKTransform2<float>* transform, bool IsCapsule = false, bool lockZRot = true);

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

    void TriggerEntered();
    void TriggerState();
    void TriggerExit();

    // GETTER FUNCTION(s)
    inline const char* GetTag() { return m_Tag; }
    inline OKTransform2<float>* GetTransform() { return m_Transform; }
    inline OKVector2<float> GetPosition() { return m_Transform->position; }
    inline OKVector2<float> GetScale() { return m_Transform->scale; }
    inline OKVector2<float> GetRotation() { return m_Transform->rotation; }

    inline ColliderType GetColliderType() const { return m_ColliderType; }
    inline bool GetIsCollidable() const { return m_IsCollidable; }
    inline bool GetIsTrigger() const { return m_IsTrigger; } // TODO Change this to something else

    inline float GetRadius() const { return m_Radius; }

    // SETTER FUNCTION(s)
    inline void SetTag(char* tag) { strcpy_s(m_Tag, strlen(tag), tag); }
    inline void SetTransform(OKTransform2<float>* transform) { m_Transform = transform; }

    inline void SetColliderType(ColliderType colliderType) { m_ColliderType = colliderType; }
    inline void SetIsCollidable(bool isCollidable) { m_IsCollidable = isCollidable; }
    inline void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }


    // POLYGONE FUNCTION(s)
    float PolygonArea();

};

// https://www.geeksforgeeks.org/area-of-a-polygon-with-given-n-ordered-vertices/

#endif