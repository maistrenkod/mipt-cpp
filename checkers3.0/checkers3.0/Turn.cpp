#include <iostream>
#include <exception>
#include <algorithm>
#include "Turn.h"

namespace turn
{

	Cage_on_field::Cage_on_field(const size_t new_x, const size_t new_y)
		: x(new_x), y(new_y)
	{
		if (x >= width_of_field || y >= heigh_of_field || x < 0 || y < 0)
		{
			//std::cout << "Smth error" << x << " " << y << std::endl;
			throw (std::out_of_range("Error: coordinates for cage is out of range"));
		}
	}

	Cage_on_field& Cage_on_field::operator=(const Cage_on_field& new_cage)
	{
		x = new_cage.x;
		y = new_cage.y;
		return *this;
	}

	std::ostream& operator<<(std::ostream& out, const Cage_on_field& cage)
	{
		out << cage.x << cage.y;
		return out;
	}

	bool operator==(const Cage_on_field& c1, const Cage_on_field& c2)
	{
		return (c1.x == c2.x) && (c1.y == c2.y);
	}

	Elementary_turn::Elementary_turn(const Cage_on_field& c_from, const Cage_on_field& c_to) noexcept
		: cage_from(c_from), cage_to(c_to)
	{}

	Cage_on_field Elementary_turn::get_from() const noexcept
	{
		return cage_from;
	}

	Cage_on_field Elementary_turn::get_to() const noexcept
	{
		return cage_to;
	}

	std::ostream& operator<<(std::ostream& out, const Elementary_turn& elem_turn)
	{
		out << elem_turn.cage_from << "-" << elem_turn.cage_to;
		return out;
	}

	Turn::Turn(const std::initializer_list<Elementary_turn>& init_list) noexcept
	{
		for (auto& turn : init_list)
		{
			parts_of_turn.push_back(turn);
		}
	}

	Turn::Turn(const std::initializer_list<Cage_on_field>& init_list) noexcept
	{
		Cage_on_field two_cages[2];
		auto iterator = init_list.begin();
		two_cages[0] = *iterator++;
		for (int i = 1; i < init_list.size(); i++)
		{
			two_cages[1] = *iterator++;
			add_part_of_turn(Elementary_turn(two_cages[0], two_cages[1]));
			two_cages[0] = two_cages[1];
		}
	}

	void Turn::add_part_of_turn(const Elementary_turn& new_part_of_turn) noexcept
	{
		parts_of_turn.push_back(new_part_of_turn);
	}


	std::list<Elementary_turn> Turn::get_full_turn() const noexcept
	{
		return parts_of_turn;
	}

	bool Turn::is_here_this_elementary_turn(const Elementary_turn& elem_turn) const noexcept
	{
		bool is_here = false;
		if (std::find(parts_of_turn.cbegin(), parts_of_turn.cend(), elem_turn) != parts_of_turn.cend())
		{
			is_here = true;
		}
		Elementary_turn back_elem_turn(elem_turn.get_to(), elem_turn.get_from());
		if (std::find(parts_of_turn.cbegin(), parts_of_turn.cend(), back_elem_turn) != parts_of_turn.cend())
		{
			is_here = true;
		}
		return is_here;
	}

	std::ostream& operator<<(std::ostream& out, const Turn& turn)
	{
		for (auto& part_of_turn : turn.parts_of_turn)
		{
			out << part_of_turn << std::endl;
		}
		return out;
	}

	bool operator==(const Elementary_turn& t1, const Elementary_turn& t2)
	{
		return (t1.cage_from == t2.cage_from) && (t1.cage_to == t2.cage_to);
	}

}	//namespace turn
