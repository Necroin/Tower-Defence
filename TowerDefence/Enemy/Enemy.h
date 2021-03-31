#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <random>
#include <vector>
#include <array>
#include "Aura/Aura.h"
#include "../DeriveObjects/HasLifeObject/HasLifeObject.h"
#include "../WinhFunc/WinhFunc.h"

class Map;
class Cell;

class Enemy : public HasLifeObject
{
private:
	friend class MaxHpAura;
	friend class RegenerationAura;
	friend class SpeedAura;
protected:
	inline static std::random_device rd;
protected:
	inline static std::pair<COORD,std::pair<int,int>>** f_map;

	char _symbol;
	std::vector<Aura*> _aura;
	Map* _map = nullptr;
	std::array<size_t, 3> _param_bonuses{ 0,0,0 };
	size_t _regeneration;
	size_t _speed = 2;
	size_t _damage;
	size_t _radius = 2;

	virtual void attack(Cell* tagret_cell) = 0;
	virtual void go() = 0;

	virtual Cell* find_target() = 0;

	bool set_aura();
	Aura* get_aura(size_t index);

	void buff(Enemy& buff_enemy);
	void set_self();

	double distance(double x, double y);
	double distance(double x1, double y1, double x2, double y2);

	void reset_f_map();
public:
	Enemy(COORD coordinates, char symbol, size_t HP, size_t Max_HP, size_t regeneration, size_t damage, Map* map);

	void action();
	bool update();

	static void init_f_map(Map* map);
	static void destroy_f_map(Map* map);
};
#endif

//class EnemyLightweight : public Enemy {
//private:
//	virtual void attack(Cell* tagret_cell);
//	virtual void go();
//
//	virtual Cell* find_target();
//
//};
//class EnemyHeavy : public Enemy
//{
//private:
//	virtual void attack(Cell* tagret_cell);
//	virtual void go();
//
//	virtual Cell* find_target();
//};
//class AviationEnemy : public Enemy {
//private:
//	virtual void attack(Cell* tagret_cell);
//	virtual void go();
//
//	virtual Cell* find_target();
//};