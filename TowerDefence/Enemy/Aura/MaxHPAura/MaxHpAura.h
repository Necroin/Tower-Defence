#pragma once
#ifndef _MAXHPAURA_H_
#define _MAXHPAURA_H_
#include "../Aura.h"

class MaxHpAura : public Aura
{
private:
	size_t bonus = 50;
public:
	virtual void get_effect(Enemy& enemy) override;
};
#endif