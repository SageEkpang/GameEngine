#include "GameObject.h"

GameObject::GameObject(std::string tag) 
{
    this->m_Tag = tag;
    this->m_Transform = nullptr; 
}

GameObject::~GameObject() 
{
    // CLEAR COMPONENTS
    if (!m_Components.empty())
    {
        std::vector<Component*>::iterator itr;
        for (itr = m_Components.begin(); itr != m_Components.end(); ++itr)
        {
            *itr = nullptr;
            delete* itr;
        }

        m_Components.clear();
    }
}

void GameObject::Update(float deltaTime) 
{
    // UPDATE CURRENT COMPONENT(s)
    for (int i = 0; i < m_Components.size(); ++i)
    {
        // If Component has a parent, multiply parent position, scale and rotation
        if (m_Components[i]->GetTransform()->GetParent() != nullptr)
        {
            // Position
            m_Components[i]->GetTransform()->SetPosition(Vector2Multiply(this->m_Components[i]->GetTransform()->GetPosition(), this->m_Components[i]->GetTransform()->GetParent()->GetPosition()));

            // Scale
            m_Components[i]->GetTransform()->SetScale(Vector2Multiply(this->m_Components[i]->GetTransform()->GetScale(), this->m_Components[i]->GetTransform()->GetParent()->GetScale()));

            // Rotation
            m_Components[i]->GetTransform()->SetRotation(this->m_Components[i]->GetTransform()->GetRotation() * this->m_Components[i]->GetTransform()->GetParent()->GetRotation());
        }
   
        // Update Components
        m_Components[i]->Update(deltaTime);
    }
}

void GameObject::Draw() 
{
    // DRAW CURRENT COMPONENT(s)
    for (int i = 0; i < m_Components.size(); ++i)
    {
        m_Components[i]->Draw();
    }
}
