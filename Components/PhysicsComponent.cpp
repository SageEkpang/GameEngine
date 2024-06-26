#include "PhysicsComponent.h"
#include "CollisionComponent.h"

PhysicsComponent::PhysicsComponent() 
{
    
}

PhysicsComponent::PhysicsComponent(CollisionComponent* collisionComponent) 
{
    m_CollisionComponent = collisionComponent;
}

PhysicsComponent::~PhysicsComponent() 
{
    if (m_CollisionComponent != nullptr)
    {
        m_CollisionComponent = nullptr;
        delete m_CollisionComponent;
    }
}

void PhysicsComponent::Update(float deltaTime) 
{
    if (m_CollisionComponent == nullptr) // Particles
    {
        // Do Physics for Collision
    }
    else 
    {
        // Do physics without collision
    }




}

