
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
AssetManager::AssetManager()
{
}

//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
AssetManager::~AssetManager()
{
}

//-----------------------------------------------------------------------------
// @brief  メッシュの取得.
// @param[in] meshFileName 取得したいメッシュファイル名.
// @return int メッシュのハンドル.
// 
// @details メッシュ（モデル)ハンドルを取得する。
// 同じファイル名を2度以上指定したときは、ファイル読み込みは行われず、duplicateされたハンドルを返す。
// ファイルが見つからないときは-1を返す.
//-----------------------------------------------------------------------------
int AssetManager::GetMesh(std::string meshFileName)
{
	int meshId = 0;
	// 連想配列から以前に登録されてないかを調べる
	auto iter = mMeshMap.find(meshFileName);

	// 見つからなかった場合は新規でファイルを読み込み、連想配列に記録する
	if (iter == mMeshMap.end())
	{
		meshId = MV1LoadModel(meshFileName.c_str());
		if (meshId == -1)
		{
			return meshId;
		}
		mMeshMap.emplace(meshFileName, meshId); //mMeshMap[meshFileName] = meshIdのこと
	}

	// 新規読み込みも2回目読み込みも、duplicateしたものを返却する
	// メッシュを使うキャラクターが複数いた場合に、原本を消されると全員消えて困るから
	// メッシュのコピー削除用にmDuplicateMeshに保存
	meshId = MV1DuplicateModel(mMeshMap[meshFileName]);
	mDuplicatesMesh.push_back(meshId);

	return meshId;
}

//-----------------------------------------------------------------------------
// @brief  アニメーションの読み込み.
// @param[in] animationFileName 読み込みたいアニメーションファイル名.
// @return int アニメーションハンドル.
// 
// @details アニメーションをファイル読み込みし、アニメーションハンドルを返す
// 同じファイル名で2度以上読み込まれた場合は、読み込みを行わずハンドルのみ返す
// アニメーションはDuplicateされない。ファイルが見つからないときは-1を返す.         
//-----------------------------------------------------------------------------
int AssetManager::GetAnimation(std::string animationFileName)
{
	int animId = 0;
	auto iter = mAnimMap.find(animationFileName);

	// 見つからなかった場合は新規読み込みし、連想配列に記録する
	if (iter == mAnimMap.end())
	{
		animId = MV1LoadModel(animationFileName.c_str());
		if (animId == -1)
		{
			return animId;
		}
		mAnimMap.emplace(animationFileName, animId);  // mAnimMap[animationFileName] = animId;のこと
	}

	// アニメーションのIDを返す
	return mAnimMap[animationFileName];
}

//-----------------------------------------------------------------------------
// @brief  メッシュの解放
// @param[in] meshID 解放したいモデルハンドル.
// 
// @details duplicateされたモデルハンドルを開放する
// duplicateされたモデルハンドルなので、全部消しても原本のモデルハンドルは内部的に残る         
//-----------------------------------------------------------------------------
void AssetManager::RemoveMesh(int meshID)
{
	// Duplicateの中でメッシュを検索し、削除
	auto iter = std::find(mDuplicatesMesh.begin(), mDuplicatesMesh.end(), meshID);
	if (iter == mDuplicatesMesh.end())
	{
		return;
	}

	MV1DeleteModel(meshID);

	// 末尾のデータと入れ替えて末尾を削除
	std::iter_swap(iter, mDuplicatesMesh.end() - 1);
	mDuplicatesMesh.pop_back();
}

//-----------------------------------------------------------------------------
// @brief  　すべてのメッシュの解放
// 
// @details duplicate, 原本のモデルハンドル、アニメーションすべてを開放する
// アプリケーションの終了時にdxLib_End()より前に呼び出す必要がある。.
//-----------------------------------------------------------------------------
void AssetManager::RemoveAll()
{
	// 全てのアニメーションを開放する
	for (auto iter = mAnimMap.begin(); iter != mAnimMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	// 全てのモデルを開放する
	for (auto iter = mMeshMap.begin(); iter != mMeshMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	// 全てのDuplicateを削除する
	for (auto iter = mDuplicatesMesh.begin(); iter != mDuplicatesMesh.end(); ++iter)
	{
		MV1DeleteModel(*iter);
	}

	mAnimMap.clear();
	mMeshMap.clear();
	mDuplicatesMesh.clear();
}
