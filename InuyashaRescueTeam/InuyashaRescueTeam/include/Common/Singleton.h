#pragma once

template <typename T>
class Singleton
{
public:
	static T* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
		return instance;
	}

	static void Destory()
	{
		if (instance != nullptr)
		{
			delete instance;
		}
		instance = nullptr;
	}

private:
	static T* instance;
};

template <typename T>
T* Singleton<T>::instance = nullptr;