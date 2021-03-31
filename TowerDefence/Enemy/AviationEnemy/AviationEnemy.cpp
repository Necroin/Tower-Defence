#include "AviationEnemy.h"
#include "../../ObjectManager/ObjectManager.h"
#include "../../Cell/Building/Castle/Castle.h"
#include "../../Map/Map.h"
#include <set>
#include <unordered_set>

void AviationEnemy::attack(Cell* tagret_cell)
{
	auto building = tagret_cell->get_building();
	if (dynamic_cast<Castle*>(building)) {
		static_cast<Castle*>(building)->get_damage(_damage);
	}
}

void AviationEnemy::go()
{
	ObjectManager<Castle*> _castle;
	auto& castle_coord = _castle.data()[0]->get_coordinates();
	reset_f_map();

	static const int dist = 1;

	static auto comaparator = [&castle_coord](const COORD& left, const COORD& right) -> bool
	{
		static auto distance = [](double x1, double y1, double x2, double y2) -> double
		{
			return std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2);
		};
		return (f_map[left.X][left.Y].second.first + distance(left.X, left.Y, castle_coord.X, castle_coord.Y)) < (f_map[right.X][right.Y].second.first + distance(right.X, right.Y, castle_coord.X, castle_coord.Y));

	};
	std::set<COORD, decltype(comaparator)> open(comaparator);
	open.emplace(_coordinates);

	static auto COORD_hash = [](const COORD& x) {
		return (
			(51 + std::hash<int>()(x.X)) * 51
			+ std::hash<int>()(x.Y)
			);
	};

	static auto COORD_equal = [](const COORD& left, const COORD& right) {
		return left.X == right.X && left.Y == right.Y;
	};
	std::unordered_multiset<COORD, decltype(COORD_hash), decltype(COORD_equal)> closed(10, COORD_hash, COORD_equal);

	bool find_flag = false;
	f_map[_coordinates.X][_coordinates.Y].first = _coordinates;
	f_map[_coordinates.X][_coordinates.Y].second.first = 0;
	f_map[_coordinates.X][_coordinates.Y].second.second = f_map[_coordinates.X][_coordinates.Y].second.first + distance(_coordinates.X, _coordinates.Y, castle_coord.X, castle_coord.Y);
	while (!open.empty() && !find_flag)
	{
		auto current = *(open.begin());

		open.erase(open.begin());
		closed.emplace(current);

		// LEFT
		auto neighbour_coords = current;
		--neighbour_coords.X;
		if (_map->in_map(neighbour_coords.X, neighbour_coords.Y)
			&& closed.find(neighbour_coords) == closed.end()
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_type() != Cell_types::_Mountain
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_entity() == nullptr)
		{
			auto temp_G = f_map[neighbour_coords.X][neighbour_coords.Y].second.first + dist;
			bool not_in_open = open.find(neighbour_coords) == open.end();
			if (not_in_open || temp_G < f_map[neighbour_coords.X][neighbour_coords.Y].second.first) {
				f_map[neighbour_coords.X][neighbour_coords.Y].first = current;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.first = temp_G;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.second = temp_G + distance(neighbour_coords.X, neighbour_coords.Y, castle_coord.X, castle_coord.Y);
				if (not_in_open) { open.emplace(neighbour_coords); }
			}
		}

		// RIGHT
		neighbour_coords = current;
		++neighbour_coords.X;
		if (_map->in_map(neighbour_coords.X, neighbour_coords.Y)
			&& closed.find(neighbour_coords) == closed.end()
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_type() != Cell_types::_Mountain
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_entity() == nullptr)
		{
			auto temp_G = f_map[neighbour_coords.X][neighbour_coords.Y].second.first + dist;
			bool not_in_open = open.find(neighbour_coords) == open.end();
			if (not_in_open || temp_G < f_map[neighbour_coords.X][neighbour_coords.Y].second.first) {
				f_map[neighbour_coords.X][neighbour_coords.Y].first = current;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.first = temp_G;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.second = temp_G + distance(neighbour_coords.X, neighbour_coords.Y, castle_coord.X, castle_coord.Y);
				if (not_in_open) { open.emplace(neighbour_coords); }
			}
		}

		// UP
		neighbour_coords = current;
		--neighbour_coords.Y;
		if (_map->in_map(neighbour_coords.X, neighbour_coords.Y)
			&& closed.find(neighbour_coords) == closed.end()
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_type() != Cell_types::_Mountain
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_entity() == nullptr)
		{
			auto temp_G = f_map[neighbour_coords.X][neighbour_coords.Y].second.first + dist;
			bool not_in_open = open.find(neighbour_coords) == open.end();
			if (not_in_open || temp_G < f_map[neighbour_coords.X][neighbour_coords.Y].second.first) {
				f_map[neighbour_coords.X][neighbour_coords.Y].first = current;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.first = temp_G;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.second = temp_G + distance(neighbour_coords.X, neighbour_coords.Y, castle_coord.X, castle_coord.Y);
				if (not_in_open) { open.emplace(neighbour_coords); }
			}
		}

		// DOWN
		neighbour_coords = current;
		++neighbour_coords.Y;
		if (_map->in_map(neighbour_coords.X, neighbour_coords.Y)
			&& closed.find(neighbour_coords) == closed.end()
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_type() != Cell_types::_Mountain
			&& _map->get(neighbour_coords.X, neighbour_coords.Y)->get_entity() == nullptr)
		{
			auto temp_G = f_map[neighbour_coords.X][neighbour_coords.Y].second.first + dist;
			bool not_in_open = open.find(neighbour_coords) == open.end();
			if (not_in_open || temp_G < f_map[neighbour_coords.X][neighbour_coords.Y].second.first) {
				f_map[neighbour_coords.X][neighbour_coords.Y].first = current;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.first = temp_G;
				f_map[neighbour_coords.X][neighbour_coords.Y].second.second = temp_G + distance(neighbour_coords.X, neighbour_coords.Y, castle_coord.X, castle_coord.Y);
				if (not_in_open) { open.emplace(neighbour_coords); }
			}
		}
		/*Sleep(10);
		DWORD written;
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), 'G', 1, current, &written);*/

		if (current.X == castle_coord.X && current.Y == castle_coord.Y)
		{
			find_flag = true;
		}
	}

	COORD next_coords = _coordinates;
	COORD tmp_coords = castle_coord;
	while (find_flag && !COORD_equal(tmp_coords, _coordinates))
	{
		next_coords = tmp_coords;
		tmp_coords = f_map[tmp_coords.X][tmp_coords.Y].first;
	}
	auto hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	FillConsoleOutputCharacterA(hOutput, _map->get(_coordinates.X, _coordinates.Y)->get_symbol(), 1, _coordinates, &written);
	_map->get(_coordinates.X, _coordinates.Y)->get_entity() = nullptr;

	_coordinates = next_coords;
	FillConsoleOutputCharacterA(hOutput, _symbol, 1, _coordinates, &written);
	_map->get(_coordinates.X, _coordinates.Y)->get_entity() = this;
}

Cell* AviationEnemy::find_target()
{
	Building* f_building = nullptr;
	for (size_t x = _coordinates.X - _radius; x < _coordinates.X + _radius; ++x)
	{
		for (size_t y = _coordinates.Y - _radius; y < _coordinates.Y + _radius; ++y)
		{
			if (_map->in_map(x, y)) {
				auto& building = _map->get(x, y)->get_building();
				if (building && building->get_type() == Cell_types::_Castle) {
					f_building = building;
				}
			}
		}
	}
	return f_building;
}

AviationEnemy::AviationEnemy(COORD coordinates, size_t HP, size_t Max_HP, size_t regeneration, size_t damage, Map* map) :
	Enemy(coordinates, 'a', HP, Max_HP, regeneration, damage, map)
{}