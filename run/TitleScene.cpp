#include "pch.h"
#include "TitleScene.h"

TitleScene::TitleScene()
	:SceneBase(SceneBase::Scene::e_title)
	, m_SceneTestCnt(0)
{
	m_ScenetestGraph = LoadGraph("data/sceneTest/TitleYagi.png");

}

TitleScene::~TitleScene()
{
}

SceneBase* TitleScene::Update(float _deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_SceneTestCnt++;
	}

	if (m_SceneTestCnt > 0)
	{
		return new GameScene();
	}
	else
	{
		m_SceneTestCnt = 0;
		return this; 
	}

}

void TitleScene::Draw()
{
	DrawGraph(0, 0, m_ScenetestGraph, TRUE);

}
