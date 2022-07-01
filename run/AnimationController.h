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

	void AddAnimTime(float deltaTime);            // �A�j���[�V�������Ԃ̃Z�b�g
	void StartAnimation(int animID);              // �A�j���[�V�����̍Đ��J�n
	void StopAnimation();                         // �A�j���[�V�����̍Đ����X�g�b�v
	bool IsPlaying();                             // ���ݍĐ�����

	// �A�j���[�V�����f�[�^�p�\���� �A�j���[�V����1��
	typedef struct AnimData
	{
		int   mAnimHandle;                        // �A�j���[�V�����n���h��
		int   mAnimIndex;                         // �A�^�b�`����A�j���[�V�����ԍ�
		float mAnimTotalTime;                     // ���̃A�j���̑��Đ�����
		float mAnimFps;                           // �A�j���[�V�����Đ����x
		bool  mIsLoop;                            // ���[�v�Đ��������邩
	}AnimData;

private:
	int   m_modelHandle;
	std::vector<AnimData> mAnimDatas;             // �A�j���[�V���������o�^�p
	int   mNowAnimTypeNum;                        // ���ݍĐ����̃A�j���[�V����ID
	int   mAttachedIndex;                         // ��t��̃C���f�b�N�X
	float mNowAnimTime;                           // ���ݍĐ����̃A�j���[�V��������
	Player* player;
};