#include "BattleUI/Particle.h"

void Particle::Spawn()
{
    for (size_t i = 0; i < 4; i += 2)
    {
        for (size_t j = 0; j < 5; j++)
        {
            GoToXY(spawnX + j, spawnY + (i / 2));

            if (data[0][i][j] && data[0][i + 1][j])
            {
                printGround(j, i, _Color);
            }
            else if ((!data[0][i][j]) && data[0][i + 1][j])
            {
                printHalfBlock(j, i, _Color);
            }
            else if (data[0][i][j] && !(data[0][i + 1][j]))
            {
                printBlock(j, i, _Color);
            }
            tbColor(7, 0);
        }
    }

    isDead = false;
}

void Particle::TickActive(vector<vector<ConsoleCellData>> data)
{
    currentTick++;

    if (currentTick > deadTick)
    {
        Draw(data);
    }
}

void Particle::Draw(vector<vector<ConsoleCellData>> _Data)
{
    if (isDead) return;
    if (currentTick > deadTick + 4) {
        isDead = true;
        RemoveParticle(_Data);
        return;
    }

    bool(&cunetData)[5][5] = data[currentTick - deadTick];

    for (size_t j = 0; j < 4; j += 2)
    {
        for (size_t i = 0; i < 5; i++)
        {
            GoToXY(spawnX + i, spawnY + (j / 2));

            if (cunetData[j][i] && cunetData[j + 1][i])
            {
                printGround(i, j, _Color);
            }
            else if ((!cunetData[j][i]) && cunetData[j + 1][i])
            {
                printHalfBlock(i, j, _Color);
            }
            else if (cunetData[j][i] && !(cunetData[j + 1][i]))
            {
                printBlock(i, j, _Color);
            }
            else {
                DrawCellData(_Data, i, (j / 2));
            }
            tbColor(7, 0);
        }
    }

}

void Particle::DrawCellData(vector<vector<ConsoleCellData>> data, int x, int y)
{
    int X = spawnX + x;
    int Y = spawnY + y;
    GoToXY(X, Y);
    tbColor(data[Y][X].foregroundColor, data[Y][X].backgroundColor);
    wcout << data[Y][X].character;
}

void Particle::RemoveParticle(vector<vector<ConsoleCellData>> data)
{
    int currentDisplayX = spawnX;

    for (size_t y = spawnY; y < spawnY + 4; y++)
    {
        currentDisplayX = spawnX;
        for (size_t x = spawnX; x < spawnX + 5; x += 0)
        {
            GoToXY(currentDisplayX, y);
            tbColor(data[y][x].foregroundColor, data[y][x].backgroundColor);
            std::wcout << data[y][x].character;
            currentDisplayX += getConsoleCharWidth(data[y][x].character);
            x += getConsoleCharWidth(data[y][x].character);
        }
    }
}
