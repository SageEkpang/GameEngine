#include "DefaultScene.h"
#include "SceneManager.h"

DefaultScene::DefaultScene()
{
	m_Name = "DefautScene";

}

DefaultScene::~DefaultScene()
{


}

void DefaultScene::Update(const float deltaTime)
{
	if (IsKeyPressed(KEY_SPACE))
	{
		m_Owner->ResetScene();
	}
}

void DefaultScene::Draw()
{
	DrawCircle(0, 0, 4.f, RED);

}
