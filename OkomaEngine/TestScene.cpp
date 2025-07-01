#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";

	{
		m_CircleObjectTwo.m_Transform.position = OKVector2<float>(0, 0);
		m_CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
		// m_CircleObjectTwo.GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(100);
		m_CircleObjectTwo.AddComponent<CircleColliderComponent>()->Construct(50);
		AddObject(&m_CircleObjectTwo);
	}

	{
		m_ExtraObject.m_Transform.position = OKVector2<float>(0, 0);
		m_ExtraObject.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
		m_ExtraObject.GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(100);
		m_ExtraObject.AddComponent<CapsuleColliderComponent>()->Construct(40, 80);
		// AddObject(&m_ExtraObject);
	}

	{
		m_OtherObject.m_Transform.position = OKVector2<float>(200, 0);
		m_OtherObject.AddComponent<Rigidbody2DComponent>()->Construct(10.f, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
		m_OtherObject.AddComponent<CapsuleColliderComponent>()->Construct(40, 80);
		// AddObject(&m_OtherObject);
	}

	{
		m_Floor.m_Transform.position = OKVector2<float>(0.f, -200.f);
		m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
		m_Floor.AddComponent<RenderComponent>()->Construct(500.f, 50.f);
		m_Floor.GetComponent<RenderComponent>()->m_ColourTint = OKVector4<unsigned int>(150u, 75u, 0u, 255u);
		m_Floor.AddComponent<RectangleColliderComponent>()->Construct(500.f, 50.f);
		AddObject(&m_Floor);
	}

}

TestScene::~TestScene()
{
	
}

void TestScene::Update(const float deltaTime)
{
	SceneEntity::Update(deltaTime);






}

void TestScene::Draw()
{
	SceneEntity::Draw();

}
