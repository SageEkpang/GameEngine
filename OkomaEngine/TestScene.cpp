#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";

	CircleObjectTwo.m_Transform.position = OKVector2<float>(20, 200);
	CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	CircleObjectTwo.AddComponent<RenderComponent>()->Construct(50.f, 50.f);
	CircleObjectTwo.AddComponent<RectangleColliderComponent>()->Construct(50, 50);
	CircleObjectTwo.AddComponent<CameraComponent>()->Construct();
	AddObject(&CircleObjectTwo);

	//Area.m_Transform.position = OKVector2<float>(400.f, -200.f);
	//Area.AddComponent<Rigidbody2DComponent>();
	//Area.AddComponent<RectangleColliderComponent>()->Construct(200.f, 200.f);
	//Area.GetComponent<RectangleColliderComponent>()->m_IsTrigger = true;

	//Area.GetComponent<RectangleColliderComponent>()->TriggerStayedExecute(
	//[&]() 
	//{
	//	Area.GetComponent<RectangleColliderComponent>()->GetTriggerObject()->GetComponent<Rigidbody2DComponent>()->ApplyForceY(1000.f);
	//});

	//AddObject(&Area);





	m_Floor.m_Transform.position = OKVector2<float>(0.f, -200.f);
	m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
	m_Floor.AddComponent<RenderComponent>()->Construct(500.f, 50.f);
	m_Floor.GetComponent<RenderComponent>()->m_ColourTint = OKVector4<unsigned int>(150u, 75u, 0u, 255u);
	m_Floor.AddComponent<RectangleColliderComponent>()->Construct(500.f, 50.f);
	AddObject(&m_Floor);
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
