#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SceneEntity.h"
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

enum class SceneID : std::int8_t
{
	SCENE_ID_TEST = 0,
	SCENE_ID_MAIN,



	SCENE_ID_COUNT
};

// NOTE: Forward Declarations
class TestScene;

class SceneManager
{
private: // PRIVATE VARIABLE(s)
	
	SceneEntity* m_CurrentScene = nullptr;

	// NOTE: TRANSITION VARIABLE(s)
	bool m_Transition = false;
	float m_TransitionTimer = 0.f;
	float m_TransitionLength = 0.f;

public: // PUBLIC VARIABLE(s)

	// CLASS FUNCTION(s)
	SceneManager();
	~SceneManager();


	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime);
	virtual void Draw();

	template<std::derived_from<SceneEntity> T>
	void NewScene();

	template<std::derived_from<SceneEntity> T>
	void ChangeScene(bool transition);

	// GETTER FUNCTION(s)

	// SETTER FUNCTION(s)
};

template<std::derived_from<SceneEntity> T>
inline void SceneManager::NewScene()
{
	delete m_CurrentScene;
	m_CurrentScene = new T();
	m_CurrentScene->m_Owner = this;
}

template<std::derived_from<SceneEntity> T>
inline void SceneManager::ChangeScene(bool transition)
{
	delete m_CurrentScene;
	m_CurrentScene = new T();
	m_CurrentScene->m_Owner = this;
}


#endif // !SCENE_MANAGER_H

