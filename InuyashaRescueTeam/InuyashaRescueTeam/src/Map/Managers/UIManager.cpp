#include "Map/Managers/UIManager.h"
#include "Map/UI/UI.h"
#include "Map/UI/UIPlayerStatus.h"

void UIManager::Init()
{
    UIPlayerStatus* uiPlayerStatus = new UIPlayerStatus();
    uiPlayerStatus->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(2, 2));
    AddUI(uiPlayerStatus);
}

void UIManager::Update()
{
	for (int i = 0; i < uis.size(); i++)
	{
		uis[i]->Update();
	}
}

void UIManager::Render()
{
	for (int i = 0; i < uis.size(); i++)
	{
        uis[i]->Render();
	}
}

void UIManager::Release()
{
    for (int i = 0; i < uis.size(); i++)
    {
        delete uis[i];
    }
    uis.clear();
}

void UIManager::AddUI(UI* ui)
{
	uis.push_back(ui);
}

void UIManager::RemoveUI(UI* ui)
{
	uis.erase(find(uis.begin(), uis.end(), ui));
    delete ui;
}
