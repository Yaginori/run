#include "pch.h"

//--------------------------------------------------
//�萔
//--------------------------------------------------
const char* FLOOR_HANDLE = "data/model/stage/wall/House.mv1";

const float OBJECT_SIZE = 50.0f;

//------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------
Map::Map()
{
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			for (int k = 0; k < MAP_Z; k++)
			{
				m_mapData[i][j][k].kind = MAP_NONE;
				m_mapObject[i][j][k] = NULL;

			}
		}
	}

	m_modelHandle[MAP_FLOOR] = MV1LoadModel(FLOOR_HANDLE);

	VECTOR startPos;
	startPos.x = 0.0f;
	startPos.y = 0.0f;
	startPos.z = 0.0f;

	//#
	//skyDome.LoadModel(SKY_DOME_HANDLE);
	//skyDome.SetPosition(&VGet(0.0f, 0.0f, 0.0f));
	//skyDome.Scale(VGet(SKY_DOME_SCALE, SKY_DOME_SCALE, SKY_DOME_SCALE));


	SelectCreateMapObject[MAP_NONE] = NULL;
	SelectCreateMapObject[MAP_FLOOR] = &Map::CreateFloor;
	//SelectCreateMapObject[MAP_WALL] = &Map::CreateWall;
}
//---------------------------------------
// �f�X�g���N�^
//-----------------------------------------
Map::~Map()
{
	//�����Ȃ�
}

//---------------------------------------
// �`��
//-----------------------------------------
void Map::Draw()
{

}

void Map::DestroyObject(const int in_x, const int in_y, const int in_z)
{
	delete (m_mapObject[in_x][in_y][in_z]);
	m_mapObject[in_x][in_y][in_z] = NULL;
	m_mapData[in_x][in_y][in_z].kind = MAP_NONE;

}


//---------------------------------------
// ����
//-----------------------------------------
void Map::Update()
{
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			for (int k = 0; k < MAP_Z; k++)
			{

				if (m_mapObject[i][j][k] != NULL)
				{
					DestroyObject(i, j, k);
				}

			}
		}
	}
}

//---------------------------------------
// �}�b�v����
//---------------------------------------
void Map::CreateMap()
{
	for (int i = 0; i < MAP_X; i++)
	{
		for (int j = 0; j < MAP_Y; j++)
		{
			for (int k = 0; k < MAP_Z; k++)
			{

				CreateObject(i, j, k, m_mapData[i][j][k].kind);

			}
		}
	}

}

//----------------------------------------
// �w�肵���I�u�W�F�N�g�̃|�C���^��Ԃ�
//----------------------------------------
GameObject* Map::GetMapObject(const int& in_x, const int& in_y, const int& in_z)
{
	return m_mapObject[in_x][in_y][in_z];
}

//----------------------------------------
// �w�肵���ʒu�̃}�b�v�̎�ނ�Ԃ�
//----------------------------------------
MapObjectInitT* Map::GetMapData(const int& in_x, const int& in_y, const int& in_z)
{
	return &m_mapData[in_x][in_y][in_z];
}

void Map::ReadMapData(const int& in_stageData)
{
	string fileName = "data/mapData/stage.csv";

	//�t�@�C���̓ǂݍ���
	ifstream ifs(fileName);
	if (!ifs)
	{
		printfDx("�}�b�v�t�@�C���̓ǂݍ��݂Ɏ��s");
	}
	int tmp = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int cnt = 0;
	string str;

	while (getline(ifs, str));
	{
		string token;
		istringstream stream(str);

		//@@@��s�̂����A������ƃR���}�𕪊�����
		while (getline(stream, token, ','));
		{

			//@@@���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			//@@@���l�͕ϊ����K�v
			tmp = stoi(token);

			m_mapData[i][j][k].kind = (MAP_KIND)tmp;
	
		}

		//@@@�v�Z���B����0616�ɕ����������Ƃ͏���������u���C�N�|�C���g�u���Č���
		k = (k + 1) % MAP_X;
		if (k == 0)
		{
			j = (j + 1) % MAP_Y;
		}
		if (k == 0 && j == 0)
		{
			i = (i + 1) % MAP_Z;
		}
	}
}

//----------------------------------------
// �I�u�W�F�N�g�̐���
//----------------------------------------
void Map::CreateObject(const int in_x, const int in_y, const int in_z, const MAP_KIND& in_kind)
{
	// �����������Ȃ��ꍇ
	if (in_kind == MAP_NONE)
	{
		m_mapObject[in_x][in_y][in_z] = NULL;
		return;
	}

	//@@@�v�Z��
	VECTOR pos;
	pos.x = (float)in_x * OBJECT_SIZE - (float)MAP_X * OBJECT_SIZE / 2 - OBJECT_SIZE / 2;
	pos.y = -50.0f + 50.0f * (float)in_y;
	pos.z = -(float)in_z * OBJECT_SIZE + (float)MAP_Z * OBJECT_SIZE / 2 + OBJECT_SIZE / 2;

	//���������̍X�V
	//@@@���������Ĉ�񂾂����Ǝv���Ă�
	m_mapData[in_x][in_y][in_z].Init(in_kind);

	//����
	//@@@�|�C���^�Ƃ��F�X��������B��ނƃ|�W�V�������֘A�t����c�Ƃ����������Ȃ񂩁H
	m_mapObject[in_x][in_y][in_z] = (this->*SelectCreateMapObject[in_kind])(pos);
}

//----------------------------------------
// �폜
//----------------------------------------
void Map::EraseMapObject(const int in_X, const int in_Y, const int in_Z)
{
	delete(m_mapObject[in_X][in_Y][in_Z]);
	m_mapObject[in_X][in_Y][in_Z] = NULL;
	m_mapData[in_X][in_Y][in_Z].kind = MAP_NONE;
}


GameObject* Map::CreateFloor(const VECTOR& in_pos)
{
	return new Floor(in_pos,m_modelHandle[MAP_FLOOR],true);
}


//GameObject* Map::CreateWall(const VECTOR& in_pos)
//{
//	//return new Wall(in_pos,m_modelHandle[MAP_FLOOR],true);
//}
