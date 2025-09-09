#include "Map/Scene/Scene.h"
#include "Map/Actor/Actor.h"
#include "Map/Component/IRenderer.h"
#include "Map/Camera.h"
#include <algorithm>

void Scene::Update()
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->GetActive())
		{
			actors[i]->Update();
		}
	}

	if (camera != nullptr)
	{
		camera->Update();
	}
}

void Scene::Render()
{
	sort(renderers.begin(), renderers.end(),
		[](const IRenderer* r1, const IRenderer* r2)
		{
			// sortOrder 낮은 순
			if (r1->sortOrder != r2->sortOrder)
				return r1->sortOrder < r2->sortOrder;

			// 액터 pos.y 낮은 순 (더 위에 있을 수록 빨리 렌더링)
			return r1->GetOwner()->GetPos().y < r2->GetOwner()->GetPos().y;
		});
	for (int i = 0; i < renderers.size(); i++)
	{
		if (renderers[i]->GetOwner()->GetActive())
		{
			renderers[i]->Render();
		}
	}
}

void Scene::Exit()
{
	for (int i = 0; i < actors.size(); i++)
	{
		delete actors[i];
	}
	actors.clear();
	renderers.clear();
	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}
}

void Scene::AddActor(Actor* actor)
{
	actors.push_back(actor);
	IRenderer* renderer = actor->GetComponent<IRenderer>();
	if (renderer != nullptr)
	{
		renderers.push_back(renderer);
	}
}

void Scene::RemoveActor(Actor* actor)
{
	auto* renderer = actor->GetComponent<IRenderer>();
	actors.erase(find(actors.begin(), actors.end(), actor));
	renderers.erase(find(renderers.begin(), renderers.end(), renderer));
    delete actor;
}

APlayer* Scene::GetPlayer()
{
	return player;
}

Camera* Scene::GetCamera()
{
	return camera;
}
