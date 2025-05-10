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

	// FIRE

	//int ParticleAmount = 10000;
	//ParticleSystem* m_ParticleSystem = new ParticleSystem(OKVector2<float>(500, 400), ParticleAmount);
	//{
	//	m_ParticleSystem->AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
	//	m_ParticleSystem->AssignParticleAction(PARTICLE_ACTION_BURST_OUT);

	//	m_ParticleSystem->AssignParticleSpawnAreaCircle(40.f);

	//	m_ParticleSystem->AssignParticleAction(PARTICLE_ACTION_SPRAY);
	//	m_ParticleSystem->SetLooping(true);
	//	m_ParticleSystem->SetEmissionRateOverTime(500u);
	//	m_ParticleSystem->SetDuration(0.5f);
	//	m_ParticleSystem->SetStartSpeed(5.0);
	//	m_ParticleSystem->SetStartSpeed(1.0);
	//	m_ParticleSystem->SetStartLifeTime(1.0f);
	//	m_ParticleSystem->AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
	//	// m_ParticleSystem->AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
	//	m_ParticleSystem->AssignColourOverLifeTime(OKVector3<unsigned int>(255, 255, 0), OKVector3<unsigned int>(255, 0, 0));
	//	m_ParticleSystem->AssignResizeOverLifeTime(OKVector2<float>(20.f, 20.f), OKVector2<float>(1.f, 1.f));
	//}
	
	// SMOKE

	//int ParticleAmountTwo = 50;
	//ParticleSystem* m_ParticleSystemTwo = new ParticleSystem(OKVector2<float>(500, 400), ParticleAmountTwo);
	//{
	//	m_ParticleSystemTwo->AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
	//	m_ParticleSystemTwo->AssignParticleSpawnAreaCircle(40.f);
	//	m_ParticleSystemTwo->SetLooping(true);
	//	m_ParticleSystemTwo->SetEmissionRateOverTime(5u);
	//	m_ParticleSystemTwo->SetDuration(0.5f);
	//	m_ParticleSystemTwo->SetStartLifeTime(6.0f);
	//	m_ParticleSystemTwo->AssignVelocityOverLifeTime(OKVector2<float>(0.f, -50.f), OKVector2<float>(0.f, -100.f));
	//	m_ParticleSystemTwo->AssignColourOverLifeTime(OKVector3<unsigned int>(200, 200, 200), OKVector3<unsigned int>(50, 50, 50));
	//	m_ParticleSystemTwo->AssignResizeOverLifeTime(OKVector2<float>(20.f, 20.f), OKVector2<float>(5.f, 5.f));
	//}


	//// Point
	//OKTransform2<float> tempTransform = OKTransform2<float>();
	//Collider* m_Point = new Collider(&tempTransform, 1.f, true);

	//// Line
	//OKTransform2<float> tempLineTransform = OKTransform2<float>();
	//Collider* m_Line = new Collider(&tempLineTransform, OKVector2<float>(0.f, 500.f), OKVector2<float>(100.f, 500.f));

	//// Circle
	//OKTransform2<float> tempCircleTransform = OKTransform2<float>(OKVector2<float>(500, 500), OKVector2<float>(0.f, 0.f), 0.f);
	//Collider* m_Circle = new Collider(&tempCircleTransform, 100.f);

	//// Rectangle
	//OKTransform2<float> tempRectangleTransform = OKTransform2<float>(OKVector2<float>(500, 500), OKVector2<float>(50.f, 50.f), 0.f);
	//Collider* m_Rectangle = new Collider(&tempRectangleTransform);

	//// Line 2
	////OKTransform2<float> tempLineTransformTwo = OKTransform2<float>();
	////Collider* m_LineTwo = new Collider(&tempLineTransformTwo, OKVector2<float>(10.f, 500.f), OKVector2<float>(500.f, 500.f));

	//// Capsule
	//OKTransform2<float> tempCapsuleTransform = OKTransform2<float>(OKVector2<float>(500, 500), OKVector2<float>(50.f, 100.f), 0.f);
	//Collider* m_Capsule = new Collider(&tempCapsuleTransform, true);

	//OKTransform2<float> tempCapsuleTransformTwo = OKTransform2<float>(OKVector2<float>(0, 0), OKVector2<float>(1.f, 100.f), 0.f);
	//Collider* m_CapsuleTwo = new Collider(&tempCapsuleTransformTwo, true);

	OKTransform2<float> AltFirst = OKTransform2<float>(OKVector2<float>(650, 200), OKVector2<float>(50, 50), 0); // 30, 60
	PhysicsObject* m_AltObjFirst = new PhysicsObject("Phy1", AltFirst, 2.f, RIGIDBODY_DYNAMIC);
	m_PhysicsObjects.push_back(m_AltObjFirst);


	OKTransform2<float> TransformFour = OKTransform2<float>(OKVector2<float>(300, 700), OKVector2<float>(700, 50), 0); // 300, 40
	PhysicsObject* m_PhysicsFour = new PhysicsObject("Phy4", TransformFour, 0, RIGIDBODY_STATIC);
	m_PhysicsObjects.push_back(m_PhysicsFour);

	ColliderManager* t_ColliderManager = new ColliderManager();
	CollisionManifold t_ColMani = CollisionManifold();
	CollisionResolution* t_CollisionResolution = new CollisionResolution();


	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
		ClearBackground(BLACK);

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
			m_PhysicsObjects[0]->GetRigidbody()->AddImpulse(0, -100);
		}




		//m_ParticleSystemTwo->Update(GetFrameTime());
		//m_ParticleSystemTwo->Draw();

		//m_ParticleSystem->Update(GetFrameTime());
		//m_ParticleSystem->Draw();

		//OKVector2<float> tempMouse = OKVector2<float>(GetMouseX(), GetMouseY());

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

		if (m_Accumulator >= FPS_60)
		{
			m_Accumulator -= FPS_60;
		}

		timer->Tick();

		EndDrawing();
	}

	// delete m_ParticleSystem;
	
	CloseAudioDevice();
	CloseWindow();

	return 0;
}