#include "SceneManager.h"
#include "TestScene.h"
#include <array>

SceneManager::SceneManager()
{
	// NOTE: Settup up Scene Manager
	NewScene<TestScene>();
}

SceneManager::~SceneManager()
{
	// NOTE: Properly clear the whole list of scenes
	delete m_CurrentScene;
}

void SceneManager::Update(const float deltaTime)
{













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
