#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
	:SceneBase(SceneBase::Scene::e_game)
	, m_SceneTestCnt(0)
{
	m_ScenetestGraph=LoadGraph("data/sceneTest/GameYagi.png");
}

GameScene::~GameScene()
{
}

SceneBase* GameScene::Update(float _deltaTime)
{


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_SceneTestCnt++;
	}

	if (m_SceneTestCnt > 0)
	{
		return new TitleScene();
	}
	else
	{
		m_SceneTestCnt = 0;
		return this;
	}
}

void GameScene::Draw()
{
	DrawGraph(0,0,m_ScenetestGraph,TRUE);
}
