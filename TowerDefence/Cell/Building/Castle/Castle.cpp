#include "Castle.h"

Castle::Castle(Map* map, COORD coordinates) : Building(this, Cell_types::_Castle, '@'), HasLevelObject(1,3),
RepairedObject(map, coordinates, _levels_parameters[0]._max_life, 0.25)
{}

bool Castle::update()
{
	_gold += _levels_parameters[_level - 1].profitability;
	if (_repair_flag) { --_repair_timer; }
	if (_repair_flag && _repair_timer == 0) {
		RepairedObject::repair();
		_repair_flag = false;
	}
	if (!_life) { return false; }
	return true;
}

void Castle::repair()
{
	if (!_repair_flag) {
		_repair_timer = _levels_parameters[_level - 1].repair_time;
		_repair_flag = true;
	}
}

void Castle::level_up()
{
	HasLevelObject::level_up();
	_life = _max_life = _levels_parameters[_level-1]._max_life;
}

const size_t& Castle::gold() { return _gold; }

const size_t& Castle::level()         const { return _level; }
const size_t& Castle::hp()            const { return _life; }
const size_t& Castle::profitability() const { return _levels_parameters[_level - 1].profitability; }
const size_t& Castle::max_hp()        const { return _levels_parameters[_level - 1]._max_life; }
const size_t& Castle::repair_time()   const { return _levels_parameters[_level - 1].repair_time; }
const size_t& Castle::repair_cost()   const { return _levels_parameters[_level - 1].repair_cost; }
const size_t& Castle::level_up_cost() const { return _levels_parameters[_level - 1].level_up_cost; }

const COORD& Castle::get_coordinates()
{
	return _coordinates;
}

bool Castle::take_gold(size_t gold)
{
	if (_gold < gold) { return false; }
	_gold -= gold;
	return true;
}

bool Castle::is_repairing() const
{
	return _repair_flag;
}

const size_t& Castle::get_repair_timer() const
{
	return _repair_timer;
}
