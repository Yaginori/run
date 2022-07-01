#pragma once
#include "SceneBase.h"
class GameScene :
    public SceneBase
{
public:
    GameScene();
    ~GameScene();

    SceneBase* Update(float _deltaTime);
    void Draw();

private:
    class Player* m_player;
    class Map* m_map;
    class AnimationController* m_animationController;

};

