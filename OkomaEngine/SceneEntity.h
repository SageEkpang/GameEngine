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
	Camera2D m_Camera;
	GameObjectManager m_GameObjectManager;

public:

	// CLASS FUNCTION(s)
	SceneEntity()
	{
		m_Name = " ";
		m_Camera = { 0 };
		m_Camera.offset = Vector2{ GetScreenWidth() / 2.f, GetScreenHeight() / 2.f };
		m_Camera.zoom = 1.f;
	}

	virtual ~SceneEntity() 
	{ 
		m_Owner = nullptr; 
		m_GameObjectManager.Destroy();
	}

	// BASE FUNCTION(s)
	virtual void Update(float deltaTime) { m_GameObjectManager.Process(deltaTime); }
	virtual void Draw() { m_GameObjectManager.Showcase(); }

	// GETTER FUNCTION(s)
	inline std::string GetName() const { return m_Name; }
	inline Camera2D GetCamera() const { return m_Camera; }

	// SETTER FUNCTION(s)
	inline void SetName(std::string name) { m_Name = name; }
	inline void SetCamera(Camera2D camera) { m_Camera = camera; }

	inline void SpawnObject(GameObjectEntity* object) { m_GameObjectManager.AddGameObject(object); }
	inline void AddObject(GameObjectEntity* object) { m_GameObjectManager.AddGameObject(object); }
	inline void RemoveObject(GameObjectEntity* object) { m_GameObjectManager.RemoveGameObject(object); }
};

#endif
