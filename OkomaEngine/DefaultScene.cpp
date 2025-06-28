#include "DefaultScene.h"
#include "SceneManager.h"

DefaultScene::DefaultScene()
{
	m_Name = "DefautScene";

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

}

DefaultScene::~DefaultScene()
{


}

void DefaultScene::Update(const float deltaTime)
{
	//if (IsKeyPressed(KEY_SPACE))
	//{
	//	m_Owner->ResetScene();
	//}
}

void DefaultScene::Draw()
{
	DrawCircle(0, 0, 4.f, RED);

}
