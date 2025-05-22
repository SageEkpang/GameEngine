#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "GameObjectEntity.h"
#include "OKMaths.h"

#include "ParticleEffectComponent.h"
#include "RectangleColliderComponent.h"

#include <iostream>

int main()
{
	// NOTE: Check the window has actually been inited
	try
	{
		InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE_NAME);
		SetWindowState(FLAG_WINDOW_RESIZABLE);
		if (!IsWindowReady()) { throw; }
	}
	catch (const std::bad_exception& e)
	{
		std::cerr << "Window Bad Exception: " << e.what() << std::endl;
	}

	// NOTE: Check the Audio has actually been inited
	try
	{
		InitAudioDevice();
		if (!IsAudioDeviceReady()) { throw; }
	}
	catch (const std::bad_exception& e)
	{
		std::cerr << "Audio Bad Exception: " << e.what() << std::endl;
	}

	Camera2D camera = { 0 };

	// Move the origin to the center of the screen
	camera.offset = Vector2{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;

	rlDisableBackfaceCulling();


	GameObjectEntity m_Tester;
	m_Tester.AddComponent<ParticleEffectComponent>();
	m_Tester.GetComponent<ParticleEffectComponent>()->Construct(OKVector2<float>(0, 0), 1000u);
	m_Tester.GetComponent<ParticleEffectComponent>()->PrefabWaterFall();
	
	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
			ClearBackground(BLACK);

			BeginMode2D(camera);

			rlPushMatrix();
			rlScalef(1.0f, 1.0f, 1.0f);
			
			// NOTE: Text Here ------

			rlPopMatrix();


			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);
			
			// NOTE: Draw Here ------
			m_Tester.GetComponent<ParticleEffectComponent>()->Update(GetFrameTime());
			m_Tester.GetComponent<ParticleEffectComponent>()->Draw();

			// m_Tester





			DrawCircle(0, 0, 3, GREEN);
		
			rlPopMatrix();

			EndMode2D();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}