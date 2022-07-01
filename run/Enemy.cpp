


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
	// ���f���̃A�����[�h.
	for (int i = 0; i < LINE_ENEMY_RAW; i++)
	{
		for (int j = 0; j < LINE_ENEMY_COL; j++)
		{
			ASSET.RemoveMesh(m_enemyModelHandle); //MV1DeleteModel(m_modelHandle);
		}
	};
}

//-----------------------------------------------------------------------------
// @brief  �X�V.
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
// @brief  �`��.
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
	// �R�c���f���̓ǂݍ���
	m_enemyModelHandle = MV1LoadModel("data/model/enemy/Chicky.mv1");


	// ��Q���̔z�u�}�f�[�^�Ƃ��Ă�linemap��p�ӂ���.
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

			// linemap�ɓ����Ă��鐔�l�ɂ���ď�Q���̎�ނ����肷��.
			if (nowLine[j] == 1)
			{
				scale = VGet(0.5f, 0.5f, 0.5f);
				enemys[i][j] = new ObstructStatic(m_enemyModelHandle,scale);
			}
			else
			{
				enemys[i][j] = NULL;
			}

			// �ʒu�̏�����.
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
// @brief  �w��ԍ��̏�Q�����擾.
//-----------------------------------------------------------------------------
GameObject* Enemy::GetStage(int raw, int col)
{
	return enemys[raw][col];
}
