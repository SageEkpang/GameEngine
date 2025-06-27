#include "SceneManager.h"
#include "TestScene.h"
#include "DefaultScene.h"

// NOTE: This is to store the different class reference inside an array
// NOTE: This HAS TO be here or it will not work
typedef SceneEntity* SceneMaker();

template<class T>
inline SceneEntity* MakeScene()
{
	return new T;
}

std::unordered_map<std::string, SceneMaker*> m_Scenes;

SceneManager::SceneManager()
{
	// NOTE: Settup up Scene Manager
	m_Scenes["TestScene"] = MakeScene<TestScene>;
	m_Scenes["DefaultScene"] = MakeScene<DefaultScene>;

	// NOTE: Default Scene to Load
	m_CurrentScene = m_Scenes["TestScene"]();
	m_CurrentScene->m_Owner = this;
	m_Transitioning = false;
}

SceneManager::~SceneManager()
{
	// NOTE: Clear Scenes
	m_Scenes.clear();

	// NOTE: Properly clear the whole list of scenes
	delete m_CurrentScene;
}

void SceneManager::Update(const float deltaTime)
{
	// NOTE: Do the transition for the screen
	#pragma region Transition Timer Processing

	if (m_TransitionTimer > 0) 
	{ 
		m_TransitionTimer -= deltaTime; return; 
	}
	else if (m_TransitionTimer < 0)
	{ 
		// NOTE: Reset the Transition Time
		m_TransitionTimer = 0.f;

		// NOTE: Create the Scene from the list
		delete m_CurrentScene;
		m_CurrentScene = m_Scenes[m_TransitionName]();
		m_CurrentScene->m_Owner = this;
		m_Transitioning = false;
	}

	#pragma endregion

	// NOTE: Update the current screen
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Draw()
{
	// NOTE: Start the Drawing
	BeginDrawing();

		// NOTE: Draw A flat Colour for the background
		ClearBackground(BLACK); // SKYBLUE

		BeginMode2D(m_CurrentScene->GetCamera());

			// NOTE: Due to the y-axis being flipped, need to flip this back to pos-y up
			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);

			// NOTE: Draw the current scene from the list of scenes
			m_CurrentScene->Draw();

			// NOTE: Pop matrix out of que
			rlPopMatrix();

		// NOTE: End drawing mode and return to loop
		EndMode2D();

	EndDrawing();
}

void SceneManager::NewScene(std::string sceneName)
{
	try
	{
		if (m_Scenes.find(sceneName) == m_Scenes.end()) { throw; }

		delete m_CurrentScene;
		m_CurrentScene = m_Scenes[sceneName]();
		m_CurrentScene->m_Owner = this;
		m_Transitioning = false;
	}
	catch (...)
	{
		printf("The Scene you are trying to find does not exist");
	}
}

void SceneManager::ChangeScene(std::string sceneName, float transitionLength)
{
	m_TransitionName = sceneName;
	if (m_Transitioning == false)
	{
		m_Transitioning = true;

		if (transitionLength > 0)
		{
			m_TransitionTimer = transitionLength;
			m_TransitionName = sceneName;
		}
		else
		{
			try
			{
				if (m_Scenes.find(sceneName) == m_Scenes.end()) { throw; }

				delete m_CurrentScene;
				m_CurrentScene = m_Scenes[sceneName]();
				m_CurrentScene->m_Owner = this;
				m_Transitioning = false;
			}
			catch (...)
			{
				printf("The Scene you are trying to find does not exist");
			}
		}
	}
}

void SceneManager::ResetScene()
{
	try
	{
		std::string t_ScreenName = m_CurrentScene->GetName();
		if (m_Scenes.find(t_ScreenName) == m_Scenes.end()) { throw; }

		delete m_CurrentScene;
		m_CurrentScene = m_Scenes[t_ScreenName]();
		m_CurrentScene->m_Owner = this;
		m_Transitioning = false;
	}
	catch (...)
	{
		printf("The Scene you are trying to find does not exist");
	}
}
