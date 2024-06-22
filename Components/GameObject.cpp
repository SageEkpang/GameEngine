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
        if (m_Components[i]->GetTransform()->parent != nullptr)
        {
            // Position
            m_Components[i]->GetTransform()->position = this->m_Components[i]->GetTransform()->position * this->m_Components[i]->GetTransform()->parent->position;

            // Scale
            m_Components[i]->GetTransform()->scale = this->m_Components[i]->GetTransform()->scale, this->m_Components[i]->GetTransform()->parent->scale;

            // Rotation
            m_Components[i]->GetTransform()->rotation = this->m_Components[i]->GetTransform()->rotation * this->m_Components[i]->GetTransform()->parent->rotation;
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

template<typename T>
T GameObject::GetComponent() 
{
    return T;
}

