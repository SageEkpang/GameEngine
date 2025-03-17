#ifndef COLLISION_MANIFOLD_H
#define COLLISION_MANIFOLD_H

#include "OKVector2.h"

class CollisionManifold
{
public: // PUBLIC VARIABLE(s)

    int m_ContactPointAmount;
    float m_PenetrationDepth;
    bool m_HasCollision;
    OKVector2<float> m_CollisionPoints[4];
    OKVector2<float> m_CollisionNormal;

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
    }

    // ~CollisionManifold() { }
};

#endif