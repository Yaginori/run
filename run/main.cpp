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

	// 現在のシーンを生成
	SceneManager* nowScene=new SceneManager();

	nowScene->SetScene(new TitleScene);


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

		// シーン制御
		nowScene->Update(deltaTime);

		// 画面を初期化する
		ClearDrawScreen();

		// 描画
		nowScene->Draw();

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		prevTime = nowTime;
	}

	// シーン削除
	delete(nowScene);

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}