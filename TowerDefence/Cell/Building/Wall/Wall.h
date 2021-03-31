#pragma once
#ifndef _WALL_H_
#define _WALL_H_
#include "../Building.h"
#include "../../../DeriveObjects/RepairedObject/RepairedObject.h"

class Wall : public Building, public RepairedObject
{
private:
public:
	Wall(Map* map, COORD coordinates, size_t life);
	inline static const size_t _buy_cost = 50;
	inline static const size_t _repair_cost = 50;
	const size_t& get_life() const;
	const size_t& get_max_life() const;
};
#endif