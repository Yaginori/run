#include "pch.h"
#include "SceneBase.h"

SceneBase::SceneBase(Scene in_nowScene)
	:m_modelHandle(-1)
{

}

SceneBase::~SceneBase()
{
}

void SceneBase::Draw()
{
	MV1DrawModel(m_modelHandle);
}
