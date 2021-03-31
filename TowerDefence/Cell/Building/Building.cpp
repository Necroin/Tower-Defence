#include "Building.h"

Building::Building(Building* building,size_t type, char symbol) : Cell(type, symbol, nullptr, building)
{}