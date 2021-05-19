#include <memory>
#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <cmath>
#include "Turn.h"
#include "Graph_of_the_game.h"
#include "Best_turn.h"

namespace gotg
{

	VALUES_FOR_FIELD inverse_value_for_field(VALUES_FOR_FIELD root)
	{
		switch (root)
		{
		case VALUES_FOR_FIELD::ENEMY_CHECKERS :
			return VALUES_FOR_FIELD::MY_CHECKERS;
		case VALUES_FOR_FIELD::MY_CHECKERS :
			return VALUES_FOR_FIELD::ENEMY_CHECKERS;
		default :
			return VALUES_FOR_FIELD::FREE_CAGES;
		}
	}

	Graph_of_the_game::Graph_of_the_game(const std::array<std::array<VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field>& new_game_field, const VALUES_FOR_FIELD who_is_t_now) throw(std::exception&)
		: turn_to_it_field(STD_TURN), game_field(new_game_field), count_of_my_checkers_eaten(0), count_of_enemy_checkers_eaten(0), who_is_turn_now(who_is_t_now)
	{
		if (who_is_turn_now == VALUES_FOR_FIELD::FREE_CAGES)
		{
			throw std::invalid_argument("Fatal error: invalid argument in constructor of \"Graph_of_the_game\": who_is_turn is equal to FREE_CAGES");
		}
	}

	bool Graph_of_the_game::is_cage_empty(const size_t x, const size_t y) const throw(std::exception&)
	{
		if (x >= turn::width_of_field || y >= turn::heigh_of_field)
		{
			throw std::out_of_range("Error: out of range in field_of_game in function \"Graph_of_the_game::is_cage_empty\"");	//	èçëèøíå
		}
		return !static_cast<bool>(game_field[y][x]);
	}

	bool Graph_of_the_game::is_cage_empty(const turn::Cage_on_field& cage) const throw(std::exception&)
	{
		if (cage.x >= turn::width_of_field || cage.y >= turn::heigh_of_field)
		{
			throw std::out_of_range("Error: out of range in field_of_game in function \"Graph_of_the_game::is_cage_empty\"");
		}
		//std::cout << "x = " << cage.x << " " << "y = " << cage.y << " " << "cheker = " << static_cast<int>(game_field[cage.y][cage.x]) << std::endl;
		return !static_cast<bool>(game_field[cage.y][cage.x]);
	}

	VALUES_FOR_FIELD Graph_of_the_game::which_checkers_is_here(const turn::Cage_on_field& cage) const noexcept
	{
		return game_field[cage.y][cage.x];
	}

