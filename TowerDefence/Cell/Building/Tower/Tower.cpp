#include "Tower.h"
#include "../../../Map/Map.h"
#include "../../../Enemy/Enemy.h"

Tower::Tower(Map* map, COORD coordinates) :
	HasLevelObject(1, 3),
	Building(this, Cell_types::_Tower, '1'),
	_map(map),
	_coordinates(coordinates)
{}

Enemy* Tower::find_nearest()
{
	Enemy* enemy = nullptr;
#if defined(max)
#undef max
#endif
	double min_distance = std::numeric_limits<double>::max();
	auto radius = _level_parameters[_level - 1].range;
	for (size_t x = _coordinates.X - radius; x < _coordinates.X + radius; ++x)
	{
		for (size_t y = _coordinates.Y - radius; y < _coordinates.Y + radius; ++y)
		{
			if (_map->in_map(x, y)) {
				auto& entity = _map->get(x, y)->get_entity();
				if (entity) {
					auto dist = distance(x, y);
					if (dist < min_distance) {
						min_distance = dist;
						enemy = entity;
					}
				}
			}
		}
	}
	return enemy;
}

double Tower::distance(double x, double y)
{
	return std::sqrt(std::pow(_coordinates.X - x, 2) + std::pow(_coordinates.Y - y, 2));
}

void Tower::action()
{
	auto enemy = find_nearest();
	if (enemy) {
		for (size_t i = 0; i < _level_parameters[_level - 1].rate; ++i) {
			enemy->get_damage(_level_parameters[_level - 1].damage);
		}
	}
}

bool Tower::update()
{
	return true;
}

void Tower::level_up()
{
	HasLevelObject::level_up();
	DWORD written;
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), '0' + _level, 1, _coordinates, &written);
}

const size_t& Tower::get_range() const
{
	return _level_parameters[_level - 1].range;
}

const size_t& Tower::get_damage() const
{
	return _level_parameters[_level - 1].damage;
}

const size_t& Tower::get_fire_rate() const
{
	return _level_parameters[_level - 1].rate;
}

const size_t& Tower::get_level_up_cost() const
{
	return _level_parameters[_level - 1].level_up_cost;
}

const size_t& Tower::get_level() const
{
	return _level;
}
