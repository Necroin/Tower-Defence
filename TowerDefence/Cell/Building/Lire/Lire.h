#pragma once
#ifndef _LIRE_H_
#define _LIRE_H_
#include "../Building.h"
#include "../../../ObjectManager/ObjectManager.h"
#include <random>
#include <Windows.h>

class Enemy;
class Map;

class Lire : public Building
{
private:
	struct LightWeightEnemyParameters {
		inline static size_t HP = 10;
		inline static size_t Max_HP = 10;
		inline static size_t regeneration = 10;
		inline static size_t damage = 10;
	};
	struct HeavyEnemyParameters {
		inline static size_t HP = 10;
		inline static size_t Max_HP = 10;
		inline static size_t regeneration = 10;
		inline static size_t damage = 10;
	};
	struct AviationEnemyParameters {
		inline static size_t HP = 10;
		inline static size_t Max_HP = 10;
		inline static size_t regeneration = 10;
		inline static size_t damage = 10;
	};
	Map* _map = nullptr;
	COORD _coordinates;
	inline static std::random_device rd;
	inline const static size_t _spawn_time = 10;
	size_t _spawn_timer = 2;
	inline static ObjectManager<Enemy*> _enemies;
	size_t _enemy_count = 0;
	size_t _wave = 1;
	inline static const size_t _radius = 3;
	Enemy* get_random_enemy();
	Enemy* get_lightweight_enemy();
	Enemy* get_aviation_enemy();
	Enemy* get_heavy_enemy();
	typedef Enemy* (Lire::*fptr)();
	static constexpr fptr get_enemy_arr[3] = {
		&Lire::get_lightweight_enemy,
		&Lire::get_heavy_enemy,
		&Lire::get_aviation_enemy
	};
public:
	Lire(Map* map, COORD coordinates);
	const size_t& timer() const;
	void action();
	bool update();
};
#endif