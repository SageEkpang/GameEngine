#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"
#include "GameObjectEntity.h"
#include "OKMaths.h"
#include "DebugDraw.h"

#include "PhysicsManager.h"
#include "OKTime.h"

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


	rlDisableBackfaceCulling();

	PhysicsManager m_PhyMana;

	// Tester Rectangle
	//GameObjectEntity RectangleObject;
	//RectangleObject.m_Transform.position = OKVector2<float>(100, 0);
	//RectangleObject.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	//RectangleObject.AddComponent<RectangleColliderComponent>()->Construct(50.f, 50.f);
	//m_PhyMana.AddPhysicsObject(&RectangleObject);

	// Tester Circle
	//GameObjectEntity CircleObject;
	//CircleObject.m_Transform.position = OKVector2<float>(0, 1);
	//CircleObject.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	//CircleObject.AddComponent<CircleColliderComponent>()->Construct(50.f);
	//m_PhyMana.AddPhysicsObject(&CircleObject);

	// Tester Circle 2
	GameObjectEntity CircleObjectTwo;
	CircleObjectTwo.m_Transform.position = OKVector2<float>(20, 200);
	CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	CircleObjectTwo.AddComponent<CapsuleColliderComponent>()->Construct(40.0f, 80.0f);
	m_PhyMana.AddPhysicsObject(&CircleObjectTwo);


	// Floor Rectangle
	GameObjectEntity m_Floor;
	m_Floor.m_Transform.position = OKVector2<float>(0.f, -200.f);
	m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
	m_Floor.AddComponent<CapsuleColliderComponent>()->Construct(50.f, 100.f);
	m_PhyMana.AddPhysicsObject(&m_Floor);

	// NOTE: Plinko


	// NOTE: Time Init
	#pragma region Time SetUp

	float t_StartTime = 0.0f;
	t_StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() / 1000000.f;
	OKTime::m_TimeScale = FPS_15;

	#pragma endregion

	while (!WindowShouldClose())
	{
		// UPDATE

		auto startTime = std::chrono::high_resolution_clock::now();


		// DRAW
		BeginDrawing();
			ClearBackground(BLACK);

			camera.offset = Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
			camera.zoom = 1.0f;

			BeginMode2D(camera);


			rlPushMatrix();
			rlScalef(1.0f, 1.0f, 1.0f);
			// NOTE: Text Here -------

			// DrawText(TextFormat("Position: %f", m_Object2.m_Transform.position.y), 0, 0, 40, GREEN);




			rlPopMatrix();







			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);
			// NOTE: Draw Here --------


			m_PhyMana.Update(OKTime::m_DeltaTime);
			m_PhyMana.Draw();

			auto endTime = std::chrono::high_resolution_clock::now();
			auto start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
			auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

			OKTime::m_UnscaledDeltaTime = (float)(end - start) / 1000.f;
			OKTime::m_DeltaTime = OKTime::m_UnscaledDeltaTime * OKTime::m_TimeScale;

			OKTime::m_RealTimeSinceStartUp = end / 1000000.f - t_StartTime;
			OKTime::m_Time = OKTime::m_RealTimeSinceStartUp * OKTime::m_TimeScale;
			OKTime::m_FrameCount++;

			rlPopMatrix();
			EndMode2D();

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}