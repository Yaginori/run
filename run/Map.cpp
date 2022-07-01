#include "pch.h"

//--------------------------------------------------
//定数
//--------------------------------------------------
const char* FLOOR_HANDLE = "data/model/stage/wall/House.mv1";

const float OBJECT_SIZE = 50.0f;

//------------------------------------------------
// コンストラクタ
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
// デストラクタ
//-----------------------------------------
Map::~Map()
{
	//処理なし
}

//---------------------------------------
// 描画
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
// 制御
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
// マップ生成
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
// 指定したオブジェクトのポインタを返す
//----------------------------------------
GameObject* Map::GetMapObject(const int& in_x, const int& in_y, const int& in_z)
{
	return m_mapObject[in_x][in_y][in_z];
}

//----------------------------------------
// 指定した位置のマップの種類を返す
//----------------------------------------
MapObjectInitT* Map::GetMapData(const int& in_x, const int& in_y, const int& in_z)
{
	return &m_mapData[in_x][in_y][in_z];
}

void Map::ReadMapData(const int& in_stageData)
{
	string fileName = "data/mapData/stage.csv";

	//ファイルの読み込み
	ifstream ifs(fileName);
	if (!ifs)
	{
		printfDx("マップファイルの読み込みに失敗");
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

		//@@@一行のうち、文字列とコンマを分割する
		while (getline(stream, token, ','));
		{

			//@@@すべて文字列として読み込まれるため
			//@@@数値は変換が必要
			tmp = stoi(token);

			m_mapData[i][j][k].kind = (MAP_KIND)tmp;
	
		}

		//@@@計算式。メモ0616に分かったことは書いたからブレイクポイント置いて見て
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
// オブジェクトの生成
//----------------------------------------
void Map::CreateObject(const int in_x, const int in_y, const int in_z, const MAP_KIND& in_kind)
{
	// 何も生成しない場合
	if (in_kind == MAP_NONE)
	{
		m_mapObject[in_x][in_y][in_z] = NULL;
		return;
	}

	//@@@計算式
	VECTOR pos;
	pos.x = (float)in_x * OBJECT_SIZE - (float)MAP_X * OBJECT_SIZE / 2 - OBJECT_SIZE / 2;
	pos.y = -50.0f + 50.0f * (float)in_y;
	pos.z = -(float)in_z * OBJECT_SIZE + (float)MAP_Z * OBJECT_SIZE / 2 + OBJECT_SIZE / 2;

	//初期化情報の更新
	//@@@初期化って一回だけかと思ってた
	m_mapData[in_x][in_y][in_z].Init(in_kind);

	//生成
	//@@@ポインタとか色々ごっちゃ。種類とポジションを関連付ける…とかいう役割なんか？
	m_mapObject[in_x][in_y][in_z] = (this->*SelectCreateMapObject[in_kind])(pos);
}

//----------------------------------------
// 削除
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
