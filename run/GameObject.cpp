#include "GameObject.h"

#define USE_MODEL_DUPLICATE 1


GameObject::GameObject(int sourcem_modelHandle, VECTOR in_setPos)
	:hitRadius(5.0f)
	,m_modelHandle(-1)
	,m_pos(in_setPos)
{

	// �R�c���f���̓ǂݍ���
#if USE_MODEL_DUPLICATE
	m_modelHandle = MV1DuplicateModel(sourcem_modelHandle);
	if (m_modelHandle < 0)
	{
		printfDx("�f�[�^�ǂݍ��݂Ɏ��s. sourceId:%d", sourcem_modelHandle);
	}
#else
	m_modelHandle = MV1LoadModel("data/model/stage/wall/House.mv1");
	if (m_modelHandle < 0)
	{
		printfDx("ObstructStatic:�f�[�^�ǂݍ��݂Ɏ��s");
	}
#endif

}


GameObject::GameObject()
	: hitRadius(0.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw()
{
	MV1DrawModel(m_modelHandle);
}
