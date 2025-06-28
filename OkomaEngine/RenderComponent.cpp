#include "RenderComponent.h"
#include "GameObjectEntity.h"

RenderComponent::RenderComponent()
{
	

}

RenderComponent::~RenderComponent()
{
	UnloadTexture(m_Image);
}

void RenderComponent::Construct(const char* imageName)
{
	m_Image = LoadTexture(imageName);
}

void RenderComponent::Construct(const char* imageName, int width, int height)
{
	m_Image = LoadTexture(imageName);
	m_Width = width;
	m_Height = height;
	
}

void RenderComponent::Update(const float deltaTime)
{


}

void RenderComponent::Draw()
{
	Rectangle dest = Rectangle{m_Owner->m_Transform.position.x + m_Offset.x, m_Owner->m_Transform.position.y + m_Offset.y, m_Width, m_Height};
	Rectangle source = Rectangle{0, 0, (float)m_Image.width, (float)m_Image.height * -1};
	DrawTexturePro(m_Image, source, dest, Vector2{ m_Width / 2.f, m_Height / 2.f}, m_Owner->m_Transform.rotation, WHITE);
}
