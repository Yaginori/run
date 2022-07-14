#include "pch.h"
#include "GameScene.h"

//------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------
GameScene::GameScene()
	:SceneBase(SceneBase::Scene::e_game)
	, m_SceneChangeFlag(false)
{
	m_player = new Player();
	m_map = new Map();
	m_camera = new Camera();

	m_map->ReadMapData(SceneBase::Scene::e_game);
}

//------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------
GameScene::~GameScene()
{
	delete(m_player);
	delete(m_map);
	delete(m_camera);
}

//------------------------------------------------
// ����
//-------------------------------------------------
SceneBase* GameScene::Update(float _deltaTime)
{
	m_player->Update(_deltaTime);
	m_map->Update();
	m_map->CreateMap();
	m_camera->Update(*m_player);


	if (CheckHitKey(KEY_INPUT_A))
	{
		m_SceneChangeFlag = true;
	}

	if (m_SceneChangeFlag)
	{
		return new ResultScene();
	}
	else
	{
		return this;
	}


	return this;
}

//------------------------------------------------
// �`��
//-------------------------------------------------
void GameScene::Draw()
{
	m_player->Draw();
	m_map->Draw();

	//DrawGraph(0,0,m_ScenetestGraph,TRUE);
}

//------------------------------------------------
// �f�[�^�̓ǂݍ���
//-------------------------------------------------
void GameScene::Load()
{

}
