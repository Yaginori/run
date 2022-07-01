#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
	:SceneBase(SceneBase::Scene::e_game)
{
}

GameScene::~GameScene()
{
}

SceneBase* GameScene::Update(float _deltaTime)
{


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return new TitleScene();

	}
	return this;
}

void GameScene::Draw()
{
}
