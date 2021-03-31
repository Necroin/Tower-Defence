#include "HasLifeObject.h"
#include "../../Map/Map.h"
#include "../../Cell/Land/Land.h"

bool HasLifeObject::get_damage(size_t damage)
{
	if (damage >= _life) { 
		_life = 0;
		_map->get(_coordinates.X, _coordinates.Y)->get_entity() = nullptr;
		_map->set(_coordinates.X, _coordinates.Y, new Land);
		DWORD written;
		FillConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), '.', 1, _coordinates, &written);
		return false;
	}
	_life -= damage;
	return true;
}

bool HasLifeObject::alive()
{
	return _life > 0;
}

HasLifeObject::HasLifeObject(Map* map, COORD coordinates, size_t life) :
	_life(life), 
	_max_life(life),
	_map(map),
	_coordinates(coordinates)
{}
