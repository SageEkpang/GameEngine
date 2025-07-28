#include "RenderComponent.h"
#include "GameObjectEntity.h"
#include "RenderManager.h"

RenderComponent::RenderComponent()
{
	m_Width = 0.0f;
	m_Height = 0.0f;
}

RenderComponent::~RenderComponent()
{
	UnloadTexture(m_Image);
}

void RenderComponent::Construct()
{
	m_Image = RenderManager::m_SavedTextures["Blank"];
}

void RenderComponent::Construct(int width, int height)
{
	m_Image = RenderManager::m_SavedTextures["Blank"];
	m_Width = float(width);
	m_Height = float(height);
}

void RenderComponent::Construct(const char* imageName)
{
	// NOTE: Check if the texture already exists in the render manager,
	// NOTE: If it is in there, use that, if not, load the texture and store it

	// NOTE: Assume the File Path beginning
	std::string t_FileToLoad = "Resources/Images/";
	std::string t_ImageName = imageName;

	// NOTE: Combine the Strings together to make where the file is and what to load
	t_FileToLoad.append(t_ImageName);

	if (RenderManager::m_SavedTextures.find(t_ImageName) == RenderManager::m_SavedTextures.end())
	{
		// NOTE: Load the file and the file type into the map
		RenderManager::m_SavedTextures[t_ImageName] = LoadTexture((t_FileToLoad + ".png").c_str());

		// NOTE: Check if the actual texture exists
		if (!IsTextureValid(RenderManager::m_SavedTextures[t_ImageName]))
		{
			// NOTE: Unload the temp texture
			UnloadTexture(RenderManager::m_SavedTextures[t_ImageName]);

			// NOTE: If loaded in texture is not real, remove from map
			RenderManager::m_SavedTextures.erase(t_ImageName);

			// NOTE: If there is no texture, then use Blank by default
			m_Image = RenderManager::m_SavedTextures["Blank"];
			return;
		}

		// NOTE: If the texture is valid, load in the texture
		m_Image = RenderManager::m_SavedTextures[t_ImageName];
	}
	else
	{
		m_Image = RenderManager::m_SavedTextures[t_ImageName];
	}
}

void RenderComponent::Construct(const char* imageName, int width, int height)
{
	// NOTE: Check if the texture already exists in the render manager,
	// NOTE: If it is in there, use that, if not, load the texture and store it

	// NOTE: Assume the File Path beginning
	std::string t_FileToLoad = "Resources/Images/";
	std::string t_ImageName = imageName;

	// NOTE: Combine the Strings together to make where the file is and what to load
	t_FileToLoad.append(t_ImageName);

	if (RenderManager::m_SavedTextures.find(t_ImageName) == RenderManager::m_SavedTextures.end())
	{
		// NOTE: Load the file and the file type into the map
		RenderManager::m_SavedTextures[t_ImageName] = LoadTexture((t_FileToLoad + ".png").c_str());

		// NOTE: Check if the actual texture exists
		if (!IsTextureValid(RenderManager::m_SavedTextures[t_ImageName]))
		{
			// NOTE: Unload the temp texture
			UnloadTexture(RenderManager::m_SavedTextures[t_ImageName]);

			// NOTE: If loaded in texture is not real, remove from map
			RenderManager::m_SavedTextures.erase(t_ImageName);

			// NOTE: If there is no texture, then use Blank by default
			m_Image = RenderManager::m_SavedTextures["Blank"];
			m_Width = float(width);
			m_Height = float(height);

			return;
		}

		// NOTE: If the texture is valid, load in the texture
		m_Image = RenderManager::m_SavedTextures[t_ImageName];
	}
	else
	{
		m_Image = RenderManager::m_SavedTextures[t_ImageName];
	}

	m_Width = float(width);
	m_Height = float(height);
}

void RenderComponent::Update(const float deltaTime)
{


}

void RenderComponent::Draw()
{
	Rectangle dest = Rectangle{m_Owner->m_Transform.position.x + m_Offset.x, m_Owner->m_Transform.position.y + m_Offset.y, m_Width, m_Height};
	Rectangle source = Rectangle{0, 0, (float)m_Image.width, (float)m_Image.height * -1};
	DrawTexturePro(m_Image, source, dest, Vector2{ m_Width / 2.f, m_Height / 2.f }, m_Owner->m_Transform.rotation, Color(m_ColourTint.x, m_ColourTint.y, m_ColourTint.z, m_ColourTint.w));
}
