#pragma once
#include <vector>

class Actor;
class IRenderer;
class Camera;
class APlayer;

using namespace std;

class Scene
{
public:
	virtual void Enter() = 0;
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	APlayer* GetPlayer();
	Camera* GetCamera();

protected:
	vector<Actor*> actors;
	vector<IRenderer*> renderers;

	APlayer* player;

	Camera* camera;
};

