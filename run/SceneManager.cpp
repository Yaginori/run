#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager(SceneBase::Scene in_nowScene)
	:m_testSceneCnt(0)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SceneChange()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_testSceneCnt++;
	}

	if (m_testSceneCnt > 0)
	{
		return new TitleScene();
	}
	else
	{
		m_testSceneCnt = 0;
		return this;
	}

}
