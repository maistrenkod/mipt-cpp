#include <iostream>
#include <array>
#include <map>
#include "Transformer.h"

namespace tf
{

	std::array<std::array<gotg::VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field> transformate_info(std::map<pos, Cell>& map_of_field)
	{
		std::array<std::array<gotg::VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field> result_field;
		for (auto& cage : map_of_field)
		{
			switch (cage.second.GetState())
			{
			case (Cell::State::BLACK):
				result_field[cage.first.first][cage.first.second] = gotg::VALUES_FOR_FIELD::ENEMY_CHECKERS;
				break;
			case (Cell::State::WHITE):
				result_field[cage.first.first][cage.first.second] = gotg::VALUES_FOR_FIELD::MY_CHECKERS;
				break;
			case (Cell::State::BLANKwhite):
			case (Cell::State::BLANKblack):
				result_field[cage.first.first][cage.first.second] = gotg::VALUES_FOR_FIELD::FREE_CAGES;
				break;
			default:
				std::cerr << "Error: can\'t create an array from the map" << std::endl;
				exit(-1);
			}
		}
		return result_field;
	}

}	// namespace tf
