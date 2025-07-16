#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";

	{
		m_CircleObjectTwo.m_Transform.position = OKVector2<float>(0, 0);
		m_CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
		m_CircleObjectTwo.GetComponent<Rigidbody2DComponent>()->ApplyImpulseX(80);
		m_CircleObjectTwo.AddComponent<RectangleColliderComponent>()->Construct(50, 50);
		AddObject(&m_CircleObjectTwo);
	}

	{
		m_OtherObject.m_Transform.position = OKVector2<float>(60, -200);
		m_OtherObject.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
		m_OtherObject.AddComponent<RectangleColliderComponent>()->Construct(140, 140);
		m_OtherObject.GetComponent<RectangleColliderComponent>()->m_IsTrigger = true;

		m_OtherObject.GetComponent<RectangleColliderComponent>()->TriggerStayedExecute([&]()
		{

			// NOTE: Do stuff to the objects
			for (auto itr = m_OtherObject.GetComponent<RectangleColliderComponent>()->GetObjects().begin(); itr != m_OtherObject.GetComponent<RectangleColliderComponent>()->GetObjects().end(); ++itr)
			{
				(*itr)->GetComponent<Rigidbody2DComponent>()->ApplyForceX(-600.f);
			}

			// printf("Collision: %d", m_OtherObject.GetComponent<RectangleColliderComponent>()->GetObjectCount());
		});

		AddObject(&m_OtherObject);
	}

	// floor
	{
		m_Floor.m_Transform.position = OKVector2<float>(0.f, -300.f);
		m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
		m_Floor.AddComponent<RenderComponent>()->Construct(700.f, 50.f);
		m_Floor.GetComponent<RenderComponent>()->m_ColourTint = OKVector4<unsigned int>(150u, 75u, 0u, 255u);
		m_Floor.AddComponent<RectangleColliderComponent>()->Construct(700.f, 50.f);
		AddObject(&m_Floor);
	}

}

TestScene::~TestScene()
{
	
}

void TestScene::Update(const float deltaTime)
{
	SceneEntity::Update(deltaTime);



	// m_Owner->ChangeScene("DefaultScene");
}

void TestScene::Draw()
{
	SceneEntity::Draw();

}
