#include "Map/Managers/UIManager.h"
#include "Map/UI/UI.h"
#include "Map/UI/UIPlayerStatus.h"
#include "Map/UI/UIInventory.h"
#include <Windows.h>
#include "InputManager/InputManager.h"

void UIManager::Init()
{
    UIPlayerStatus* uiPlayerStatus = new UIPlayerStatus();
    uiPlayerStatus->SetPosition(Anchor::LT, Vector2F(0.0f, 0.0f), Vector2D(2, 2));
    AddUI(uiPlayerStatus);

    uiInventory = new UIInventory();
    uiInventory->SetActive(false);
    uiInventory->SetPosition(Anchor::CM, Vector2F(0.5f, 0.5f), Vector2D(0, 0));
    AddUI(uiInventory);
}

void UIManager::Update()
{
    if (InputManager::GetInstance().GetKeyAction(GameState::FIELD) == KeyAction::INVENTORY)
    {
        SwitchInventory();
    }

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

void UIManager::ShowInventory(bool show)
{
    if (uiInventory != nullptr)
    {
        uiInventory->SetActive(show);
        if (show)
        {
            uiInventory->SetData();
        }
    }
}

void UIManager::SwitchInventory()
{
    if (uiInventory == nullptr)
        return;
    ShowInventory(!uiInventory->GetActive());
}
