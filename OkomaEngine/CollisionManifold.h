#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "OKVector2.h"

class GameObjectEntity;

class CollisionManifold
{
public: // PUBLIC VARIABLE(s)

    int m_ContactPointAmount;
    float m_PenetrationDepth;
    bool m_HasCollision;
    OKVector2<float> m_CollisionPoints[4];
    OKVector2<float> m_CollisionNormal;

    // NOTE: Hit Result Information (Used Primarily for Line Trace)
    bool m_BlockingHit;
    float m_Distance;

    OKVector2<float> m_ImpactPoint;
    OKVector2<float> m_ImpactNormal;

    OKVector2<float> m_TraceStart;
    OKVector2<float> m_TraceEnd;

    GameObjectEntity* m_OwningObject;
    GameObjectEntity* m_HitObject;

public: // PUBLIC FUNCTION(s)

    // CLASS FUNCTION(s)
    CollisionManifold()
    {
        m_ContactPointAmount = 0;
        m_PenetrationDepth = 0.0f;
        m_HasCollision = false;
        m_CollisionNormal = OKVector2<float>(0, 0);

        m_CollisionPoints[0] = OKVector2<float>(0, 0);
        m_CollisionPoints[1] = OKVector2<float>(0, 0);
        m_CollisionPoints[2] = OKVector2<float>(0, 0);
        m_CollisionPoints[3] = OKVector2<float>(0, 0);

        m_BlockingHit = false;
        m_Distance = 0.f;

        m_ImpactPoint = OKVector2<float>(0.f, 0.f);
        m_ImpactNormal = OKVector2<float>(0.f, 0.f);

        m_TraceStart = OKVector2<float>(0.f, 0.f);
        m_TraceEnd = OKVector2<float>(0.f, 0.f);

        m_OwningObject = nullptr;
        m_HitObject = nullptr;
    }

    // ~CollisionManifold() { }
};

#endif