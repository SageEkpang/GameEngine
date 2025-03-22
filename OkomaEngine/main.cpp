#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"

#include "PhysicsObject.h"
#include "TriggerArea.h"
#include "ColliderManager.h"
#include "CollisionResolution.h"

int main()
{
	// Game Utility (namespace) over Game Manager (class)
	InitWindow(1000, 800, "OkomaEngine");
	InitAudioDevice();

	
	Timer* timer = new Timer();
	float m_Accumulator = 0;
	float m_SimpleCounter = 0;

	std::vector<PhysicsObject*> m_PhysicsObjects;

	OKTransform2<float>* TransformFirst = new OKTransform2<float>(OKVector2<float>(100, 200), OKVector2<float>(100, 100), 0); // 30, 60
	PhysicsObject* m_PhysicsFirst = new PhysicsObject("Phy1", TransformFirst, 10, RIGIDBODY_DYNAMIC, false, false);
	m_PhysicsObjects.push_back(m_PhysicsFirst);

	//OKTransform2<float>* TriggerTransformFirst = new OKTransform2<float>(OKVector2<float>(100, 200), OKVector2<float>(0, 0), OKVector2<float>(30, 60)); // 30, 60
	//TriggerArea* m_TriggerAreaFirst = new TriggerArea("Trigger First", TriggerTransformFirst);
	//m_TriggerAreas.push_back(m_TriggerAreaFirst);

	OKTransform2<float>* TransformSecond = new OKTransform2<float>(OKVector2<float>(80, 400), OKVector2<float>(80, 50), 45); // 100, 40
	PhysicsObject* m_PhysicsSecond = new PhysicsObject("Phy2", TransformSecond, 0, RIGIDBODY_STATIC, false, false);
	m_PhysicsObjects.push_back(m_PhysicsSecond);

	//OKTransform2<float>* TransformThird = new OKTransform2<float>(OKVector2<float>(300, 400), OKVector2<float>(300, 40), 0); // 300, 40
	//PhysicsObject* m_PhysicsThird = new PhysicsObject("Phy3", TransformThird, 0, RIGIDBODY_STATIC);
	//m_PhysicsObjects.push_back(m_PhysicsThird);

	//OKTransform2<float>* TransformFour = new OKTransform2<float>(OKVector2<float>(0, 700), OKVector2<float>(1000, 40), 0); // 300, 40
	//PhysicsObject* m_PhysicsFour = new PhysicsObject("Phy3", TransformFour, 0, RIGIDBODY_STATIC);
	//m_PhysicsObjects.push_back(m_PhysicsFour);

	ColliderManager* t_ColliderManager = new ColliderManager();
	CollisionManifold t_ColMani = CollisionManifold();
	CollisionResolution* t_CollisionResolution = new CollisionResolution();


	Vector2 LineStart = Vector2{100, 300};
	Vector2 LineEnd = Vector2{200, 300};

	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
		ClearBackground(RAYWHITE);

		m_Accumulator += timer->GetDeltaTime();
		m_SimpleCounter += timer->GetDeltaTime();

		if (IsKeyDown(KEY_A))
		{
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(-200 * timer->GetDeltaTime(), 0);
		}

		if (IsKeyDown(KEY_D))
		{
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(200 * timer->GetDeltaTime(), 0);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(0, -1000);
			
		}

		for (int i = 0; i < m_PhysicsObjects.size(); ++i)
		{
			for (int j = 0; j < m_PhysicsObjects.size(); ++j)
			{
				if (i == j) { continue; }

				t_ColMani = t_ColliderManager->CheckCollisions(m_PhysicsObjects[i]->GetCollider(), m_PhysicsObjects[j]->GetCollider());
				// DrawText(TextFormat("col: %d", t_ColMani.m_HasCollision), 10, 10, 40, PINK);
				
				if (t_ColMani.m_HasCollision == true)
				{
					// NOTE: Coef is Bounce Level to the collision detection
					t_CollisionResolution->ResolveCollision(m_PhysicsObjects[i]->GetRigidbody(), m_PhysicsObjects[j]->GetRigidbody(), 0.3f, t_ColMani.m_PenetrationDepth, t_ColMani.m_CollisionNormal, GetFrameTime());
				}
			}
		}

		for (auto& v : m_PhysicsObjects)
		{
			v->Update(GetFrameTime());
		}

		for (auto& v : m_PhysicsObjects)
		{
			v->Draw();
		}

		//if (m_Accumulator >= FPS_60)
		//{
		//	m_Accumulator -= FPS_60;
		//}

		timer->Tick();

		EndDrawing();
	}
	
	CloseAudioDevice();
	CloseWindow();

	return 0;
}