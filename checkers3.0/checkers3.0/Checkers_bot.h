#pragma once
#include <iostream>
#include <array>
#include <functional>
#include "Turn.h"
#include "Graph_of_the_game.h"

namespace ch_bot
{

	extern turn::Turn get_the_best_turn(std::array<std::array<gotg::VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field>&, gotg::VALUES_FOR_FIELD, const size_t, std::function<double(const bt::Eaten_checkers)>);

}	//	namespace ch_bot
