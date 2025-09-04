#include "Entity\Entity.h"

void Entity::SetStamina(int n)
{
	if (n > MAXstamina) { stamina = MAXstamina; }
	else if (n < 0) { stamina = 0; }
	else { stamina = n; }

}

void Entity::SetHP(int n)
{
	if (n > MAXhp) { hp = MAXhp; }
	else if (n < 0) { hp = 0; }
	else { hp = n; }
}

void Entity::TakeDamage(int dmg)
{
	if (dmg < 0) dmg = 0;
	hp -= dmg;
	if (hp < 0) hp = 0;
}
