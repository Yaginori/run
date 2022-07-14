//-------------------------------------------------
//  �}�b�v�̐����A�r���A�`��Ȃǂ��Ǘ�����N���X
//-------------------------------------------------
#pragma once

//--------------------------------------------------
//�萔
//--------------------------------------------------
const int MAP_X = 3;
const int MAP_Y = 1;
const int MAP_Z = 100;

enum MAP_KIND
{
	MAP_NONE,MAP_FLOOR,MAP_WALL,MAP_KIND_BASE
};

struct MapObjectInitT
{
	MAP_KIND kind;

	//����������
	void Init(const MAP_KIND& in_kind)
	{
		kind = in_kind;
	}
};


//------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------
class Map
{
public:
	Map(); //�R���X�g���N�^
	~Map(); //�f�X�g���N�^

	void Update(); //����
	void Draw();   //�`��
	//void DrawSkyDome(); //�X�J�C�h�[���`��
	void DestroyObject(const int in_x, const int in_y, const int in_z);
	void CreateMap(); // �}�b�v����
	// �w�肵���I�u�W�F�N�g�̃|�C���^��Ԃ�
	// ;;�}�b�v�S�̂�h�炷�Ƃ��Ƃ��A�I�u�W�F�N�g�̍��W�ړ��Ɏg���Ă���
	GameObject* GetMapObject(const int& in_x,
		                     const int& in_y,
		                     const int& in_z);
	// �w�肵���ʒu�̃}�b�v����Ԃ�
	// ;;�n���Ă�̂��^�O�t���̃f�[�^�Ȃ̂ŁA����g����if�Ƃ�switch�ŕ����₷������֐�
	MapObjectInitT* GetMapData(const int& in_x,
		                       const int& in_y,
		                       const int& in_z);
	
	void Map::ReadMapData(SceneBase::Scene in_stageData);// �}�b�v�f�[�^�̓ǂݍ���


private:
	// �I�u�W�F�N�g�̐���
	void CreateObject(const int in_x,
					  const int in_y,
		              const int in_z,
					  const MAP_KIND & in_kind);



	// ��������I�u�W�F�N�g���̐��������փW�����v����
	GameObject* (Map::* SelectCreateMapObject[MAP_KIND_BASE])(const VECTOR& inStartPosition);
	GameObject* CreateFloor(const VECTOR& in_pos);
	//GameObject* CreateWall(const VECTOR& in_pos);



	// �폜
	void EraseMapObject(const int in_X,
		                const int in_Y,
		                const int in_Z);




	MapObjectInitT m_mapData[MAP_X][MAP_Y][MAP_Z];
	GameObject* m_mapObject[MAP_X][MAP_Y][MAP_Z];
	int m_modelHandle[MAP_KIND_BASE];
};
