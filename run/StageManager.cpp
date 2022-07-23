//-----------------------------------------------------------------------------
// @brief  ��Q���}�l�[�W���[.
//-----------------------------------------------------------------------------

//���g�̃C���X�^���X������
StageManager* StageManager::mManager = nullptr;

//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
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
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------
StageManager::~StageManager()
{
	// �����Ȃ�.
}


//-----------------------------------------------------------------------------
// @brief  ��Q������.
//-----------------------------------------------------------------------------
void StageManager::CreateStages()
{
	staticModelSourceHandle = MV1LoadModel("data/model/stage/wall/House.mv1");

	// ��Q���̔z�u�}�f�[�^�Ƃ��Ă�linemap��p�ӂ���.
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
			// linemap�ɓ����Ă��鐔�l�ɂ���ď�Q���̎�ނ����肷��.
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

			// �ʒu�̏�����.
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
// @brief  ��Q���폜.
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
				// �R�c���f���̃X�P�[����13�{�ɂ���
				//MV1SetScale(m_modelHandle, scale);

				// �RD���f���̃|�W�V�����ݒ�
				//MV1SetPosition(m_modelHandle, pos);

				Obstructs[i][j]->Update(deltaTime);

			}
		}
	}

}

//-----------------------------------------------------------------------------
// @brief  �`��.
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
// @brief  �w��ԍ��̏�Q�����擾.
//-----------------------------------------------------------------------------
GameObject* StageManager::GetStage(int raw, int col)
{
	return Obstructs[raw][col];
}

//�I�I���C�����[�v�ŌĂяo������
void StageManager::CreateInstance()
{
	if (mManager == nullptr)
	{
		//�C���X�^���X����
		mManager = new StageManager();
	}

}

// �I�I���C�����[�v�ŌĂяo������
void StageManager::DeleteInstance()
{
	// �v��Ȃ��Ȃ����X�e�[�W���폜
	for (auto Stage : mManager->mObject)
	{
		delete Stage;
	}

	if (mManager != nullptr)
	{
		// �폜
		delete mManager;
		mManager = nullptr;
	}

}

