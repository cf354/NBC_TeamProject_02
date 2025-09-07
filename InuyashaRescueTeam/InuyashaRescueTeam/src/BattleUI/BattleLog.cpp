#include "BattleUI/BattleLog.h"

void BattleLog::Draw()
{
    GoToXY(_spawnX, _spawnY);
    DrawUI();
    PrintLog();
}

void BattleLog::AddLog(std::string s)
{
    if (_log.size() > _height - 3) _log.pop();
    _log.push(s);
}

void BattleLog::PrintLog(std::string s)
{
    AddLog(s);
    PrintLog();
}

void BattleLog::SetUI()
{
    _UITop.append("┌");
    for (int i = 0; i < _width - 2; i++)
    {
        _UITop.append("─");
    }
    _UITop.append("┐");

    _UIMiddle.append("│");
    for (int i = 0; i < _width - 2; i++)
    {
        _UIMiddle.append(" ");
    }
    _UIMiddle.append("│");

    _UIBottom.append("└");
    for (int i = 0; i < _width - 2; i++)
    {
        _UIBottom.append("─");
    }
    _UIBottom.append("┘");
}

void BattleLog::DrawUI()
{
    GoToXY(_spawnX, _spawnY);
    std::cout << _UITop;
    for (int i = 0; i < _height - 1; i++)
    {
        GoToXY(_spawnX, _spawnY + i + 1);
        std::cout << _UIMiddle;
    }
    GoToXY(_spawnX, _spawnY + _height - 1);
    std::cout << _UIBottom;
}


void BattleLog::PrintLog()
{
    if (_log.empty()) return;
    DrawUI();

    std::queue<std::string> temp(_log);

    size_t size = temp.size();

    for (size_t i = 0; i < size; i++)
    {
        GoToXY(_spawnX + 1, _spawnY + 1 + i);
        std::cout << temp.front();
        temp.pop();
    }
}