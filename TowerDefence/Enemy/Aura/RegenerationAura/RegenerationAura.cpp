#include "RegenerationAura.h"
#include "../../Enemy.h"

void RegenerationAura::get_effect(Enemy& enemy)
{
	enemy._param_bonuses[Params::Regeneration] = bonus;
}