#include "SceneManager.h"
#include "TestScene.h"
#include <array>

SceneManager::SceneManager()
{
	// NOTE: Settup up Scene Manager
	// m_Scenes[0] = MakeScene<TestScene>();
	m_Scenes[0] = MakeScene<TestScene>();

	NewScene<TestScene>();
}

SceneManager::~SceneManager()
{
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

		// NOTE: 
		delete m_CurrentScene;
		m_CurrentScene = m_Scenes[0]();
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
