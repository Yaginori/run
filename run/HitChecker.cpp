//-----------------------------------------------------------------------------
// @brief  ヒットチェック.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// @brief  ヒットチェック処理.
//-----------------------------------------------------------------------------
void HitChecker::Check(Player& player, Enemy& enemy)
{
	// Z軸とX軸の二次元座標としてあたり判定を行う.
	VECTOR yZeroPlayer = VGet(player.GetPos().x, player.GetPos().y, player.GetPos().z);
	bool isHit = true;

	// 一度でもぶつかったら位置が変わるのでヒット計算をしなおす.
	while (isHit)
	{
		isHit = false;

		for (int i = 0; i < LINE_STAGE_COL; i++)
		{
			for (int j = 0; j < LINE_STAGE_RAW; j++)
			{
				//指定番号の障害物を取得
				GameObject* obstruct = enemy.GetStage(j, i);
				if (obstruct != NULL)
				{
					VECTOR yZeroObstruct = VGet(obstruct->GetPos().x, obstruct->GetPos().y, obstruct->GetPos().z);

					// お互いのポジションと半径の距離が重なったら当たっていることになる.(xだけにする）
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
			// ヒットしてたらプレイヤークラスのヒットフラグをtrueにする
			if (isHit)
			{
				player.hitFlag = true;
				yZeroPlayer = VGet(player.GetPos().x, player.GetPos().y, player.GetPos().z);
				break;
			}
		}

		//一度ヒットしたらループから抜ける
		if (player.hitFlag)
		{
			break;
		}

	}
}