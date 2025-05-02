#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"

#include "PhysicsObject.h"
#include "TriggerArea.h"
#include "ColliderManager.h"
#include "CollisionResolution.h"
 #include "ParticleSystem.h"

 std::vector<PhysicsObject*> m_PhysicsObjects;

int main()
{
	// Game Utility (namespace) over Game Manager (class)
	InitWindow(1000, 800, "OkomaEngine");
	InitAudioDevice();

	Timer* timer = new Timer();
	float m_Accumulator = 0;
	float m_SimpleCounter = 0;

	int ParticleAmount = 1000;
	ParticleSystem* m_ParticleSystem = new ParticleSystem(OKVector2<float>(500, 400), ParticleAmount);
	
	m_ParticleSystem->SetLooping(true);
	m_ParticleSystem->SetEmissionRateOverTime(100u);
	m_ParticleSystem->SetStartSpeed(1.0);
	m_ParticleSystem->SetStartLifeTime(1.0f);

	m_ParticleSystem->AssignForceOverLifeTime(OKVector2<float>(0.f, 0.f), OKVector2<float>(0.f, -100.f));
	m_ParticleSystem->AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
	m_ParticleSystem->AssignParticleAction(PARTICLE_ACTION_BURST_OUT);

	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
		ClearBackground(BLACK);

		m_Accumulator += timer->GetDeltaTime();
		m_SimpleCounter += timer->GetDeltaTime();


		m_ParticleSystem->Update(GetFrameTime());
		m_ParticleSystem->Draw();


		//if (IsKeyDown(KEY_A))
		//{
		//	m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(-800 * timer->GetDeltaTime(), 0);
		//}

		//if (IsKeyDown(KEY_D))
		//{
		//	m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(800 * timer->GetDeltaTime(), 0);
		//}

		//if (IsKeyPressed(KEY_SPACE))
		//{
		//	m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(0, -1000);
		//}

		//for (int i = 0; i < m_PhysicsObjects.size(); ++i)
		//{
		//	for (int j = 0; j < m_PhysicsObjects.size(); ++j)
		//	{
		//		if (i == j) { continue; }

		//		t_ColMani = t_ColliderManager->CheckCollisions(m_PhysicsObjects[i]->GetCollider(), m_PhysicsObjects[j]->GetCollider());
		//		// DrawText(TextFormat("col: %d", t_ColMani.m_HasCollision), 10, 10, 40, PINK);
		//		
		//		if (t_ColMani.m_HasCollision == true)
		//		{
		//			// NOTE: Coef is Bounce Level to the collision detection
		//			t_CollisionResolution->ResolveCollision(m_PhysicsObjects[i]->GetRigidbody(), m_PhysicsObjects[j]->GetRigidbody(), 0.9f, t_ColMani.m_PenetrationDepth, t_ColMani.m_CollisionNormal, GetFrameTime());
		//		}
		//	}
		//}

		//for (auto& v : m_PhysicsObjects)
		//{
		//	v->Update(timer->GetDeltaTime());
		//}

		//for (auto& v : m_PhysicsObjects)
		//{
		//	v->Draw();
		//}

		if (m_Accumulator >= FPS_60)
		{
			m_Accumulator -= FPS_60;
		}

		timer->Tick();

		EndDrawing();
	}

	delete m_ParticleSystem;
	
	CloseAudioDevice();
	CloseWindow();

	return 0;
}