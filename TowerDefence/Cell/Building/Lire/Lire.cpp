#include "Lire.h"
#include "../../../Enemy/LightweightEnemy/LightWeightEnemy.h"
#include "../../../Enemy/HeavyEnemy/HeavyEnemy.h"
#include "../../../Enemy/AviationEnemy/AviationEnemy.h"

Enemy* Lire::get_random_enemy()
{
	static std::uniform_int_distribution<size_t> enemy_dis(0, 2);
	return (this->*get_enemy_arr[enemy_dis(rd)])();
}

Enemy* Lire::get_lightweight_enemy()
{
	return new LightWeightEnemy(_coordinates,
		LightWeightEnemyParameters::HP * _wave,
		LightWeightEnemyParameters::Max_HP * _wave,
		LightWeightEnemyParameters::regeneration * _wave,
		LightWeightEnemyParameters::damage * _wave,
		_map
		);
}

Enemy* Lire::get_heavy_enemy()
{
	return new HeavyEnemy(_coordinates,
		HeavyEnemyParameters::HP * _wave,
		HeavyEnemyParameters::Max_HP * _wave,
		HeavyEnemyParameters::regeneration * _wave,
		HeavyEnemyParameters::damage * _wave,
		_map
	);
}

Enemy* Lire::get_aviation_enemy()
{
	return new AviationEnemy(_coordinates,
		AviationEnemyParameters::HP * _wave,
		AviationEnemyParameters::Max_HP * _wave,
		AviationEnemyParameters::regeneration * _wave,
		AviationEnemyParameters::damage * _wave,
		_map
	);
}

Lire::Lire(Map* map, COORD coordinates) : Building(this, Cell_types::_Lire, '*'), _map(map), _coordinates(coordinates)
{}

const size_t& Lire::timer() const
{
	return _spawn_timer;
}

void Lire::action()
{
	--_spawn_timer;
	if (!_spawn_timer) {
		_enemy_count = _wave + 1;
	}
	if(_enemy_count) {
		_enemies.push(get_random_enemy());
		--_enemy_count;
	}
}

bool Lire::update()
{
	if (!_spawn_timer) { 
		++_wave;
		_spawn_timer = _spawn_time * _wave;
	}
	return true;
}
