#include "SpeedAura.h"
#include "../../Enemy.h"

void SpeedAura::get_effect(Enemy& enemy) {
	enemy._param_bonuses[Params::Speed] = bonus;
}