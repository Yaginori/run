


Enemy::Enemy()
	: mAnimControl(nullptr)
{

	//pos = VGet(0, 0, 0);

	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			enemys[i][j] = NULL;
		}
	}

}

Enemy::~Enemy()
{
	// モデルのアンロード.
	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			ASSET.RemoveMesh(m_enemyModelHandle); //MV1DeleteModel(m_modelHandle);
		}
	};
}

//-----------------------------------------------------------------------------
// @brief  更新.
//-----------------------------------------------------------------------------
void Enemy::Update(float deltaTime)
{
	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			if (enemys[i][j] != NULL)
			{
				enemys[i][j]->Update(deltaTime);

			}
		}
	}
}

//-----------------------------------------------------------------------------
// @brief  描画.
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			if (enemys[i][j] != NULL)
			{
				
				enemys[i][j]->Draw();

			}
		}
	}
}

void Enemy::CreateEnemys()
{
	// ３Ｄモデルの読み込み
	m_enemyModelHandle = MV1LoadModel("data/model/enemy/Chicky.mv1");


	// 障害物の配置図データとしてのlinemapを用意する.
	int line1[LINE_ENEMY_COL] = { 0,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0 };
	int line2[LINE_ENEMY_COL] = { 0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0 };
	int line3[LINE_ENEMY_COL] = { 0,0,0,0,0,0,0,0,0,0,	1,1,1,1,1,1,1,1,1,1,	1,1,1,1,1,1,1,1,1,1 };

	int* lineMap[LINE_ENEMY_RAW] =
	{
		line1,	// 1
		line2,	// 2
		line3	// 3
	};

	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		int* nowLine = lineMap[i];
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{

			// linemapに入っている数値によって障害物の種類を決定する.
			if (nowLine[j] == 1)
			{
				scale = VGet(0.5f, 0.5f, 0.5f);
				enemys[i][j] = new ObstructStatic(m_enemyModelHandle,scale);
			}
			else
			{
				enemys[i][j] = NULL;
			}

			// 位置の初期化.
			if (enemys[i][j] != NULL)
			{
				enemys[i][j]->SetPos(
					VGet(
						(ENEMY_SPACE_W * j) - (ENEMY_SPACE_W * LINE_ENEMY_COL * 0.5f),
						-10.0f,
						(ENEMY_SPACE_D * LINE_ENEMY_RAW) - (ENEMY_SPACE_D * i)
					)
				);
			}
		}
	}

}

void Enemy::DestrooyEnemys()
{

	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			if (enemys[i][j] != NULL)
			{

				delete(enemys[i][j]);
				enemys[i][j] = NULL;

			}
		}
	}

		MV1DeleteModel(m_enemyModelHandle);
}

//-----------------------------------------------------------------------------
// @brief  指定番号の障害物を取得.
//-----------------------------------------------------------------------------
GameObject* Enemy::GetStage(int raw, int col)
{
	return enemys[raw][col];
}
