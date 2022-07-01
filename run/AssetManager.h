#pragma once
#include <DxLib.h>
#include <unordered_map>
//#include <atlstr.h>
#include <string>

class AssetManager
{
public:
	static AssetManager& GetInstance()
	{
		static AssetManager inst;
		return inst;
	}

	~AssetManager();
	int  GetMesh(std::string meshFileName);           // ファイルからメッシュ（モデルハンドル）を得る
	int  GetAnimation(std::string animationFileName); // ファイルからアニメーションハンドルを得る
	void RemoveMesh(int meshID);                      // メッシュID(モデルハンドル)の登録解除＆開放する
	void RemoveAll();                                 // すべて解放する

private:
	AssetManager();                                   // シングルトン

	std::unordered_map<std::string, int> mMeshMap;    // メッシュ原本（こちらは原本として保存だけ行い、Duplicateされたものを返す）
	std::unordered_map<std::string, int> mAnimMap;    // アニメーション原本（こちらは返す)
	std::vector<int> mDuplicatesMesh;                 // メッシュをコピーしたもの（こちらを使用する）
};

// GetInstanceの省略形
#define ASSET AssetManager::GetInstance()
