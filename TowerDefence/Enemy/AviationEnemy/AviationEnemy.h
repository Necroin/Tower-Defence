#pragma once
#ifndef _AVIATIONENEMY_H_
#define _AVIATIONENEMY_H_
#include "../Enemy.h"

class AviationEnemy : public Enemy
{
private:
	virtual void attack(Cell* tagret_cell) override;
	virtual void go() override;

	virtual Cell* find_target() override;
public:
	AviationEnemy(COORD coordinates, size_t HP, size_t Max_HP, size_t regeneration, size_t damage, Map* map);
};
#endif