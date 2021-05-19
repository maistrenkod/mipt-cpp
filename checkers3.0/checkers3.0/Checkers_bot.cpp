#include <iostream>
#include <array>
#include <functional>
#include <vector>
#include <ctime>
#include "Turn.h"
#include "Graph_of_the_game.h"

namespace ch_bot
{

	turn::Turn get_the_best_turn(std::array<std::array<gotg::VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field>& my_field, gotg::VALUES_FOR_FIELD who_is_turn, const size_t deep_of_prediction, std::function<double(const bt::Eaten_checkers)> value_for_analyses_finder)
	{

		gotg::Graph_of_the_game my_graph(my_field, who_is_turn);

		//	print start field
		std::cout << "Start field:" << std::endl << my_graph << std::endl;

		//	print all possible turns
		/*
		for (int j = 0; j < turn::heigh_of_field; j++)
		{
			for (int k = 0; k < turn::width_of_field; k++)
			{
				turn::Cage_on_field check(k, j);
				if (my_graph.which_checkers_is_here(check) == gotg::VALUES_FOR_FIELD::FREE_CAGES || my_graph.which_checkers_is_here(check) == gotg::VALUES_FOR_FIELD::ENEMY_CHECKERS)
				{
					continue;
				}
				std::vector<turn::Turn> possible_turns = my_graph.get_all_turns_for_checker(check, gotg::VALUES_FOR_FIELD::MY_CHECKERS);
				for (auto& i : possible_turns)
				{
					std::cout << i << std::endl;
				}
				if (!possible_turns.empty())
				{
					std::cout << std::endl;
				}
			}
			*/

		auto my_graph_ptr = std::make_shared<gotg::Graph_of_the_game>(my_graph);
		auto my_analyzer = std::make_shared<std::vector<bt::Info_about_one_first_turn>>();
		gotg::make_full_graph(my_graph_ptr, deep_of_prediction, my_analyzer, value_for_analyses_finder);

		//	print all middle values
		//std::cout << "Middle values:" << std::endl;
		for (const auto& turn : *my_analyzer)
		{
			/*std::cout << turn.get_middle_value() << std::endl;
			std::cout << turn.get_turn() << std::endl;*/
		}

		std::vector<turn::Turn> best_turns;
		auto best_turn_info = *my_analyzer->begin();
		for (const auto& turn : *my_analyzer)
		{
			if (turn.get_middle_value() > best_turn_info.get_middle_value())
			{
				best_turn_info = turn;
				best_turns.clear();
			}
			if (turn.get_middle_value() == best_turn_info.get_middle_value())
			{
				best_turns.push_back(turn.get_turn());
			}
		}

		srand(time(0));
		size_t random_index = rand() % best_turns.size();

		return best_turns[random_index];
	}

}	//	namespace ch_bot