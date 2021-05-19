#pragma once
#include <vector>
#include <functional>
#include "Turn.h"

namespace bt
{

	struct Eaten_checkers
	{
	public:
		size_t count_of_my_cheakers;
		size_t count_of_enemy_cheakers;
		Eaten_checkers(const size_t, const size_t) noexcept;
	};

	class Info_about_one_first_turn
	{
	private:
		std::vector<Eaten_checkers> eaten_checkers;
		turn::Turn turn;
		std::function<double(Eaten_checkers)> value_for_analysis_finder;		// why not the reference???
		double middle_value{ 0 };
	public:
		Info_about_one_first_turn() = default;
		Info_about_one_first_turn(turn::Turn&, std::function<double(const Eaten_checkers)>) noexcept;
		Info_about_one_first_turn(std::function<double(const Eaten_checkers)>) noexcept;
		void add_eaten_cheackers(Eaten_checkers&) noexcept;
		void add_turn(const turn::Turn&) noexcept;
		void add_finder(std::function<double(const Eaten_checkers)>);
		void find_middle_value() noexcept;
		double get_middle_value() const noexcept;
		turn::Turn get_turn() const noexcept;
		std::function<double(const Eaten_checkers)> get_finder() const noexcept;
		~Info_about_one_first_turn() = default;
	};

}	//	namespace bt