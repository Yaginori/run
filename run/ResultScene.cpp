#include "pch.h"
#include "ResultScene.h"

ResultScene::ResultScene()
	:SceneBase(SceneBase::Scene::e_result)
	,m_SceneChangeFlag(false)
{
	m_ScenetestGraph = LoadGraph("data/sceneTest/GameYagi.png");
}

ResultScene::~ResultScene()
{

}

SceneBase* ResultScene::Update(float _deltaTime)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_SceneChangeFlag = true;
	}

	if (m_SceneChangeFlag)
	{
		return new TitleScene();
	}
	else
	{
		return this;
	}

}

void ResultScene::Draw()
{
	DrawGraph(0, 0, m_ScenetestGraph, TRUE);

}

void ResultScene::Load()
{
}
