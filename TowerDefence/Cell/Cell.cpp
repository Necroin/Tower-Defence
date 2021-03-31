#include "Cell.h"

Cell::Cell(size_t type, char symbol, Enemy* enemy, Building* building) :
	_type(type),
	_symbol(symbol),
	_enemy(enemy),
	_building(building)
{}

int Cell::get_type()
{
	return _type;
}

Enemy*& Cell::get_entity()
{
	return _enemy;
}

Building*& Cell::get_building()
{
	return _building;
}

const char& Cell::get_symbol()
{
	return _symbol;
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	out << cell._symbol;
	return out;
}
