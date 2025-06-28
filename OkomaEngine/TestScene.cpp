#include "TestScene.h"
#include "SceneManager.h"

TestScene::TestScene()
{
	m_Name = "TestScene";

	CircleObjectTwo.m_Transform.position = OKVector2<float>(20, 200);
	CircleObjectTwo.AddComponent<Rigidbody2DComponent>()->Construct(10, RIGIDBODY_MOVEMENT_TYPE_DYNAMIC);
	CircleObjectTwo.AddComponent<RenderComponent>()->Construct("Resources/Images/MajorasMask.png", 50.f, 50.f);
	CircleObjectTwo.AddComponent<RectangleColliderComponent>()->Construct(50.0f, 50.0f);
	AddObject(&CircleObjectTwo);

	PlayerCamera.m_Transform.position = OKVector2<float>(20, 0);
	PlayerCamera.AddComponent<CameraComponent>();
	//PlayerCamera.Parent(&CircleObjectTwo);
	AddObject(&PlayerCamera);
	m_Camera = &PlayerCamera.GetComponent<CameraComponent>()->m_Camera;

	m_Floor.m_Transform.position = OKVector2<float>(0.f, -200.f);
	m_Floor.AddComponent<Rigidbody2DComponent>()->Construct(FLT_MAX, RIGIDBODY_MOVEMENT_TYPE_STATIC);
	m_Floor.AddComponent<RenderComponent>()->Construct("Resources/Images/BoyWhoCriedArt.png", 500.f, 50.f);
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
