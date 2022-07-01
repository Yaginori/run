//-----------------------------------------------------------------------------
// @brief  �q�b�g�`�F�b�N.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// @brief  �q�b�g�`�F�b�N����.
//-----------------------------------------------------------------------------
void HitChecker::Check(Player& player, Enemy& enemy)
{
	// Z����X���̓񎟌����W�Ƃ��Ă����蔻����s��.
	VECTOR yZeroPlayer = VGet(player.GetPos().x, player.GetPos().y, player.GetPos().z);
	bool isHit = true;

	// ��x�ł��Ԃ�������ʒu���ς��̂Ńq�b�g�v�Z�����Ȃ���.
	while (isHit)
	{
		isHit = false;

		for (int i = 0; i < LINE_STAGE_COL; i++)
		{
			for (int j = 0; j < LINE_STAGE_RAW; j++)
			{
				//�w��ԍ��̏�Q�����擾
				GameObject* obstruct = enemy.GetStage(j, i);
				if (obstruct != NULL)
				{
					VECTOR yZeroObstruct = VGet(obstruct->GetPos().x, obstruct->GetPos().y, obstruct->GetPos().z);

					// ���݂��̃|�W�V�����Ɣ��a�̋������d�Ȃ����瓖�����Ă��邱�ƂɂȂ�.(x�����ɂ���j
					VECTOR playerToObs = VSub(yZeroObstruct, yZeroPlayer);
					//printfDx("playerToObs:%f %f %f\n", playerToObs.x, playerToObs.y, playerToObs.z);
					if (VSize(playerToObs) < player.GetHitRadius() + obstruct->GetHitRadius())
					{
						//printfDx("Hit!");
						player.OnHitObstruct(*obstruct);
						isHit = true;
						break;
					}
				}
			}
			// �q�b�g���Ă���v���C���[�N���X�̃q�b�g�t���O��true�ɂ���
			if (isHit)
			{
				player.hitFlag = true;
				yZeroPlayer = VGet(player.GetPos().x, player.GetPos().y, player.GetPos().z);
				break;
			}
		}

		//��x�q�b�g�����烋�[�v���甲����
		if (player.hitFlag)
		{
			break;
		}

	}
}