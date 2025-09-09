#pragma once
#include <vector>
#include "Common/Singleton.h"

using namespace std;

class UI;

class UIManager : public Singleton<UIManager>
{
public:
	void Init();
	void Update();
	void Render();
    void Release();

	void AddUI(UI* ui);
	void RemoveUI(UI* ui);

private:
	vector<UI*> uis;
};

#define UI_MANAGER (UIManager::GetInstance())
