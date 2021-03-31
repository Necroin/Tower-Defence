#pragma once
#ifndef _REGENERATIONAURA_H_
#define _REGENERATIONAURA_H_
#include "../Aura.h"

class RegenerationAura : public Aura 
{
private:
	size_t bonus = 50;
public:
	virtual void get_effect(Enemy& enemy) override;
};
#endif