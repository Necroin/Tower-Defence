#include "Map.h"
#include "../ObjectManager/ObjectManager.h"
#include "../WinhFunc/WinhFunc.h"

Map::Map(size_t level) : _level(level)
{
	Lire* tmp_lire = nullptr;
	Castle* tmp_castle = nullptr;
	ObjectManager<Lire*> lires;
	ObjectManager<Castle*> castles;
	std::string extention(".txt");
	std::string file_path("Map\\Level");
	file_path.append(std::to_string(_level));
	file_path.append(extention);
	std::ifstream file(file_path);
	char symbol;
	size_t row_index = 0;
	_cells.push_back(std::vector<Cell*>());
	while (file.get(symbol)) {
		COORD coord{ static_cast<SHORT>(_cells[row_index].size()), static_cast<SHORT>(row_index)};
		switch (symbol)
		{
		case '.': _cells[row_index].push_back(new Land); break;
		case '^': _cells[row_index].push_back(new Mountain); break;
		case '~': _cells[row_index].push_back(new Water); break;
		case '@': tmp_castle = new Castle(this,coord); castles.push(tmp_castle); _cells[row_index].push_back(tmp_castle); break;
		case '*': tmp_lire = new Lire(this, coord); lires.push(tmp_lire); _cells[row_index].push_back(tmp_lire); break;
		case '\n': ++row_index; _cells.push_back(std::vector<Cell*>()); break;
		default:
			break;
		}
	}
	_length = _cells[0].size();
	_height = _cells.size();
	file.close();
}

Map::~Map()
{
	for (size_t i = 0; i < _cells.size(); ++i)
	{
		for (size_t j = 0; j < _cells[i].size(); ++j)
		{
			auto& cell = _cells[i][j];
			if (cell) { delete cell; }
		}
	}
}

size_t Map::height()
{
	return _height;
}

size_t Map::length()
{
	return _length;
}

Cell*& Map::get(size_t row_index, size_t column_index)
{
	return _cells[column_index][row_index];
}

void Map::set(size_t x, size_t y, Cell* new_cell)
{
	auto& old_cell = _cells[y][x];
	delete old_cell;
	old_cell = new_cell;
	COORD coords{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
	DWORD written;
	FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), new_cell->get_symbol(), 1, coords, &written);
}

const std::vector<std::vector<Cell*>>& Map::get_cells()
{
	return _cells;
}

bool Map::in_map(size_t x, size_t y)
{
	return (x >= 0 && y >= 0 && x < _length && y < _height) ? true : false;
}
