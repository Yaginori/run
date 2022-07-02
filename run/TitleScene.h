#pragma once
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:
    TitleScene();
    ~TitleScene();

    SceneBase* Update(float _deltaTime);
    void Draw();

private:
   int m_ScenetestGraph;
   int m_SceneTestCnt;
};

