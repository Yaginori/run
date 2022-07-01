#include "pch.h"
#include "Floor.h"

Floor::Floor(const VECTOR& in_pos, const int in_modelHandle, const bool in_isColijonFlag)
{
	m_pos = in_pos;
	m_modelHandle = in_modelHandle;

}

void Floor::Draw()
{
	MV1DrawModel(m_modelHandle);
}

