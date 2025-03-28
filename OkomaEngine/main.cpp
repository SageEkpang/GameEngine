#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"

#include "PhysicsObject.h"
#include "TriggerArea.h"
#include "ColliderManager.h"
#include "CollisionResolution.h"

std::vector<PhysicsObject*> m_PhysicsObjects;

void SpawnAnotherPhysicsObject()
{

}

int main()
{
	// Game Utility (namespace) over Game Manager (class)
	InitWindow(1000, 800, "OkomaEngine");
	InitAudioDevice();

	
	Timer* timer = new Timer();
	float m_Accumulator = 0;
	float m_SimpleCounter = 0;


	{
		OKTransform2<float>* TransformFirst = new OKTransform2<float>(OKVector2<float>(100, 200), OKVector2<float>(40, 80), 0); // 30, 60
		PhysicsObject* m_PhysicsFirst = new PhysicsObject("Phy1", TransformFirst, 10, RIGIDBODY_DYNAMIC, true);
		m_PhysicsObjects.push_back(m_PhysicsFirst);
	}

	{
		OKTransform2<float>* TransformFirst = new OKTransform2<float>(OKVector2<float>(600, 200), OKVector2<float>(40, 80), 0); // 30, 60
		PhysicsObject* m_PhysicsFirst = new PhysicsObject("Phy1", TransformFirst, 10, 20, RIGIDBODY_DYNAMIC);
		m_PhysicsObjects.push_back(m_PhysicsFirst);

		OKTransform2<float>* AltFirst = new OKTransform2<float>(OKVector2<float>(650, 200), OKVector2<float>(40, 80), 0); // 30, 60
		PhysicsObject* m_AltObjFirst = new PhysicsObject("Phy1", AltFirst, 10, 20, RIGIDBODY_DYNAMIC);
		m_PhysicsObjects.push_back(m_AltObjFirst);
	}


	{
		OKTransform2<float>* TransformSecond = new OKTransform2<float>(OKVector2<float>(80, 400), OKVector2<float>(80, 50), 0); // 100, 40
		PhysicsObject* m_PhysicsSecond = new PhysicsObject("Phy2", TransformSecond, 0, RIGIDBODY_STATIC, false, false);
		m_PhysicsObjects.push_back(m_PhysicsSecond);
	}

	{
		OKTransform2<float>* TransformThird = new OKTransform2<float>(OKVector2<float>(300, 400), OKVector2<float>(300, 40), 0); // 300, 40
		PhysicsObject* m_PhysicsThird = new PhysicsObject("Phy3", TransformThird, 0, RIGIDBODY_STATIC);
		m_PhysicsObjects.push_back(m_PhysicsThird);
	}

	{
		OKTransform2<float>* TransformFour = new OKTransform2<float>(OKVector2<float>(0, 700), OKVector2<float>(1000, 40), 0); // 300, 40
		PhysicsObject* m_PhysicsFour = new PhysicsObject("Phy4", TransformFour, 0, RIGIDBODY_STATIC);
		m_PhysicsObjects.push_back(m_PhysicsFour);
	}
	
	{
		OKTransform2<float>* TransformFive = new OKTransform2<float>(OKVector2<float>(10, 710), OKVector2<float>(40, 40), 0); // 300, 40
		PhysicsObject* m_PhysicsFive = new PhysicsObject("Phy5", TransformFive, 0, 40, RIGIDBODY_STATIC);
		m_PhysicsObjects.push_back(m_PhysicsFive);
	}

	{
		OKTransform2<float>* TransformFive = new OKTransform2<float>(OKVector2<float>(850, 730), OKVector2<float>(40, 40), 0); // 300, 40
		PhysicsObject* m_PhysicsFive = new PhysicsObject("Phy5", TransformFive, 0, 40, RIGIDBODY_STATIC);
		m_PhysicsObjects.push_back(m_PhysicsFive);
	}

	OKTransform2<float>* TriggerTransformFirst = new OKTransform2<float>(OKVector2<float>(380, 250), OKVector2<float>(150, 150), 0); // 30, 60
	TriggerArea* m_TriggerAreaFirst = new TriggerArea("Trigger First", TriggerTransformFirst);

	OKTransform2<float>* TriggerTransformSecond = new OKTransform2<float>(OKVector2<float>(850, 600), OKVector2<float>(150, 150), 0); // 30, 60
	TriggerArea* m_TriggerAreaSecond = new TriggerArea("Trigger Second", TriggerTransformSecond, 60.f);

	OKTransform2<float>* TriggerTransformThird = new OKTransform2<float>(OKVector2<float>(30, 600), OKVector2<float>(40, 80), 0); // 30, 60
	TriggerArea* m_TriggerAreaThird = new TriggerArea("Trigger Third", TriggerTransformThird, true, false);

	ColliderManager* t_ColliderManager = new ColliderManager();
	CollisionManifold t_ColMani = CollisionManifold();
	CollisionResolution* t_CollisionResolution = new CollisionResolution();

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
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(-800 * timer->GetDeltaTime(), 0);
		}

		if (IsKeyDown(KEY_D))
		{
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(800 * timer->GetDeltaTime(), 0);
		}

		if (IsKeyPressed(KEY_SPACE))
		{
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(0, -1000);
		}

		m_TriggerAreaFirst->Draw();

		m_TriggerAreaFirst->TriggerEntered(m_PhysicsObjects[0]);
		m_TriggerAreaFirst->TriggerStayed(m_PhysicsObjects[0],
			[] {
				DrawText("this has entered the box", 10, 10, 50, PURPLE);
			});

		m_TriggerAreaSecond->Draw();

		m_TriggerAreaSecond->TriggerEntered(m_PhysicsObjects[0]);
		m_TriggerAreaSecond->TriggerStayed(m_PhysicsObjects[0],
			[] {
				DrawText("this has entered the circle", 10, 10, 50, PURPLE);
			});

		m_TriggerAreaThird->Draw();

		m_TriggerAreaThird->TriggerEntered(m_PhysicsObjects[0]);
		m_TriggerAreaThird->TriggerStayed(m_PhysicsObjects[0], []
		{
			DrawText("this has entered the capsule", 10, 10, 50, ORANGE);

		});
		// m_TriggerAreaThird->TriggerExited(m_PhysicsObjects[0]);

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
					t_CollisionResolution->ResolveCollision(m_PhysicsObjects[i]->GetRigidbody(), m_PhysicsObjects[j]->GetRigidbody(), 0.9f, t_ColMani.m_PenetrationDepth, t_ColMani.m_CollisionNormal, GetFrameTime());
				}
			}
		}

		for (auto& v : m_PhysicsObjects)
		{
			v->Update(timer->GetDeltaTime());
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