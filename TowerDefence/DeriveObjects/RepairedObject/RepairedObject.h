#pragma once
#ifndef _REPAIREDOBJECT_H_
#define _REPAIREDOBJECT_H_
#include "../HasLifeObject/HasLifeObject.h"

class RepairedObject : public HasLifeObject
{
protected:
	double _repair_coef;
public:
	void repair() {
		_life += static_cast<double>(_max_life)* _repair_coef;
		if (_life > _max_life) {
			_life = _max_life;
		}
	}
public:
	RepairedObject(Map* map,COORD coordinates ,size_t life, double repair_coef) : _repair_coef(repair_coef), HasLifeObject(map, coordinates,life) {}
};
#endif