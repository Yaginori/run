//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)		
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetGraphMode(1280, 1024, 16);
	ChangeWindowMode(TRUE);


	// プレイヤーを生成.
	Player* player = new Player();

	// カメラを生成.
	Camera* camera = new Camera();


	// 障害物を生成.
	StageManager* stageManager = new StageManager();
	stageManager->CreateStages();

	Enemy* enemy = new Enemy();
	enemy->CreateEnemys();

	// 時間計測
	int nowTime  = GetNowCount();
	int prevTime = nowTime;

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム時間を算出
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime)/ 1000.0f;

		char buf[256];
		//sprintf(buf, "deltaTime[%5.4f]", deltaTime);

		// プレイヤー制御.
		player->Update(deltaTime);

		// カメラ制御.
		camera->Update(*player);

		// 障害物制御.
		stageManager->Update(deltaTime);

		enemy->Update(deltaTime);

		// ヒットのチェック.
		HitChecker::Check(*player, *enemy);

		// 画面を初期化する
		ClearDrawScreen();

		//DrawString(100, 100, buf, GetColor(255, 255, 255));

		// プレイヤー描画.
		player->Draw();

		// 障害物描画.
		stageManager->Draw();

		enemy->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		prevTime = nowTime;
	}

	// プレイヤーを削除.
	delete(player);

	// カメラを削除.
	delete(camera);

	// 障害物を削除.
	stageManager->DestroyStages();
	delete(stageManager);

	enemy->DestrooyEnemys();
	delete(enemy);

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}