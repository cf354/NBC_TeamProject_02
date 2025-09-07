#pragma once
#include "UIWidget.h"
#include <string>
#include <queue>

class BattleLog : public UIWidget
{
public:
    BattleLog(int width, int height, int spawnX, int spawnY) : UIWidget(width, height, spawnX, spawnY) {
        SetUI();
    }

    BattleLog(int width, int height) : UIWidget(width, height) {
        SetUI();
    }

private:
    std::queue<std::string> _log;
    std::string _UITop;
    std::string _UIMiddle;
    std::string _UIBottom;

public:
    virtual void Draw() override;
    void AddLog(std::string s);
    void PrintLog(std::string s);

private:
    void SetUI();
    void DrawUI();
    void PrintLog();
};
