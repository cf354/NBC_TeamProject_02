#include "Entity\Player.h"

void Player::setExp(int n)
{
	exp = n;
	if (exp >= 100) {
		{
			for (int i = 0; i < exp / 100; i++)
			{
				LevelUp();
			}
			exp = exp % 100;
		}
	}
}

void Player::LevelUp()
{
	level++; 
	MAXhp += 10; 
	atk += 5; 
	def += 3;
}

