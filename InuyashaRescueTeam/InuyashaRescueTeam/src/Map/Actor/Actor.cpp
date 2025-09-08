#include "Map/Actor/Actor.h"

Actor::Actor()
	: name(""), isActive(true), pos()
{
}

Actor::~Actor()
{
	for (int i = 0; i < components.size(); i++)
	{
		delete components[i];
	}
	components.clear();
}

void Actor::Update()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update();
	}
}

void Actor::SetName(string name)
{
	this->name = name;
}

void Actor::SetActive(bool isActive)
{
	this->isActive = isActive;
}

void Actor::SetPos(Vector2D pos)
{
	this->pos = pos;
}

string Actor::GetName() const
{
	return name;
}

bool Actor::GetActive() const
{
	return isActive;
}

Vector2D Actor::GetPos() const
{
	return pos;
}
