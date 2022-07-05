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
    void Load();

private:
    class Player* m_player;
    class Map* m_map;
    class Camera* m_camera;

    bool m_SceneChangeFlag;

};

