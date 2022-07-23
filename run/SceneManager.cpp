#include "pch.h"
#include "SceneManager.h"



SceneManager::SceneManager()
{
	m_nowScene = nullptr;
}

SceneManager::~SceneManager()
{
	delete m_nowScene;
}

void SceneManager::Update(float _deltaTime)
{
	SceneBase* tmpScene = m_nowScene->Update(_deltaTime); // ���݂̃V�[����ۑ�����

	if (tmpScene != m_nowScene) // �V�[�����؂�ւ������
	{
		delete m_nowScene;
		m_nowScene = tmpScene;
		m_nowScene->Load();
	}

}

void SceneManager::Draw()
{
	m_nowScene->Draw();
}

void SceneManager::Sound()
{
}

void SceneManager::SetScene(SceneBase* in_scene)
{
	if (m_nowScene != nullptr) // m_nowScene���󔒂ł͂Ȃ�������
	{
		delete m_nowScene;     // m_nowScene�����
	}


	m_nowScene = in_scene;
	m_nowScene->Load();
}
