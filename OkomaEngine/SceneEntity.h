#ifndef SCENE_H
#define SCENE_H

#include "HeaderManager.h"
#include "GameObjectManager.h"

#include <iostream>
#include <string>

class SceneManager;

// TODO: Add a Game Object Manager - Has the different managers in it 

class SceneEntity
{
public:

	SceneManager* m_Owner = nullptr;

protected: // PROTECTED VARIABLE(s)

	std::string m_Name;
	Camera2D* m_Camera;
	GameObjectManager m_GameObjectManager;

public:

	// CLASS FUNCTION(s)
	SceneEntity()
	{
		m_Name = " ";
		m_Camera = new Camera2D();
		m_Camera->offset = Vector2{ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
		m_Camera->zoom = 1.f;
	}

	virtual ~SceneEntity() 
	{ 
		m_Owner = nullptr; 
		m_GameObjectManager.Destroy();
		delete m_Camera;
	}

	// BASE FUNCTION(s)
	virtual void Update(float deltaTime) { m_GameObjectManager.Process(deltaTime); }
	virtual void Draw() { m_GameObjectManager.Showcase(); }

	// GETTER FUNCTION(s)
	inline std::string GetName() const { return m_Name; }
	inline Camera2D* GetCamera() 
	{ 
		if (m_GameObjectManager.GetCurrentCamera() == nullptr) { return m_Camera; }
		return m_GameObjectManager.GetCurrentCamera();
	}

	// SETTER FUNCTION(s)
	inline void SpawnObject(GameObjectEntity prefab) { m_GameObjectManager.AddGameObject(prefab); }
	inline void AddObject(GameObjectEntity object) { m_GameObjectManager.AddGameObject(object); }
	inline void RemoveObject(GameObjectEntity* object) { m_GameObjectManager.RemoveGameObject(object); }
};

#endif
