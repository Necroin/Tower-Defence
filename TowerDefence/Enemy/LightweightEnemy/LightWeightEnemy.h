#pragma once
#ifndef _LIGHTWEIGHTENEMY_H_
#define _LIGHTWEIGHTENEMY_H_
#include "../Enemy.h"

class LightWeightEnemy : public Enemy
{
private:
	virtual void attack(Cell* tagret_cell) override;
	virtual void go() override;

	virtual Cell* find_target() override;

public:
	LightWeightEnemy(COORD coordinates, size_t HP, size_t Max_HP, size_t regeneration, size_t damage, Map* map);
};
#endif