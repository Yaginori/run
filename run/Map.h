//-------------------------------------------------
//  マップの生成、排除、描画などを管理するクラス
//-------------------------------------------------
#pragma once

//--------------------------------------------------
//定数
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

	//初期化処理
	void Init(const MAP_KIND& in_kind)
	{
		kind = in_kind;
	}
};


//------------------------------------------------------------
//クラス定義
//------------------------------------------------------------
class Map
{
public:
	Map(); //コンストラクタ
	~Map(); //デストラクタ

	void Update(); //制御
	void Draw();   //描画
	//void DrawSkyDome(); //スカイドーム描画
	void DestroyObject(const int in_x, const int in_y, const int in_z);
	void CreateMap(); // マップ生成
	// 指定したオブジェクトのポインタを返す
	// ;;マップ全体を揺らすときとか、オブジェクトの座標移動に使ってたよ
	GameObject* GetMapObject(const int& in_x,
		                     const int& in_y,
		                     const int& in_z);
	// 指定した位置のマップ情報を返す
	// ;;渡してるのがタグ付けのデータなので、それ使ってifとかswitchで分けやすくする関数
	MapObjectInitT* GetMapData(const int& in_x,
		                       const int& in_y,
		                       const int& in_z);
	
	void Map::ReadMapData(SceneBase::Scene in_stageData);// マップデータの読み込み


private:
	// オブジェクトの生成
	void CreateObject(const int in_x,
					  const int in_y,
		              const int in_z,
					  const MAP_KIND & in_kind);



	// 生成するオブジェクト毎の生成処理へジャンプする
	GameObject* (Map::* SelectCreateMapObject[MAP_KIND_BASE])(const VECTOR& inStartPosition);
	GameObject* CreateFloor(const VECTOR& in_pos);
	//GameObject* CreateWall(const VECTOR& in_pos);



	// 削除
	void EraseMapObject(const int in_X,
		                const int in_Y,
		                const int in_Z);




	MapObjectInitT m_mapData[MAP_X][MAP_Y][MAP_Z];
	GameObject* m_mapObject[MAP_X][MAP_Y][MAP_Z];
	int m_modelHandle[MAP_KIND_BASE];
};
