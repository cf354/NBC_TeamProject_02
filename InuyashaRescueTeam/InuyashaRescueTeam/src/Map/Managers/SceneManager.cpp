#include "Map/Managers/SceneManager.h"
#include "Map/Scene/GameScene.h"

void SceneManager::Init()
{
	scenes.push_back(new GameScene());
	LoadScene(0);
}

void SceneManager::Update()
{
	scenes[currScene]->Update();
}

void SceneManager::Render()
{
	scenes[currScene]->Render();
}

void SceneManager::LoadScene(int sceneIdx)
{
	if (sceneIdx < 0 || sceneIdx >= scenes.size())
		return;

	scenes[currScene]->Exit();
	currScene = sceneIdx;
	scenes[currScene]->Enter();
}

Scene* SceneManager::GetCurrentScene()
{
	return scenes[currScene];
}