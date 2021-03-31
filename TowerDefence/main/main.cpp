#include "../TD/Game.h"
#include "../ObjectManager/ObjectManager.h"
#include <iostream>

int main(int argc, char* args) {
	system("mode con cols=200 lines=50");
	Game game;
	game.Pre_render();
	while (game.is_active())
	{
		game.Input();
		if (game.update_timer()) {
			game.decr_timer();
		}
		else {
			game.Action();
			game.Update();
			game.Render();
			game.refresh_timer();
		}
	}
	return 0;
}