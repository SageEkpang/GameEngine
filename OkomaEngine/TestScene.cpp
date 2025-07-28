#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";

	{
		//GameObjectEntity m_CircleObjectTwo;
		//m_CircleObjectTwo.m_Transform.position = OKVector2<float>(0, 0);
		//m_CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
		//m_CircleObjectTwo.AddComponent<CircleColliderComponent>()->Construct(40);
		//AddObject(&m_CircleObjectTwo);
	}

	// floor
	{
		//m_Floor.m_Transform.position = OKVector2<float>(0.f, -300.f);
		//m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
		//m_Floor.AddComponent<RenderComponent>()->Construct(700.f, 50.f);
		//m_Floor.GetComponent<RenderComponent>()->m_ColourTint = OKVector4<unsigned int>(150u, 75u, 0u, 255u);
		//m_Floor.AddComponent<RectangleColliderComponent>()->Construct(700.f, 50.f);
		//AddObject(&m_Floor);
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
	

}
