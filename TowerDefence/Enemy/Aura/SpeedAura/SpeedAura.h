#pragma once
#ifndef _SPEEDAURA_H_
#define _SPEEDAURA_H_
#include "../Aura.h"

class SpeedAura : public Aura
{
private:
	size_t bonus = 2;
public:
	virtual void get_effect(Enemy& enemy) override;
};
#endif
