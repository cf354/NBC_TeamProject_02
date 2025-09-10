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

void Particle::TickActive()
{
    currentTick++;

    if (currentTick > deadTick)
    {
        Draw();
    }
}

void Particle::TickActive(std::vector<std::vector<ConsoleCellData>> data)
{
    currentTick++;

    if (currentTick > deadTick)
    {
        Draw(data);
    }
}

void Particle::Draw(std::vector<std::vector<ConsoleCellData>> _Data)
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

void Particle::Draw()
{
    if (isDead) return;
    if (currentTick > deadTick + 4) {
        isDead = true;
        RemoveParticle();
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
                DrawCellData(i, (j / 2));
            }
            tbColor(7, 0);
        }
    }

}

void Particle::DrawCellData(int x, int y)
{
    int X = spawnX + x;
    int Y = spawnY + y;
    GoToXY(X, Y);
    //tbColor(_BackGroundData[y][x].foregroundColor, _BackGroundData[y][x].backgroundColor);    
    tbColor(_BackGroundData[y][x].foregroundColor, ParticleColor::P_GREEN);
    std::wcout << _BackGroundData[y][x].character;
}

void Particle::DrawCellData(std::vector<std::vector<ConsoleCellData>> data, int x, int y)
{
    int X = spawnX + x;
    int Y = spawnY + y;
    GoToXY(X, Y);
    tbColor(data[Y - 2][X].foregroundColor, data[Y - 2][X].backgroundColor);
    //tbColor(data[Y - 2][X].foregroundColor, ParticleColor::P_GREEN);
    std::wcout << data[Y - 2][X].character;
}

void Particle::RemoveParticle()
{
    int currentDisplayX = spawnX;

    for (size_t y = 0; y < 2; y++)
    {
        currentDisplayX = spawnX;
        for (size_t x = 0; x < 5; x+=0)
        {
            GoToXY(currentDisplayX, spawnY + y);
            //tbColor(_BackGroundData[y][x].foregroundColor, _BackGroundData[y][x].backgroundColor);
            tbColor(_BackGroundData[y][x].foregroundColor, ParticleColor::P_RED);
            std::wcout << _BackGroundData[y][x].character;
            currentDisplayX += getConsoleCharWidth(_BackGroundData[y][x].character);
            x += getConsoleCharWidth(_BackGroundData[y][x].character);
        }
    }
}

void Particle::RemoveParticle(std::vector<std::vector<ConsoleCellData>> data)
{
    int currentDisplayX = spawnX;

    for (size_t y = spawnY; y < spawnY + 2; y++)
    {
        currentDisplayX = spawnX;
        for (size_t x = spawnX; x < spawnX + 5; x += 0)
        {
            GoToXY(currentDisplayX, y);
            tbColor(data[y - 2][x].foregroundColor, data[y - 2][x].backgroundColor);
            //tbColor(data[y - 2][x].foregroundColor, ParticleColor::P_RED);
            std::wcout << data[y - 2][x].character;
            currentDisplayX += getConsoleCharWidth(data[y - 2][x].character);
            x += getConsoleCharWidth(data[y - 2][x].character);
        }
    }
}
