#include "pch.h"
#include "Floor.h"

Floor::Floor(const VECTOR& in_pos, const int in_modelHandle, const bool in_isColijonFlag)
{
	m_pos = in_pos;
	m_modelHandle = in_modelHandle;
	MV1SetScale(in_modelHandle, VGet(13.0f, 13.0f, 13.0f));
}

void Floor::Draw()
{
	MV1DrawModel(m_modelHandle);
}

