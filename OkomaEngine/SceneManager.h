#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SceneEntity.h"
#include <unordered_map>
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
class DefaultScene;

class SceneManager
{
private: // PRIVATE VARIABLE(s)
	
	SceneEntity* m_CurrentScene = nullptr;
	
	// NOTE: TRANSITION VARIABLE(s)
	bool m_Transitioning = false;
	float m_TransitionTimer = 0.f;
	float m_TransitionLength = 0.f;
	std::string m_TransitionName;
	
public: // PUBLIC VARIABLE(s)

	// CLASS FUNCTION(s)
	SceneManager();
	~SceneManager();


	// BASE FUNCTION(s)
	virtual void Update(const float deltaTime);
	virtual void Draw();

	void NewScene(std::string sceneName);
	void ChangeScene(std::string sceneName, float transitionLength = 0.0f);
	void ResetScene();

	// GETTER FUNCTION(s)

	// SETTER FUNCTION(s)
};


#endif // !SCENE_MANAGER_H


