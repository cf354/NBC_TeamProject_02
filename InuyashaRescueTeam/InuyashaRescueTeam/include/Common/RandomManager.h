#pragma once
#include <random>
#include <memory>
#include "Singleton.h"

using namespace std;

class RandomManager : public Singleton<RandomManager>
{
public:
	void Init();
	void SetSeed(unsigned int seed);
	unsigned int GetSeed();
	void SetCompletelyRandom();
	/// <summary>
	/// min이상 max미만 정수 반환
	/// </summary>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <returns></returns>
	int Range(int min, int max);
	float Range(float min, float max);
	double Range(double min, double max);

private:
	mt19937 engine;
	random_device rd;			// 완전 랜덤을 원할 때, engine의 seed를 rd에서 무작위 값으로 설정
	unsigned int seed;
};

#define RANDOM_MANAGER (RandomManager::GetInstance())
