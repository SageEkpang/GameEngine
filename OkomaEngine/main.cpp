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

	Camera2D camera = { 0 };

	// Move the origin to the center of the screen
	camera.offset = Vector2{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;

	rlDisableBackfaceCulling();

	PhysicsManager m_PhyMana;

	// Oriented Rectangle
	GameObjectEntity m_Tester;
	m_Tester.m_Transform.position = OKVector2<float>(0, -100);

	m_Tester.AddComponent<RectangleColliderComponent>()->Construct(OKVector2<float>(500, 100));
	m_Tester.AddComponent<Rigidbody2DComponent>()->Construct(10.f, RigidbodyMovementType::RIGIDBODY_MOVEMENT_TYPE_STATIC);

	m_PhyMana.AddPhysicsObject(&m_Tester);
	
	// Rectangle Object
	GameObjectEntity m_Object2;
	m_Object2.m_Transform.position = OKVector2<float>(100, 100);

	int thing = 10;

	m_Object2.AddComponent<RectangleColliderComponent>()->Construct(OKVector2<float>(50, 50));
	m_Object2.AddComponent<Rigidbody2DComponent>()->Construct(10.f);

	m_Object2.AddComponent<InputComponent>()->AddInputMapping(KEY_SPACE, InputType::INPUT_TYPE_KEY_PRESSED,
	[&m_Object2] {

			m_Object2.GetComponent<Rigidbody2DComponent>()->ApplyImpulseY(100);
	});

	m_PhyMana.AddPhysicsObject(&m_Object2);
	
	// Circle Collider Object
	//GameObjectEntity m_Object3;
	//m_Object3.m_Transform.position = OKVector2<float>(500, 100);
	//m_Object3.AddComponent<CircleColliderComponent>()->Construct(10);
	//m_PhyMana.AddPhysicsObject(&m_Object3);
	

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


			rlPopMatrix();






			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);
			// NOTE: Draw Here --------


			m_PhyMana.Update(GetFrameTime());
			m_PhyMana.Draw();

			DrawCircle(0, 0, 3, RED);
		

			rlPopMatrix();






			EndMode2D();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();

	return 0;
}