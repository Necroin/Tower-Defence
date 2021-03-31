#pragma once
#ifndef _AURA_H_
#define _AURA_H_

class Enemy;

class Aura {
public:
	enum Params
	{
		Max_HP,
		Speed,
		Regeneration
	};
public:
	virtual void get_effect(Enemy& enemy) = 0;
};
#endif