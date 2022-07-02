#pragma once
class SceneManager
{
public:
	SceneManager(SceneBase::Scene in_nowScene);
	~SceneManager();
	void SceneChange();

private:
	int m_testSceneCnt;
};

