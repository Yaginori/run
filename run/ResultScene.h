#pragma once
#include "SceneBase.h"
class ResultScene :
    public SceneBase
{
public:
    ResultScene();
    ~ResultScene();

    SceneBase* Update(float _deltaTime);
    void Draw();
    void Load();

private:
    int m_ScenetestGraph;
    bool m_SceneChangeFlag;

};

