#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SceneEntity.h"
#include <array>
#include <functional>
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

typedef SceneEntity* SceneMaker();

class SceneManager
{
private: // PRIVATE VARIABLE(s)
	
	SceneEntity* m_CurrentScene = nullptr;
	std::array<SceneMaker*, 10> m_Scenes;

	// NOTE: TRANSITION VARIABLE(s)
	bool m_Transitioning = false;
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
	void ChangeScene(float transitionLength = 0.0f);


	template <class T> 
	SceneEntity* MakeScene();

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
inline void SceneManager::ChangeScene(float transitionLength)
{
	if (m_Transitioning == false)
	{
		m_Transitioning = true;

		if (transitionLength >= 0)
		{
			m_TransitionTimer = transitionLength;
		}
		else
		{
			delete m_CurrentScene;
			m_CurrentScene = new T();
			m_CurrentScene->m_Owner = this;
			m_Transitioning = false;
		}
	}
}

template<class T>
inline SceneEntity* SceneManager::MakeScene()
{
	return new T;
}

#endif // !SCENE_MANAGER_H

