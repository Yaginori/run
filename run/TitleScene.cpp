#include "pch.h"
#include "TitleScene.h"

TitleScene::TitleScene()
	:SceneBase(SceneBase::Scene::e_title)
{

}

TitleScene::~TitleScene()
{
}

SceneBase* TitleScene::Update(float _deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return new GameScene();

	}
	return this;

}

void TitleScene::Draw()
{
}
