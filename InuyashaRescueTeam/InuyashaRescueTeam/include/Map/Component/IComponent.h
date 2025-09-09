#pragma once
class Actor;

class IComponent
{
public:
	virtual void Update() = 0;

	void SetOwner(Actor* owner);
	Actor* GetOwner() const;

protected:
	Actor* owner;
};

