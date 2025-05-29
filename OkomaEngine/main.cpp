#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "GameObjectEntity.h"
#include "OKMaths.h"
#include "DebugDraw.h"

#include "CollisionManager.h"

#include <iostream>

int main()
{
	// NOTE: Check the window has actually been inited

	#pragma region Window SetUp

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

	#pragma endregion

	#pragma region Audio SetUp

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

	#pragma endregion

	Camera2D camera = { 0 };

	// Move the origin to the center of the screen
	camera.offset = Vector2{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;

	rlDisableBackfaceCulling();

	GameObjectEntity m_Tester;
	m_Tester.m_Transform.position = OKVector2<float>(0, 0);
	m_Tester.AddComponent<LineColliderComponent>();
	m_Tester.GetComponent<LineColliderComponent>()->Construct(OKVector2<float>(500, 0), OKVector2<float>(-500, 100));

	GameObjectEntity m_Object2;
	m_Object2.m_Transform.position = OKVector2<float>(0, 0);
	m_Object2.AddComponent<CircleColliderComponent>();
	m_Object2.GetComponent<CircleColliderComponent>()->Construct(10.f);

	CollisionManager m_ColMani;
	CollisionManifold m_Result;
	
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
			m_Result = m_ColMani.CheckCollisions(&m_Tester, &m_Object2);

			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				m_Object2.m_Transform.position = OKVector2<float>(GetMouseX() - camera.offset.x, GetMouseY() - camera.offset.y);
			}

			if (m_Result.m_HasCollision)
			{
				DrawText("Collided", 10, 100, 40, GREEN);
			}
			else
			{
				DrawText("Not Collided", 10, 100, 40, RED);
			}

			DebugDraw::Shape::DebugLines(&m_Tester);
			DebugDraw::Shape::DebugCircle(&m_Object2);
			

			rlPopMatrix();


			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);
			// NOTE: Draw Here ------



			// m_Tester.GetComponent<ParticleEffectComponent>()->Update(GetFrameTime());
			// m_Tester.GetComponent<ParticleEffectComponent>()->Draw();

			// DrawCircle(0, 0, 3, GREEN);
		
			rlPopMatrix();

			EndMode2D();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}