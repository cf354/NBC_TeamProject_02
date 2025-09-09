#include "Map/Component/IComponent.h"

void IComponent::SetOwner(Actor* owner)
{
	this->owner = owner;
}

Actor* IComponent::GetOwner() const
{
	return owner;
}
