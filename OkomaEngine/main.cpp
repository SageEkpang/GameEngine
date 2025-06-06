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
	m_Floor.GetComponent<ParticleEffectComponent>()->PrefabFire();
	// m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(10.f, RigidbodyMovementType::RIGIDBODY_MOVEMENT_TYPE_STATIC);
	// m_PhyMana.AddPhysicsObject(&m_Floor);

	// Rectangle Object
	//GameObjectEntity m_Object2;
	//m_Object2.m_Transform.position = OKVector2<float>(10, 10);
	//m_Object2.AddComponent<CapsuleColliderComponent>()->Construct(OKVector2<float>(50.f, 100.f));
	//m_Object2.AddComponent<Rigidbody2DComponent>()->Construct(30.f);
	//m_PhyMana.AddPhysicsObject(&m_Object2);
	

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




			m_Floor.GetComponent<ParticleEffectComponent>()->Update(GetFrameTime());
			m_Floor.GetComponent<ParticleEffectComponent>()->Draw();


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