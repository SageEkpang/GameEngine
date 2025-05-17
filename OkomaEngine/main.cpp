#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "GameObjectEntity.h"

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
	m_Tester.GetComponent(0, 0);
	// m_Tester.GetComponent<RectangleColliderComponent>();






	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
			ClearBackground(BLACK);

			BeginMode2D(camera);

			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);

			// NOTE: Draw Here ------


			DrawCircle(0, 0, 3, GREEN);



		
			rlPopMatrix();
			EndMode2D();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}