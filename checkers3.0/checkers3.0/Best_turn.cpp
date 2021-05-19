#include <vector>
#include <functional>
#include "Turn.h"
#include "Best_turn.h"

namespace bt
{

	Eaten_checkers::Eaten_checkers(const size_t my_count, const size_t enemy_count) noexcept
		: count_of_my_cheakers(my_count), count_of_enemy_cheakers(enemy_count)
	{}

	Info_about_one_first_turn::Info_about_one_first_turn(turn::Turn& t, std::function<double(const Eaten_checkers)> value_finder) noexcept
		: turn(t), value_for_analysis_finder(value_finder)
	{}

	Info_about_one_first_turn::Info_about_one_first_turn(std::function<double(const Eaten_checkers)> value_finder) noexcept
		: value_for_analysis_finder(value_finder)
	{}

	void Info_about_one_first_turn::add_eaten_cheackers(Eaten_checkers& e_cheackers) noexcept
	{
		eaten_checkers.push_back(e_cheackers);
		//std::cout << "e_checkers: " << e_cheackers.count_of_my_cheakers << "\t" << e_cheackers.count_of_enemy_cheakers << std::endl;
	}

	void Info_about_one_first_turn::find_middle_value() noexcept
	{
		//static int counter = 0;
		//std::cout << "Find_middle_value called:\t" << ++counter << std::endl;
		std::vector<double> values_for_analysis(eaten_checkers.size());
		for (int i = 0; i < eaten_checkers.size(); i++)
		{
			values_for_analysis[i] = value_for_analysis_finder(eaten_checkers[i]);
		}
		double sum = 0;
		size_t count = 0;
		//std::cout << "Before:" << std::endl;
		//std::cout << "sum = " << sum << " count = " << count << std::endl;
		for (const auto& elem : values_for_analysis)
		{
			sum += elem;
			//std::cout << "Elem = " << elem << std::endl;
			count++;
		}
		//std::cout << "After:" << std::endl;
		//std::cout << "sum = " << sum << " count = " << count << std::endl;
		if (count == 0)
		{
			std::cerr << "Error: strange count in find_middle_value" << std::endl;
			exit(-1);
		}
		middle_value = sum / count;
	}

	void Info_about_one_first_turn::add_turn(const turn::Turn& t) noexcept
	{
		turn = t;
	}

	void Info_about_one_first_turn::add_finder(std::function<double(const Eaten_checkers)> finder)
	{
		value_for_analysis_finder = finder;
	}

	std::function<double(const Eaten_checkers)> Info_about_one_first_turn::get_finder() const noexcept
	{
		return value_for_analysis_finder;
	}

	double Info_about_one_first_turn::get_middle_value() const noexcept
	{
		return middle_value;
	}

	turn::Turn Info_about_one_first_turn::get_turn() const noexcept
	{
		return turn;
	}

}	//	namespace bt
