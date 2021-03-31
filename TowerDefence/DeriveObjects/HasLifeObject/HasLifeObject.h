#pragma once
#ifndef _HASLIFEOBJECT_H_
#define _HASLIFEOBJECT_H_
#include <Windows.h>

class Map;

class HasLifeObject {
protected:
	size_t _life;
	size_t _max_life;

	COORD _coordinates;
	Map* _map;
public:
	bool get_damage(size_t damage);
	bool alive();
public:
	HasLifeObject(Map* map, COORD coordinates, size_t life = 0);
};
#endif