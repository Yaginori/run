//-----------------------------------------------------------------------------
// @brief  障害物マネージャー.
//-----------------------------------------------------------------------------

//自身のインスタンス初期化
StageManager* StageManager::mManager = nullptr;

//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
StageManager::StageManager()
	: floatModelSourceHandle(-1)
	, staticModelSourceHandle(-1)
{
	for (int i = 0; i < LINE_STAGE_RAW; i++)
	{
		for (int j = 0; j < LINE_STAGE_COL; j++)
		{
			Obstructs[i][j] = NULL;
		}
	}
}


//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------
StageManager::~StageManager()
{
	// 処理なし.
}


//-----------------------------------------------------------------------------
// @brief  障害物生成.
//-----------------------------------------------------------------------------
void StageManager::CreateStages()
{
	staticModelSourceHandle = MV1LoadModel("data/model/stage/wall/House.mv1");

	// 障害物の配置図データとしてのlinemapを用意する.
	int line1[LINE_STAGE_COL] = { 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0 };
	int line2[LINE_STAGE_COL] = { 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 };
	int line3[LINE_STAGE_COL] = { 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1 };
													   
	int* lineMap[LINE_STAGE_RAW] =
	{
		line1,	// 1
		line2,	// 2
		line3	// 3
	};

	for (int i = 0; i < LINE_STAGE_RAW; i++)
	{
		int* nowLine = lineMap[i];
		for (int j = 0; j < LINE_STAGE_COL; j++)
		{
			// linemapに入っている数値によって障害物の種類を決定する.
			if (nowLine[j] == 1)
			{

				scale=VGet(0.0f, 0.0f, 0.0f);
				//Obstructs[i][j] = new GameObject(staticModelSourceHandle);
				Obstructs[i][j] = new ObstructStatic(staticModelSourceHandle, scale);
			}
			else
			{
				Obstructs[i][j] = NULL;
			}

			// 位置の初期化.
			if (Obstructs[i][j] != NULL)
			{
				Obstructs[i][j]->SetPos(
					VGet(
						(STAGE_SPACE_W * j) - (STAGE_SPACE_W * LINE_STAGE_COL * 0.5f),  //x
						-230.0f,														//y
						(STAGE_SPACE_D * LINE_STAGE_RAW) - (STAGE_SPACE_D * i)          //z
					)
				);
			}
		}
	}
}


//-----------------------------------------------------------------------------
// @brief  障害物削除.
//-----------------------------------------------------------------------------
void StageManager::DestroyStages()
{

	for (int i = 0; i < LINE_STAGE_RAW; i++)
	{
		for (int j = 0; j < LINE_STAGE_COL; j++)
		{
			if (Obstructs[i][j] != NULL)
			{

				delete(Obstructs[i][j]);
				Obstructs[i][j] = NULL;

			}
		}
	}
	MV1DeleteModel(staticModelSourceHandle);
}


void StageManager::Update(float deltaTime)
{
	for (int i = 0; i < LINE_STAGE_RAW; i++)
	{
		for (int j = 0; j < LINE_STAGE_COL; j++)
		{
			if (Obstructs[i][j] != NULL)
			{
				// ３Ｄモデルのスケールを13倍にする
				//MV1SetScale(m_modelHandle, scale);

				// ３Dモデルのポジション設定
				//MV1SetPosition(m_modelHandle, pos);

				Obstructs[i][j]->Update(deltaTime);

			}
		}
	}

}

//-----------------------------------------------------------------------------
// @brief  描画.
//-----------------------------------------------------------------------------
void StageManager::Draw()
{
	for (int i = 0; i < LINE_STAGE_RAW; i++)
	{
		for (int j = 0; j < LINE_STAGE_COL; j++)
		{
			if (Obstructs[i][j] != NULL)
			{
				Obstructs[i][j]->Draw();

			}
		}
	}
}


//-----------------------------------------------------------------------------
// @brief  指定番号の障害物を取得.
//-----------------------------------------------------------------------------
GameObject* StageManager::GetStage(int raw, int col)
{
	return Obstructs[raw][col];
}

//！！メインループで呼び出そうな
void StageManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		//インスタンス生成
		mManager = new StageManager();
	}

}

// ！！メインループで呼び出そうな
void StageManager::DeleteInstance()
{
	// 要らなくなったステージを削除
	for (auto Stage : mManager->mObject)
	{
		delete Stage;
	}

	if (mManager != nullptr)
	{
		// 削除
		delete mManager;
		mManager = nullptr;
	}

}

