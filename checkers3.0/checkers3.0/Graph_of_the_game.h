#pragma once
#include <memory>
#include <vector>
#include <array>
#include <exception>
#include <iostream>
#include <functional>
#include "Turn.h"
#include "Best_turn.h"

namespace gotg
{

	enum class VALUES_FOR_FIELD : char
	{
		FREE_CAGES = 0,
		MY_CHECKERS = 1,
		ENEMY_CHECKERS = 2
	};

	extern VALUES_FOR_FIELD inverse_value_for_field(VALUES_FOR_FIELD);

	const turn::Turn STD_TURN{ turn::Cage_on_field(0, 0), turn::Cage_on_field(0, 0) };

	class Graph_of_the_game final
	{
	private:
		std::array<std::array<VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field> game_field;
		turn::Turn turn_to_it_field;
		std::vector<std::shared_ptr<Graph_of_the_game>> subgraphs;
		size_t count_of_my_checkers_eaten;		// êîëè÷åñòâî øàøåê, êîòîðîå ñúåë ïðîòèâíèê
		size_t count_of_enemy_checkers_eaten;	// êîëè÷åñòâî øàøåê, êîòîðîå ñúåë èãðîê
		VALUES_FOR_FIELD who_is_turn_now;		//
	public:
		Graph_of_the_game(const std::array<std::array<VALUES_FOR_FIELD, turn::width_of_field>, turn::heigh_of_field>&, const VALUES_FOR_FIELD) throw(std::exception&);
		bool is_cage_empty(const size_t, const size_t) const throw(std::exception&);
		bool is_cage_empty(const turn::Cage_on_field&) const throw(std::exception&);
		VALUES_FOR_FIELD which_checkers_is_here(const turn::Cage_on_field&) const noexcept;
		std::vector<turn::Turn> get_all_turns_for_checker(turn::Cage_on_field&, VALUES_FOR_FIELD, bool = true) const noexcept;
		void make_all_valid_subgraphs() throw(std::exception&);
		void change_field_using_turn_to_it() noexcept;
		friend std::ostream& operator<<(std::ostream&, const Graph_of_the_game&);
		friend void make_full_graph(std::shared_ptr<Graph_of_the_game>, const size_t, const std::shared_ptr<std::vector<bt::Info_about_one_first_turn>>, std::function<double(const bt::Eaten_checkers&)>, bool = true);
	};

	extern void make_full_graph(std::shared_ptr<Graph_of_the_game>, const size_t, const std::shared_ptr<std::vector<bt::Info_about_one_first_turn>>, std::function<double(const bt::Eaten_checkers&)>, bool );

}	//	namespace gotg
