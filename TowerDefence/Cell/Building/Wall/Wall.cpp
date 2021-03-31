#include "Wall.h"

Wall::Wall(Map* map, COORD coordinates, size_t life) : Building(this, Cell_types::_Wall, '#'), RepairedObject(map, coordinates, life, 0.25)
{}

const size_t& Wall::get_life() const
{
	return _life;
}

const size_t& Wall::get_max_life() const
{
	return _max_life;
}
