#include "Common/RandomManager.h"

void RandomManager::SetSeed(unsigned int seed)
{
	this->seed = seed;
	engine.seed(seed);
}

unsigned int RandomManager::GetSeed()
{
	return seed;
}

void RandomManager::SetCompletelyRandom()
{
	SetSeed(rd());
}

int RandomManager::Range(int min, int max)
{
	uniform_int_distribution<int> dist(min, max - 1);
	return dist(engine);
}

float RandomManager::Range(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(engine);
}

double RandomManager::Range(double min, double max)
{
	uniform_real_distribution<double> dist(min, max);
	return dist(engine);
}
