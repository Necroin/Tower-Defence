#pragma once
#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include <fstream>
#include <string>
#include "../Cell/Cell.h"
#include "../Cell/Building/Wall/Wall.h"
#include "../Cell/Mountain/Mountain.h"
#include "../Cell/Land/Land.h"
#include "../Cell/Water/Water.h"
#include "../Cell/Building/Castle/Castle.h"
#include "../Cell/Building/Lire/Lire.h"

class Map {
private:
	std::vector<std::vector<Cell*>> _cells;
	size_t _level;
	size_t _length = 0;
	size_t _height = 0;
public:
	Map(size_t level);
	~Map();

	size_t height();
	size_t length();

	Cell*& get(size_t row_index, size_t column_index);
	void set(size_t x, size_t y, Cell* new_cell);
	const std::vector<std::vector<Cell*>>& get_cells();
	bool in_map(size_t x, size_t y);
};
#endif