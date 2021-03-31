#include "MaxHpAura.h"
#include "../../Enemy.h"

void MaxHpAura::get_effect(Enemy& enemy)
{
	enemy._param_bonuses[Params::Speed] = bonus;
}