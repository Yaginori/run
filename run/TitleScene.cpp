#include "pch.h"
#include "TitleScene.h"

TitleScene::TitleScene()
	:SceneBase(SceneBase::Scene::e_title)
	, m_SceneChangeFlag(false)
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
		m_SceneChangeFlag = true;
	}

	if (m_SceneChangeFlag)
	{
		return new GameScene();
	}
	else
	{
		return this; 
	}

}

void TitleScene::Draw()
{
	DrawGraph(0, 0, m_ScenetestGraph, TRUE);

}

void TitleScene::Load()
{

}
