#pragma once
#ifndef _CASTLE_H_
#define _CASTLE_H_
#include "../Building.h"
#include "../../../DeriveObjects/HasLevelObject/HasLevelObject.h"
#include "../../../DeriveObjects/RepairedObject/RepairedObject.h"
#include <vector>

class Castle : public Building, public HasLevelObject, public RepairedObject
{
private:
	struct Parameters
	{
		size_t profitability;
		size_t _max_life;
		size_t repair_time;
		size_t repair_cost;
		size_t level_up_cost;
	};
	inline static const std::vector<Parameters> _levels_parameters = {
		Parameters{1000,25000,20,10,100},
		Parameters{50,50000,10,20,200},
		Parameters{100,100000,5,30,300}
	};

	inline static size_t _gold = 0;
	bool _repair_flag = false;
	size_t _repair_timer = 0;
public:
	Castle(Map* map, COORD coordinates);
	bool update();
	void repair();
	void level_up();
	~Castle() override {}
public:
	static const size_t& gold();
	const size_t& level() const;
	const size_t& hp() const;
	const size_t& profitability() const;
	const size_t& max_hp() const;
	const size_t& repair_time() const;
	const size_t& repair_cost() const;
	const size_t& level_up_cost() const;
	const COORD& get_coordinates();
	static bool take_gold(size_t gold);
	bool is_repairing() const;
	const size_t& get_repair_timer() const;
};
#endif