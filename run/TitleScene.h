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
    void Load();

private:
   int m_ScenetestGraph;
   bool m_SceneChangeFlag;
};

