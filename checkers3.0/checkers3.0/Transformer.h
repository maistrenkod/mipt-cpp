#pragma once
#include <iostream>
#include <map>
#include <array>
#include "Graph_of_the_game.h"
#include "Turn.h"
#include "Cell.h"

using pos = std::pair<size_t, size_t>;


namespace tf
{

	extern std::array<std::array<gotg::VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field> transformate_info(std::map<pos, Cell>&);

}	// namespace tf