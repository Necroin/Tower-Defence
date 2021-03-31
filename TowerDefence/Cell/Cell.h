#pragma once
#ifndef _CELL_H_
#define _CELL_H_
#include <iostream>

enum Cell_types {
	_Land,
	_Mountain,
	_Water,
	_Wall,
	_Castle,
	_Lire,
	_Tower
};


class Enemy;
class Building;

class Cell {
protected:
	size_t _type;
	char _symbol;
	Enemy* _enemy = nullptr;
	Building* _building = nullptr;
public:
	int get_type();
	Enemy*& get_entity();
	Building*& get_building();
	const char& get_symbol();
	Cell(size_t type, char symbol = ' ', Enemy* enemy = nullptr, Building* building = nullptr);
	virtual ~Cell() {}
public:
	friend std::ostream& operator << (std::ostream& out, const Cell& cell);
};
#endif