	std::vector<turn::Turn> Graph_of_the_game::get_all_turns_for_checker(turn::Cage_on_field& cage, VALUES_FOR_FIELD checker_in_this_cage, bool is_it_first_call) const noexcept
	{
		//std::cout << "Cage = " << cage << std::endl;
		static std::vector<turn::Turn> possible_turns;
		static VALUES_FOR_FIELD which_chekers_can_eat;
		static int direction_of_turns = 0;	// äàëåå ìîæåò áûòü òîëüêî 1 èëè -1
		static bool is_was_eat = false;
		if (is_it_first_call == true)
		{
			possible_turns.clear();
			switch (checker_in_this_cage)
			{
			case VALUES_FOR_FIELD::MY_CHECKERS :
				which_chekers_can_eat = VALUES_FOR_FIELD::ENEMY_CHECKERS;
				direction_of_turns = 1;
				break;
			case VALUES_FOR_FIELD::ENEMY_CHECKERS :
				which_chekers_can_eat = VALUES_FOR_FIELD::MY_CHECKERS;
				direction_of_turns = -1;
				break;
			case VALUES_FOR_FIELD::FREE_CAGES :
				return possible_turns;
				break;
			default:
				std::cerr << "Fatal error: can\'t define type of the cage in function \"Graph_of_the_game::get_all_turns_for_checker\"";
				exit(-1);
			}
		}
		turn::Turn last_turn_in_possible_turns = STD_TURN;
		if (!possible_turns.empty())
		{
			last_turn_in_possible_turns = possible_turns[possible_turns.size() - 1];
		}
		size_t start_size_for_possible_turns = possible_turns.size();
		try
		{
			turn::Cage_on_field new_cage(cage.x - 2, cage.y - 2);
			if ((is_cage_empty(new_cage)) && (which_checkers_is_here(turn::Cage_on_field(cage.x - 1, cage.y - 1)) == which_chekers_can_eat) && (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
				is_was_eat = true;
				get_all_turns_for_checker(new_cage, checker_in_this_cage, false);
			}
		}
		catch (std::exception& ex) {}
		//	íå ìîæåò áûòü 2 øàãîâ ïî îäèíàêîâûì êëåòêàì
		try
		{
			turn::Cage_on_field new_cage(cage.x - 2, cage.y + 2);
			//std::cout << is_cage_empty(new_cage) << "\t" << (which_checkers_is_here(turn::Cage_on_field(cage.x - 1, cage.y + 1)) == VALUES_FOR_FIELD::ENEMY_CHECKERS) << "\t" << (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false) << std::endl;
			if ((is_cage_empty(new_cage)) && (which_checkers_is_here(turn::Cage_on_field(cage.x - 1, cage.y + 1)) == which_chekers_can_eat) && (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
				is_was_eat = true;
				get_all_turns_for_checker(new_cage, checker_in_this_cage, false);
			}
		}
		catch (std::exception& ex) {}
		try
		{
			turn::Cage_on_field new_cage(cage.x + 2, cage.y - 2);
			if ((is_cage_empty(new_cage)) && (which_checkers_is_here(turn::Cage_on_field(cage.x + 1, cage.y - 1)) == which_chekers_can_eat) && (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
				is_was_eat = true;
				get_all_turns_for_checker(new_cage, checker_in_this_cage, false);
			}
		}
		catch (std::exception& ex) {}
		try
		{
			turn::Cage_on_field new_cage(cage.x + 2, cage.y + 2);

			//test
			//std::cout << is_cage_empty(new_cage) << "\t" << (which_checkers_is_here(turn::Cage_on_field(cage.x + 1, cage.y + 1)) == VALUES_FOR_FIELD::ENEMY_CHECKERS) << "\t" << (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false) << std::endl;
			//if ((last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == true))
			//{
				//std::cout << "Last_turn is " << last_turn_in_possible_turns << "Elementary_turn is " << turn::Elementary_turn(cage, new_cage) << std::endl;
			//}
			//test

			if ((is_cage_empty(new_cage)) && (which_checkers_is_here(turn::Cage_on_field(cage.x + 1, cage.y + 1)) == which_chekers_can_eat) && (last_turn_in_possible_turns.is_here_this_elementary_turn(turn::Elementary_turn(cage, new_cage)) == false))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
				//std::cout << "New_cage = " << new_cage << std::endl;
				is_was_eat = true;
				get_all_turns_for_checker(new_cage, checker_in_this_cage, false);
			}
		}
		catch (std::exception& ex) {}
		if (is_was_eat == true)
		{
			is_was_eat = false;
			return possible_turns;
		}
		try
		{
			turn::Cage_on_field new_cage(cage.x + 1, cage.y + direction_of_turns);		//	øàøêè èãðîêà ðàñïîëãàãàþòñÿ ââåðõó ïîëÿ è äâèãàþòñÿ âíèç
			if (is_cage_empty(new_cage))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
			}
		}
		catch (std::exception& ex) {}
		try
		{
			turn::Cage_on_field new_cage(cage.x - 1, cage.y + direction_of_turns);
			if (is_cage_empty(new_cage))
			{
				if (start_size_for_possible_turns != 0)
				{
					possible_turns.push_back(last_turn_in_possible_turns);
					possible_turns[possible_turns.size() - 1].add_part_of_turn(turn::Elementary_turn(cage, new_cage));
				}
				else
				{
					possible_turns.push_back(turn::Turn{ cage, new_cage });
				}
			}
		}
		catch (std::exception& ex) {}
		return possible_turns;
	}

	std::ostream& operator<<(std::ostream& out, const Graph_of_the_game& graph)
	{
		for (int i = 0; i < turn::heigh_of_field; i++)
		{
			for (int j = 0; j < turn::width_of_field; j++)
			{
				out << static_cast<int>(graph.game_field[i][j]) << " ";
			}
			out << std::endl;
		}
		return out;
	}

	void Graph_of_the_game::make_all_valid_subgraphs() throw(std::exception&)
	{
		std::vector<turn::Turn> all_possible_turns;
		VALUES_FOR_FIELD who_is_next_turn = inverse_value_for_field(who_is_turn_now);
		for (int i = 0; i < turn::heigh_of_field; i++)
		{
			for (int j = 0; j < turn::width_of_field; j++)
			{
				turn::Cage_on_field my_cage(j, i);
				if (which_checkers_is_here(my_cage) != who_is_turn_now)
				{
					continue;
				}
				all_possible_turns = get_all_turns_for_checker(my_cage, who_is_turn_now);
				for (auto& turn : all_possible_turns)
				{
					subgraphs.push_back(std::make_shared<Graph_of_the_game>(game_field, who_is_next_turn));
					subgraphs[subgraphs.size() - 1]->turn_to_it_field = turn;
					subgraphs[subgraphs.size() - 1]->count_of_my_checkers_eaten = count_of_my_checkers_eaten;
					subgraphs[subgraphs.size() - 1]->count_of_enemy_checkers_eaten = count_of_enemy_checkers_eaten;
					subgraphs[subgraphs.size() - 1]->change_field_using_turn_to_it();
					/*std::cout << turn << std::endl;
					std::cout << *subgraphs[subgraphs.size() - 1] << std::endl;
					std::cout << "Count of my cheackers eaten:\t" << subgraphs[subgraphs.size() - 1]->count_of_my_checkers_eaten << std::endl;
					std::cout << "Count of enemy cheackers eaten:\t" << subgraphs[subgraphs.size() - 1]->count_of_enemy_checkers_eaten << std::endl;
					std::cout << std::endl << std::endl;*/
				}
			}
		}
	}

	void Graph_of_the_game::change_field_using_turn_to_it() noexcept
	{
		//	â ïðåäïîëîæåíèè ÷òî turn çàäàí êîððåêòíî
		for (auto& elem_turn : turn_to_it_field.get_full_turn())
		{
			if (abs(static_cast<int>(elem_turn.get_to().x - elem_turn.get_from().x)) == 2)
			{
				game_field[(elem_turn.get_from().y + elem_turn.get_to().y) / 2][(elem_turn.get_from().x + elem_turn.get_to().x) / 2] = VALUES_FOR_FIELD::FREE_CAGES;
				if (who_is_turn_now == VALUES_FOR_FIELD::ENEMY_CHECKERS)
				{
					count_of_enemy_checkers_eaten++;
				}
				else
				{
					count_of_my_checkers_eaten++;
				}
			}
		}
		game_field[(*turn_to_it_field.get_full_turn().begin()).get_from().y][(*turn_to_it_field.get_full_turn().begin()).get_from().x] = VALUES_FOR_FIELD::FREE_CAGES;
		game_field[(*--turn_to_it_field.get_full_turn().end()).get_to().y][(*--turn_to_it_field.get_full_turn().end()).get_to().x] = inverse_value_for_field(who_is_turn_now);		//	èñïðàâèòü!
	}

	void make_full_graph(std::shared_ptr<Graph_of_the_game> graph_ptr, const size_t deep_of_prediction, const std::shared_ptr<std::vector<bt::Info_about_one_first_turn>> info_about_eaten_checkers_vector_ptr, std::function<double(const bt::Eaten_checkers&)> analyse_value_finder, bool is_first)
	{
		static size_t deep = 0;
		static size_t count = 0;	//	test
		static size_t first_turn_index = 0;
		if (is_first == true)
		{
			deep = 0;
			count = 0;
			first_turn_index = 0;
		}
		if (deep >= deep_of_prediction)
		{
			bt::Eaten_checkers eaten_checkers(graph_ptr->count_of_my_checkers_eaten, graph_ptr->count_of_enemy_checkers_eaten);
			//std::cout << "Eaten checkers:\t" << "my: " << graph_ptr->count_of_my_checkers_eaten << "\tenemy: " << graph_ptr->count_of_enemy_checkers_eaten << std::endl;
			(*info_about_eaten_checkers_vector_ptr)[first_turn_index - 1].add_eaten_cheackers(eaten_checkers);
			deep--;
			return;
		}
		graph_ptr->make_all_valid_subgraphs();
		for (auto& subgraph : graph_ptr->subgraphs)
		{
			if (deep == 0)
			{
				info_about_eaten_checkers_vector_ptr->push_back(bt::Info_about_one_first_turn(analyse_value_finder));
				(*info_about_eaten_checkers_vector_ptr)[info_about_eaten_checkers_vector_ptr->size() - 1].add_turn(subgraph->turn_to_it_field);
				first_turn_index++;
			}
			deep++;
			count++;	//test
			//std::cout << "Now turns :" << static_cast<int>(subgraph->who_is_turn_now) << std::endl;
			make_full_graph(subgraph, deep_of_prediction, info_about_eaten_checkers_vector_ptr, analyse_value_finder, false);
			if (deep == 0)
			{
				(*info_about_eaten_checkers_vector_ptr)[first_turn_index - 1].find_middle_value();
			}
		}
		deep--;
		//std::cout << "count:\t" << count << std::endl;
		return;
	}

}	//	namespace gotg