#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "../Map/Map.h"
#include "../Enemy/Enemy.h"
#include "../ObjectManager/ObjectManager.h"
#include <iostream>
#include "../WinhFunc/WinhFunc.h"
#include "../Cell/Building/Tower/Tower.h"

class Game {
private:
	Map* _map = nullptr;
	bool _active;

	ObjectManager<Enemy*> _enemies;
	ObjectManager<Lire*> _lires;
	ObjectManager<Castle*> _castles;
	ObjectManager<Tower*> _towers;

	HANDLE hOutput;
	HANDLE hInput;
	DWORD console_prev_mode;
	DWORD written;

	// UPDATE TIME
	size_t _update_time =  10000000;
	size_t _update_timer = _update_time;


	// BUTTONS
	COORD _exit_coordinates;
	inline static const std::string _exit_text = "EXIT";

	COORD _set_tower_coordinates;
	inline static const std::string _set_tower_text = "Set Tower";

	COORD _set_wall_coordinates;
	inline static const std::string _set_wall_text = "Set Wall";

	COORD _object_level_up_coordinates;
	COORD _castle_level_up_coordinates;
	COORD _castle_repair_coordinates;
	inline static const std::string _level_up_text = "Level Up";

	COORD _object_info_coordinates;


	COORD _gold_coordinates;
	void update_gold_info();

	COORD input_begin_coords;

	COORD _wall_repair_coordinates;
	inline static const std::string _repair_text = "Repair";

	// STATUS BAR
	void status_bar(std::string message);
	COORD _status_bar_coordinates;
	inline static const std::string _status_bar_text = "Status bar : ";

	bool check_in_map(const COORD& coords);
private:
	inline void show_info();
public:
	bool is_active();
	size_t update_timer();
	void refresh_timer();
	void decr_timer();

	void Input();
	void Action();
	void Update();
	void Render();
	void Pre_render();
public:
	Game();
	~Game();
};
#endif