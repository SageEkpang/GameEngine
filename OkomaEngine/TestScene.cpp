#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";
	m_PhyMana.SetDrawColliders(true);
	m_PhyMana.SetDrawDebugVelocity(true);

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

	CircleObjectTwo.m_Transform.position = OKVector2<float>(20, 200);
	CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	CircleObjectTwo.GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(100.f);
	CircleObjectTwo.AddComponent<RectangleColliderComponent>()->Construct(40.0f, 40.0f);
	m_PhyMana.AddPhysicsObject(&CircleObjectTwo);

	m_Floor.m_Transform.position = OKVector2<float>(0.f, -200.f);
	m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
	m_Floor.AddComponent<RectangleColliderComponent>()->Construct(500.f, 50.f);
	m_PhyMana.AddPhysicsObject(&m_Floor);
}

TestScene::~TestScene()
{


}

void TestScene::Update(const float deltaTime)
{
	m_PhyMana.Update(deltaTime);

	if (IsKeyPressed(KEY_SPACE))
	{
		m_Owner->ResetScene();
		// m_Owner->ChangeScene("DefaultScene", 2.f);
	}
}

void TestScene::Draw()
{
	m_PhyMana.Draw();
}
