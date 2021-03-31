#pragma once
#ifndef _TOWER_H_
#define _TOWER_H_
#include "../Building.h"
#include "../../../DeriveObjects/HasLevelObject/HasLevelObject.h"
#include <vector>
#include "../../../WinhFunc/WinhFunc.h"

class Map;

class Tower : public Building, public HasLevelObject
{
private:
	struct Parameters {
		size_t range;
		size_t damage;
		size_t rate;
		size_t level_up_cost;
	};
	inline static const std::vector<Parameters> _level_parameters = {
		Parameters{5,5,5,5},
		Parameters{5,5,5,5},
		Parameters{5,5,5,5}
	};
	Enemy* find_nearest();
	double distance(double x, double y);
	Map* _map;
	COORD _coordinates;
public:
	Tower(Map* map, COORD coordinates);
	void action();
	bool update();
	void level_up();
	inline static const size_t _buy_cost = 200;

	const size_t& get_range() const;
	const size_t& get_damage() const;
	const size_t& get_fire_rate() const;
	const size_t& get_level_up_cost() const;
	const size_t& get_level() const;

};
#endif