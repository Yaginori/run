#pragma once
#include <DxLib.h>
#include <string>
#include <unordered_map>
class Player;

class AnimationController
{
public:
	AnimationController(int m_modelHandle);
	~AnimationController();

	int AddAnimation(std::string animFileName, float animFps, bool isLoop );

	void AddAnimTime(float deltaTime);            // アニメーション時間のセット
	void StartAnimation(int animID);              // アニメーションの再生開始
	void StopAnimation();                         // アニメーションの再生をストップ
	bool IsPlaying();                             // 現在再生中か

	// アニメーションデータ用構造体 アニメーション1個分
	typedef struct AnimData
	{
		int   mAnimHandle;                        // アニメーションハンドル
		int   mAnimIndex;                         // アタッチするアニメーション番号
		float mAnimTotalTime;                     // このアニメの総再生時間
		float mAnimFps;                           // アニメーション再生速度
		bool  mIsLoop;                            // ループ再生を許可するか
	}AnimData;

private:
	int   m_modelHandle;
	std::vector<AnimData> mAnimDatas;             // アニメーション複数登録用
	int   mNowAnimTypeNum;                        // 現在再生中のアニメーションID
	int   mAttachedIndex;                         // 取付後のインデックス
	float mNowAnimTime;                           // 現在再生中のアニメーション時刻
	Player* player;
};