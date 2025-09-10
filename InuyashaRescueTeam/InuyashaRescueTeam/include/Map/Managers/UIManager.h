#pragma once
#include <vector>
#include "Common/Singleton.h"

using namespace std;

class UI;
class UIInventory;

class UIManager : public Singleton<UIManager>
{
public:
	void Init();
	void Update();
	void Render();
    void Release();

	void AddUI(UI* ui);
	void RemoveUI(UI* ui);

    void ShowInventory(bool show);
    void SwitchInventory();

private:
	vector<UI*> uis;

    UIInventory* uiInventory;       // 원래는 UIManager를 상속하거나 씬별 UI를 따로 관리하게 해야 하는데, 마감까지 촉박하므로 여기 배치
};

#define UI_MANAGER (UIManager::GetInstance())
