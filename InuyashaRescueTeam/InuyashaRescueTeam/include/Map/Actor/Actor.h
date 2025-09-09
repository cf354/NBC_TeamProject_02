#pragma once
#include <string>
#include <vector>
#include "Map/Component/IComponent.h"
#include "Map/MapTypes.h"

using namespace std;
using namespace Map;

class IComponent;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update();

	void SetName(string name);
	void SetActive(bool isActive);
	void SetPos(Vector2D pos);

	string GetName() const;
	bool GetActive() const;
	Vector2D GetPos() const;

	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(is_base_of<IComponent, T>::value, "T must derive from IComponent");
		T* comp = new T(forward<Args>(args)...);
		comp->SetOwner(this);
		components.push_back(comp);
		return comp;
	}

	template <typename T>
	void RemoveComponent()
	{
		for (auto it = components.begin(); it < components.end(); it++)
		{
			T* casted = dynamic_cast<T*>(*it);
			if (casted != nullptr)
			{
				delete casted;
				components.erase(it);
				return;
			}
		}
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto* comp : components)
		{
			T * casted = dynamic_cast<T*>(comp);
			if (casted != nullptr)
			{
				return casted;
			}
		}
		return nullptr;
	}

	template <typename T>
	vector<T*> GetComponents()
	{
		vector<T*> result;
		for (auto* comp : components)
		{
			T* casted = dynamic_cast<T*>(comp);
			if (casted != nullptr)
			{
				result.push_back(casted);
			}
		}
		return result;
	}

protected:
	string name;
	bool isActive;
	Vector2D pos;				// Actor는 모든 위치 중하단으로 설정
	vector<IComponent*> components;
};

