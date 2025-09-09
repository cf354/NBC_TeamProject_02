#pragma once
#include <vector>
#include <string>
#include "Common/Singleton.h"
#include "Map/Scene/Scene.h"

using namespace std;

class SceneManager : public Singleton<SceneManager>
{
public:
	void Init();
	void Update();
	void Render();

	void LoadScene(int sceneIdx);
	Scene* GetCurrentScene();

private:
	vector<Scene*> scenes;
	int currScene;
};

#define SCENE_MANAGER (SceneManager::GetInstance())
