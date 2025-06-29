#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "GameObjectEntity.h"
#include <unordered_map>

class RenderManager
{
private:

	std::vector<GameObjectEntity*> m_RenderObjects;

public:

	typedef std::map<std::string, Texture2D> SavedTextureMap;
	static SavedTextureMap m_SavedTextures;

	// CLASS FUNCTION(s)
	RenderManager();
	~RenderManager();

	// BASE FUNCTION(s)
	void Update(const float deltaTime);
	void Draw();

	// HELPER FUNCTION(s)
	inline void AddRenderObject(GameObjectEntity* gameObject) { m_RenderObjects.push_back(gameObject); };

};

#endif