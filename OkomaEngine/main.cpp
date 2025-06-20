#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "GameObjectEntity.h"
#include "OKMaths.h"
#include "DebugDraw.h"

#include "PhysicsManager.h"

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

	// Move the origin to the center of the screen
	Camera2D camera = { 0 };
	camera.offset = Vector2{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;

	rlDisableBackfaceCulling();

	PhysicsManager m_PhyMana;

	// Oriented Rectangle
	GameObjectEntity m_Floor;
	m_Floor.m_Transform.position = OKVector2<float>(0, 0);

	m_Floor.AddComponent<ParticleEffectComponent>()->Construct(1000u);
	m_Floor.GetComponent<ParticleEffectComponent>()->PrefabSmoke();

	m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(10);
	m_Floor.GetComponent<Rigidbody2DComponent>()->m_Gravity = OKVector2<float>(0, 100);

	m_Floor.AddComponent<CircleColliderComponent>()->Construct(100.f);
	m_PhyMana.AddPhysicsObject(&m_Floor);


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
			// NOTE: Text Here -------

			// DrawText(TextFormat("Position: %f", m_Object2.m_Transform.position.y), 0, 0, 40, GREEN);




			rlPopMatrix();







			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);
			// NOTE: Draw Here --------



			m_Floor.Update(GetFrameTime());
			m_Floor.Draw();

			// m_Floor.GetComponent<ParticleEffectComponent>()->Update(GetFrameTime());
			// m_Floor.GetComponent<ParticleEffectComponent>()->Draw();


			// m_PhyMana.Update(GetFrameTime());
			// m_PhyMana.Draw();

			DrawCircle(0, 0, 3, RED);
		



			rlPopMatrix();
			EndMode2D();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}