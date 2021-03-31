#pragma once
#ifndef _HASLEVELOBJECT_H_
#define _HASLEVELOBJECT_H_

class HasLevelObject {
protected:
	size_t _level;
	size_t _max_level;
public:
	void level_up() {
		++_level;
		if (_level > _max_level) { _level = _max_level; }
	}
	bool can_level_up() {
		return _level < _max_level;
	}
	HasLevelObject(size_t level, size_t max_level) : _level(level), _max_level(max_level) {}
};
#endif