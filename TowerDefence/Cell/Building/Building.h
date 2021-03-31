#pragma once
#ifndef _BUILDING_H_
#define _BUILDING_H_
#include "../Cell.h"

class Building : public Cell
{
public:
	Building(Building* building, size_t type, char symbol = ' ');
};
#endif