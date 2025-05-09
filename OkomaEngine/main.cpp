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

	int ParticleAmount = 10000;
	ParticleSystem* m_ParticleSystem = new ParticleSystem(OKVector2<float>(500, 400), ParticleAmount);
	{
		m_ParticleSystem->AssignParticleEmitterType(PARTICLE_EMITTER_TYPE_SINGLE);
		m_ParticleSystem->AssignParticleAction(PARTICLE_ACTION_BURST_OUT);

		m_ParticleSystem->AssignParticleSpawnAreaCircle(40.f);

		m_ParticleSystem->AssignParticleAction(PARTICLE_ACTION_SPRAY);
		m_ParticleSystem->SetLooping(true);
		m_ParticleSystem->SetEmissionRateOverTime(500u);
		m_ParticleSystem->SetDuration(0.5f);
		m_ParticleSystem->SetStartSpeed(5.0);
		m_ParticleSystem->SetStartSpeed(1.0);
		m_ParticleSystem->SetStartLifeTime(1.0f);
		m_ParticleSystem->AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
		// m_ParticleSystem->AssignVelocityOverLifeTime(OKVector2<float>(0.f, -100.f), OKVector2<float>(0.f, -400.f));
		m_ParticleSystem->AssignColourOverLifeTime(OKVector3<unsigned int>(255, 255, 0), OKVector3<unsigned int>(255, 0, 0));
		m_ParticleSystem->AssignResizeOverLifeTime(OKVector2<float>(20.f, 20.f), OKVector2<float>(1.f, 1.f));
	}
	
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

	//ColliderManager colMani;

	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
		ClearBackground(BLACK);

		m_Accumulator += timer->GetDeltaTime();
		m_SimpleCounter += timer->GetDeltaTime();


		//m_ParticleSystemTwo->Update(GetFrameTime());
		//m_ParticleSystemTwo->Draw();

		m_ParticleSystem->Update(GetFrameTime());
		m_ParticleSystem->Draw();

		//OKVector2<float> tempMouse = OKVector2<float>(GetMouseX(), GetMouseY());

		//if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		//{
		//	m_Line->SetLineStartPosition(tempMouse);
		//	// m_CapsuleTwo->SetPosition(tempMouse);
		//}

		//if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		//{

		//	m_Line->SetLineEndPosition(tempMouse);
		//}


		// m_Point->Draw();
		// m_Line->Draw();
		// m_LineTwo->Draw();
		// m_Circle->Draw();
		// m_Rectangle->Draw();
		// m_Capsule->Draw();
		//  m_CapsuleTwo->Draw();

		//if (colMani.CheckCollisions(m_Line, m_Capsule).m_HasCollision)
		//{
		//	DrawText("Has Collided", 30, 30, 40, GREEN);
		//}







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