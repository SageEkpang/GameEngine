#include "HeaderManager.h"
#include "WindowConstants.h"
#include "Timer.h"
#include "TimeStepConstants.h"

int main()
{
	// NOTE: Check the window has actually been inited
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


	//Timer* timer = new Timer();
	//float m_Accumulator = 0;
	//float m_SimpleCounter = 0;

	// FIRE

	//int ParticleAmount = 10000;
	//ParticleEffect* m_ParticleSystem = new ParticleEffect(OKVector2<float>(500, 400), ParticleAmount);
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
	//
	//// SMOKE

	//int ParticleAmountTwo = 50;
	//ParticleEffect* m_ParticleSystemTwo = new ParticleEffect(OKVector2<float>(500, 400), ParticleAmountTwo);
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

	//OKTransform2<float> AltFirst = OKTransform2<float>(OKVector2<float>(650, 200), OKVector2<float>(50, 50), 0); // 30, 60
	//PhysicsObject* m_AltObjFirst = new PhysicsObject("Phy1", AltFirst, 2.f, RIGIDBODY_DYNAMIC);
	//m_PhysicsObjects.push_back(m_AltObjFirst);


	//OKTransform2<float> TransformFour = OKTransform2<float>(OKVector2<float>(300, 700), OKVector2<float>(700, 50), 0); // 300, 40
	//PhysicsObject* m_PhysicsFour = new PhysicsObject("Phy4", TransformFour, 0, RIGIDBODY_STATIC);
	//m_PhysicsObjects.push_back(m_PhysicsFour);

	//ColliderManager* t_ColliderManager = new ColliderManager();
	//CollisionManifold t_ColMani = CollisionManifold();
	//CollisionResolution* t_CollisionResolution = new CollisionResolution();

	Camera2D camera = { 0 };

	// Move the origin to the center of the screen
	camera.offset = Vector2{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;

	rlDisableBackfaceCulling();

	// SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		// UPDATE

		// DRAW
		BeginDrawing();
			ClearBackground(BLACK);

			BeginMode2D(camera);

			rlPushMatrix();
			rlScalef(1.0f, -1.0f, 1.0f);

			// NOTE: Draw Here ------


			DrawCircle(0, 0, 3, GREEN);



		
			rlPopMatrix();
			EndMode2D();
		EndDrawing();
	}


	//if (m_Accumulator >= FPS_60)
		//{
		//	m_Accumulator -= FPS_60;
		//}

		//timer->Tick();

	// delete m_ParticleSystem;
	
	CloseAudioDevice();
	CloseWindow();

	return 0;
}