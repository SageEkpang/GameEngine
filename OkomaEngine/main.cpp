#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"

#include "PhysicsObject.h"
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

	OKTransform2<float>* TransformFirst = new OKTransform2<float>(OKVector2<float>(30, 200), OKVector2<float>(0, 0), OKVector2<float>(30, 30));
	PhysicsObject* m_PhysicsFirst = new PhysicsObject("Phy1", TransformFirst, 10, RIGIDBODY_DYNAMIC);
	m_PhysicsObjects.push_back(m_PhysicsFirst);

	//OKTransform2<float>* TransformSecond = new OKTransform2<float>(OKVector2<float>(20, 400), OKVector2<float>(0, 0), OKVector2<float>(40, 40));
	//PhysicsObject* m_PhysicsSecond = new PhysicsObject("Phy2", TransformSecond, 0, 40, RIGIDBODY_STATIC);
	//m_PhysicsObjects.push_back(m_PhysicsSecond);

	OKTransform2<float>* TransformThird = new OKTransform2<float>(OKVector2<float>(300, 400), OKVector2<float>(0, 0), OKVector2<float>(300, 40));
	PhysicsObject* m_PhysicsThird = new PhysicsObject("Phy3", TransformThird, 0, RIGIDBODY_STATIC);
	m_PhysicsObjects.push_back(m_PhysicsThird);

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

		for (auto& v : m_PhysicsObjects)
		{
			v->Update(timer->GetDeltaTime());
		}

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
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(0, -200);
		}

		for (auto& v : m_PhysicsObjects)
		{
			v->Draw();
		}

		for (int i = 0; i < m_PhysicsObjects.size(); ++i)
		{
			for (int j = 0; j < m_PhysicsObjects.size(); ++j)
			{
				if (i == j) { continue; }

				t_ColMani = t_ColliderManager->CheckCollisions(m_PhysicsObjects[i]->GetCollider(), m_PhysicsObjects[j]->GetCollider());

				if (t_ColMani.m_HasCollision == true)
				{
					t_CollisionResolution->ResolveCollision(m_PhysicsObjects[i]->GetRigidbody(), m_PhysicsObjects[j]->GetRigidbody(), 0.5f, t_ColMani.m_PenetrationDepth, t_ColMani.m_CollisionNormal, timer->GetDeltaTime());
				}
			}
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