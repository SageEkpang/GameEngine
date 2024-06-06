#include "PhysicsComponent.h"
#include "CollisionComponent.h"

PhysicsComponent::PhysicsComponent(CollisionComponent* collisionComponent) 
{
    m_CollisionComponent = new CollisionComponent();
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
    
}
