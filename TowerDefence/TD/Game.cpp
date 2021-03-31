#include "Game.h"
#include "../WinhFunc/WinhFunc.h"

Game::Game() :  _active(true)
{
	_map = new Map(1);
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleMode(hInput, &console_prev_mode);
	SetConsoleMode(hInput, console_prev_mode & ~ENABLE_QUICK_EDIT_MODE);

	size_t y_offset = 2;
	size_t x_offset = 2;
	size_t set_tower_offset = 5;
	size_t set_wall_offset = 5;
	size_t status_bar_offset = 2;
	
	_set_wall_coordinates.Y = _set_tower_coordinates.Y = _exit_coordinates.Y = _map->height() + y_offset;
	_exit_coordinates.X = x_offset;
	_set_tower_coordinates.X = _exit_coordinates.X + _exit_text.size() + set_tower_offset;
	_set_wall_coordinates.X = _set_tower_coordinates.X + _set_tower_text.size() + set_wall_offset;

	_status_bar_coordinates.Y = _exit_coordinates.Y + status_bar_offset;
	_status_bar_coordinates.X = x_offset;

	size_t x_object_info_offset = 50;
	_object_info_coordinates.Y = _exit_coordinates.Y;
	_object_info_coordinates.X = _set_wall_coordinates.X + x_object_info_offset;

	Enemy::init_f_map(_map);
}

Game::~Game()
{
	Enemy::destroy_f_map(_map);
	delete _map;
	_enemies.destroy_data();
}

void Game::update_gold_info()
{
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hOutput, &consoleInfo);
		int wide = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
		FillConsoleOutputCharacterA(hOutput, ' ', wide - _gold_coordinates.X, { _gold_coordinates.X, _gold_coordinates.Y }, &written);
	}
	auto str = std::to_string(Castle::gold());
	WriteConsoleOutputCharacterA(hOutput, str.c_str(), str.size(), _gold_coordinates, &written);
}

void Game::status_bar(std::string message)
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hOutput, &consoleInfo);
	int wide = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
	static SHORT x_ofset = 2;
	static COORD output_coords{ _status_bar_coordinates.X + _status_bar_text.size() + x_ofset,_status_bar_coordinates.Y };
	FillConsoleOutputCharacterA(hOutput, ' ', wide - output_coords.X, { output_coords.X, output_coords.Y }, &written);
	WriteConsoleOutputCharacterA(hOutput, message.c_str(), message.size(), output_coords, &written);
}

bool Game::check_in_map(const COORD& coords)
{
	return (coords.X >= 0 && coords.Y >= 0 && coords.X < _map->length() && coords.Y < _map->height()) ? true : false;
}

inline void Game::show_info()
{
	static size_t y_info_offset = 5;
	static size_t x_info_offset = 5;
	static size_t castles_info_offset = 3;
	static size_t lires_info_offset = 3;
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hOutput, &consoleInfo);
		int wide = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
		size_t global_x_offset = _map->length() + x_info_offset;
		for (SHORT y = y_info_offset; y < _map->height(); ++y) {
			FillConsoleOutputCharacterA(hOutput, ' ', wide - global_x_offset, { static_cast<SHORT>(global_x_offset), y }, & written);
		}
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD info_coordinates = { _map->length() + x_info_offset, y_info_offset };
	_gold_coordinates = info_coordinates;
	_gold_coordinates.X += 6;
	auto go_down = [&info_coordinates, &hConsole]() {
		++info_coordinates.Y;
		SetConsoleCursorPosition(hConsole, info_coordinates);
	};
	SetConsoleCursorPosition(hConsole, info_coordinates);
	std::cout << "Gold: " << Castle::gold();

	info_coordinates.Y += castles_info_offset;
	auto& castles_data = _castles.data();
	for (size_t i = 0; i < castles_data.size(); ++i) {
		static size_t next_castle_offset = 2;
		SetConsoleCursorPosition(hConsole, info_coordinates);
		std::cout << "Castle " << i + 1 << " :";
		if (castles_data[i]->can_level_up()) {
			std::cout << " |";
			_castle_level_up_coordinates = GetConsoleCursorPosition(hOutput);
			SHORT x_offset = 2;
			_castle_level_up_coordinates.X += x_offset;
			WriteConsoleOutputCharacterA(hOutput, _level_up_text.c_str(), _level_up_text.size(), _castle_level_up_coordinates, &written);
		}
		go_down();
		std::cout << "Level -> " << castles_data[i]->level(); go_down();
		if (castles_data[i]->can_level_up()) { std::cout << "Level up cost -> " << castles_data[i]->level_up_cost(); go_down(); }
		std::cout << "Profitability -> " << castles_data[i]->profitability(); go_down();
		std::cout << "HP -> " << castles_data[i]->hp(); go_down();
		std::cout << "Max HP -> " << castles_data[i]->max_hp(); go_down();
		std::cout << "Repair time -> " << castles_data[i]->repair_time(); go_down();
		std::cout << "Repair cost -> " << castles_data[i]->repair_cost(); go_down();
		_castle_repair_coordinates = info_coordinates;
		_castle_repair_coordinates.X += 2;
		std::cout << "| Repair |";
		if (_castles.data()[0]->is_repairing()) {
			std::cout << " (" << _castles.data()[0]->get_repair_timer() << ")";
		}
		info_coordinates.Y += next_castle_offset;
	}

	info_coordinates.Y += lires_info_offset;
	SetConsoleCursorPosition(hConsole, info_coordinates);
	auto& lires_data = _lires.data();
	for (size_t i = 0; i < lires_data.size(); ++i) {
		std::cout<< "Lire " << i+1 << " : " << "Time to spawn -> " << lires_data[i]->timer();
		go_down();
	}

	SetConsoleCursorPosition(hConsole, input_begin_coords);
}

