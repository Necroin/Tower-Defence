#include "Enemy.h"
#include "Aura/MaxHPAura/MaxHpAura.h"
#include "Aura/RegenerationAura/RegenerationAura.h"
#include "Aura/SpeedAura/SpeedAura.h"
#include "../Map/Map.h"


Enemy::Enemy(COORD coordinates, char symbol, size_t HP, size_t Max_HP, size_t regeneration, size_t damage, Map* map) :
	_map(map),
	HasLifeObject(map, coordinates, HP),
	_regeneration(regeneration),
	_damage(damage)
{
	_symbol = set_aura() ? std::toupper(symbol) : symbol;
}

bool Enemy::set_aura() 
{
	bool set = false;
	static std::uniform_int_distribution<size_t> dis_aura_chance_1(0, 10);
	static std::uniform_int_distribution<size_t> dis_aura_chance_3(0, 30);
	static std::uniform_int_distribution<size_t> dis_aura_chance_2(0, 20);
	static std::uniform_int_distribution<size_t> final_dis(0, 0);
	static std::vector<std::uniform_int_distribution<size_t>> dis_aura_chance = {
		dis_aura_chance_1,
		dis_aura_chance_2,
		dis_aura_chance_3,
		final_dis
	};
	static std::uniform_int_distribution<size_t> dis_aura_index(0, 2);
	size_t inc = 0;
	while (!dis_aura_chance[inc](rd)) {
		_aura.push_back(get_aura(dis_aura_index(rd)));
		++inc;
		set = true;
	}
	return set;
}

Aura* Enemy::get_aura(size_t index)
{
	switch (index)
	{
	case 0: return new SpeedAura;
	case 1: return new MaxHpAura;
	case 2: return new RegenerationAura;
	default:
		return nullptr;
		break;
	}
}

void Enemy::buff(Enemy& buff_enemy)
{
	buff_enemy._max_life -= _param_bonuses[Aura::Max_HP];
	buff_enemy._speed -= _param_bonuses[Aura::Speed];
	buff_enemy._regeneration -= _param_bonuses[Aura::Regeneration];
	buff_enemy._param_bonuses = { 0,0,0 };
	for (auto&& aura : _aura) {
		aura->get_effect(buff_enemy);
	}
	buff_enemy._max_life += _param_bonuses[Aura::Max_HP];
	buff_enemy._speed += _param_bonuses[Aura::Speed];
	buff_enemy._regeneration += _param_bonuses[Aura::Regeneration];
}

void Enemy::set_self()
{
	auto& cells = _map->get_cells();
	cells[_coordinates.X][_coordinates.Y]->get_entity() = this;
}

double Enemy::distance(double x, double y)
{
	return std::sqrt(std::pow(_coordinates.X - x, 2) + std::pow(_coordinates.Y - y, 2));
}

double Enemy::distance(double x1, double y1, double x2, double y2)
{
	return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

void Enemy::action()
{
	Cell* target_cell;
	(target_cell = find_target()) ? attack(target_cell) : go();
	auto& _cells = _map->get_cells();
	if (!_aura.empty()) {
		for (size_t x = _coordinates.X - _radius; x < _coordinates.X + _radius; ++x)
		{
			for (size_t y = _coordinates.Y - _radius; y < _coordinates.Y - _radius; ++y)
			{
				if (_map->in_map(x, y)) {
					auto enemy = _cells[y][x]->get_entity();
					if (enemy) buff(*enemy);
				}
			}
		}
	}
}

bool Enemy::update()
{
	return true;
}

void Enemy::init_f_map(Map* map)
{
	auto length = map->length();
	auto height = map->height();

	f_map = new std::pair<COORD, std::pair<int, int>> * [length];
	for (size_t i = 0; i < length; ++i)
	{
		f_map[i] = new std::pair<COORD, std::pair<int, int>>[height];
	}
}

void Enemy::destroy_f_map(Map* map)
{
	auto length = map->length();
	auto height = map->height();

	for (size_t i = 0; i < length; ++i)
	{
		delete f_map[i];
	}
	delete f_map;
}


void Enemy::reset_f_map()
{
	auto length = _map->length();
	auto height = _map->height();
	for (size_t x = 0; x < length; ++x)
	{
		for (size_t y = 0; y < height; ++y)
		{
			f_map[x][y] = { {0,0}, {0,0} };
		}

	}
}