bool Game::is_active()
{
	return _active;
}

size_t Game::update_timer()
{
	return _update_timer;
}

void Game::refresh_timer()
{
	_update_timer = _update_time;
}

void Game::decr_timer()
{
	--_update_timer;
}

void Game::Input()
{
	static auto mouse_pressed = []() -> bool
	{
		static bool pressed = false;
		static bool was_pressed = false;
		pressed = (GetKeyState(VK_LBUTTON) & 0x8000);
		if (pressed && !was_pressed) {
			was_pressed = true;
			return true;
		}
		was_pressed = pressed;
		return false;
	};
	COORD mouse_coords;
	if (mouse_pressed()) {
		mouse_coords = GetCursorWindowPosition();
		if (mouse_coords.Y + 1 == _exit_coordinates.Y && mouse_coords.X >= _exit_coordinates.X && mouse_coords.X < _exit_coordinates.X + _exit_text.size()) {
			_active = false;
		}
		else if (mouse_coords.Y == _castle_level_up_coordinates.Y && mouse_coords.X >= _castle_level_up_coordinates.X && mouse_coords.X < _castle_level_up_coordinates.X + _level_up_text.size()) {
			auto cost = _castles.data()[0]->level_up_cost();
			if (Castle::gold() >= cost) {
				_castles.data()[0]->level_up();
				Castle::take_gold(cost);
				show_info();
				if (!_castles.data()[0]->can_level_up()) {
					_castle_level_up_coordinates = { -1,-1 };
				}
			}
			else {
				status_bar("You haven't enought gold");
			}
		}
		else if (mouse_coords.Y == _castle_repair_coordinates.Y && mouse_coords.X >= _castle_repair_coordinates.X && mouse_coords.X < _castle_repair_coordinates.X + _repair_text.size()) {
			if (!_castles.data()[0]->is_repairing()) {
				auto cost = _castles.data()[0]->repair_cost();
				if (Castle::gold() >= cost) {
					_castles.data()[0]->repair();
					Castle::take_gold(cost);
					update_gold_info();
					status_bar("Repair started");
				}
				else {
					status_bar("You haven't enought gold");
				}
			}
			else {
				status_bar("Repair process is already running");
			}
		}
		else if (mouse_coords.Y + 1 == _set_tower_coordinates.Y && mouse_coords.X >= _set_tower_coordinates.X && mouse_coords.X < _set_tower_coordinates.X + _set_tower_text.size()) {
			if (Castle::gold() >= Tower::_buy_cost) {
				status_bar("Choose a place to set");
				while (!mouse_pressed());
				mouse_coords = GetCursorWindowPosition();

				if (check_in_map(mouse_coords) && _map->get(mouse_coords.X, mouse_coords.Y)->get_type() == Cell_types::_Land) {
					Tower* tower = new Tower(_map, mouse_coords);
					_map->set(mouse_coords.X, mouse_coords.Y, tower);
					_towers.push(tower);
					Castle::take_gold(Tower::_buy_cost);
					update_gold_info();
					status_bar("");
				}
				else {
					status_bar("You can't set the tower here");
				}
			}
			else {
				status_bar("You haven't enought gold");
			}
		}
		else if (mouse_coords.Y + 1 == _set_wall_coordinates.Y && mouse_coords.X >= _set_wall_coordinates.X && mouse_coords.X < _set_wall_coordinates.X + _set_wall_text.size()) {
			if (Castle::gold() >= Wall::_buy_cost) {
				status_bar("Choose a place to set");
				while (!mouse_pressed());
				mouse_coords = GetCursorWindowPosition();

				if (check_in_map(mouse_coords) && _map->get(mouse_coords.X, mouse_coords.Y)->get_type() == Cell_types::_Land) {
					Wall* wall = new Wall(_map, mouse_coords, 20000);
					_map->set(mouse_coords.X, mouse_coords.Y, wall);
					Castle::take_gold(Wall::_buy_cost);
					update_gold_info();
					status_bar("");
				}
				else {
					status_bar("You can't set the wall here");
				}
			}
			else {
				status_bar("You haven't enought gold");
			}

		}
		else if (check_in_map(mouse_coords) && _map->get(mouse_coords.X, mouse_coords.Y)->get_type() == Cell_types::_Tower) {
			Tower* tower = static_cast<Tower*>(_map->get(mouse_coords.X, mouse_coords.Y));
			SetConsoleCursorPosition(hOutput, _object_info_coordinates);
			auto cout_coord = _object_info_coordinates;
			std::cout << "Tower : ";
			if (tower->can_level_up()) {
				std::cout << " | ";
				auto coords = _object_info_coordinates;
				coords.X += 8;
				WriteConsoleOutputCharacterA(hOutput, _level_up_text.c_str(), _level_up_text.size(), coords, &written);
				_object_level_up_coordinates = coords;
				cout_coord.Y += 1;
				SetConsoleCursorPosition(hOutput, cout_coord);
				std::cout << "Level Up cost : " << tower->get_level_up_cost();
			}
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Level : " << tower->get_level();
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Damage : " << tower->get_damage();
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Range : " << tower->get_range();
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Fire rate : " << tower->get_fire_rate();

			while (!mouse_pressed());
			mouse_coords = GetCursorWindowPosition();
			if (mouse_coords.Y == _object_level_up_coordinates.Y && mouse_coords.X >= _object_level_up_coordinates.X && mouse_coords.X < _object_level_up_coordinates.X + _level_up_text.size()) {
				if (Castle::gold() >= tower->get_level_up_cost()) {
					Castle::take_gold(tower->get_level_up_cost()); 
					update_gold_info();
					tower->level_up();
					status_bar("Level Up !");
				}
				else {
					status_bar("You haven't enought gold");
				}
			}
			{
				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
				GetConsoleScreenBufferInfo(hOutput, &consoleInfo);
				int wide_x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
				int wide_y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
				for (SHORT y = 0; y < wide_y; ++y) {
					FillConsoleOutputCharacterA(hOutput, ' ', wide_x - _object_info_coordinates.X, { _object_info_coordinates.X, _object_info_coordinates.Y + y }, &written);
				}
			}
			_object_level_up_coordinates = { -1,-1 };
		}
		else if (check_in_map(mouse_coords) && _map->get(mouse_coords.X, mouse_coords.Y)->get_type() == Cell_types::_Wall) {
			Wall* wall = static_cast<Wall*>(_map->get(mouse_coords.X, mouse_coords.Y));
			SetConsoleCursorPosition(hOutput, _object_info_coordinates);
			auto cout_coord = _object_info_coordinates;
			_wall_repair_coordinates = _object_info_coordinates;
			_wall_repair_coordinates.X += 9;
			std::cout << "Wall : | " << _repair_text;
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Life : " << wall->get_life();
			cout_coord.Y += 1;
			SetConsoleCursorPosition(hOutput, cout_coord);
			std::cout << "Max Life : " << wall->get_max_life();

			while (!mouse_pressed());
			mouse_coords = GetCursorWindowPosition();
			if (mouse_coords.Y == _wall_repair_coordinates.Y && mouse_coords.X >= _wall_repair_coordinates.X && mouse_coords.X < _wall_repair_coordinates.X + _level_up_text.size()) {
				if (Castle::gold() >= Wall::_repair_cost) {
					Castle::take_gold(Wall::_repair_cost); 
					update_gold_info();
					wall->repair();
					status_bar("Repaired");
				}
				else {
					status_bar("You haven't enought gold");
				}
			}
			{
				CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
				GetConsoleScreenBufferInfo(hOutput, &consoleInfo);
				int wide_x = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
				int wide_y = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
				for (SHORT y = 0; y < wide_y; ++y) {
					FillConsoleOutputCharacterA(hOutput, ' ', wide_x - _object_info_coordinates.X, { _object_info_coordinates.X, _object_info_coordinates.Y + y }, &written);
				}
			}
			_wall_repair_coordinates = { -1,-1 };
		}
		else {}

	}

	//SetConsoleCursorPosition(hOutput, input_begin_coords);
}

void Game::Action()
{
	_lires.action();
	_towers.action();
	_enemies.action();
}

void Game::Update()
{
	_enemies.update();
	_lires.update();
	_active = _castles.data()[0]->update();
	_towers.update();
}

void Game::Render()
{
	show_info();
	status_bar("");
}

void Game::Pre_render()
{
	auto& cells = _map->get_cells();
	for (size_t i = 0; i < _map->height(); ++i)
	{
		for (size_t j = 0; j < _map->length(); ++j)
		{
			std::cout << *(cells[i][j]);
		}
		std::cout << std::endl;
	}
	input_begin_coords = GetConsoleCursorPosition(hOutput);

	show_info();

	WriteConsoleOutputCharacterA(hOutput, _exit_text.c_str(), _exit_text.size(), _exit_coordinates, &written);
	WriteConsoleOutputCharacterA(hOutput, _set_tower_text.c_str(), _set_tower_text.size(), _set_tower_coordinates, &written);
	WriteConsoleOutputCharacterA(hOutput, _set_wall_text.c_str(), _set_wall_text.size(), _set_wall_coordinates, &written);
	WriteConsoleOutputCharacterA(hOutput, _status_bar_text.c_str(), _status_bar_text.size(), _status_bar_coordinates, &written);
}