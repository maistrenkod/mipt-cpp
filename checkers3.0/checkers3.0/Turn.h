#pragma once
#include <exception>
#include <list>
#include <initializer_list>
#include <iostream>

namespace turn
{
	constexpr size_t width_of_field = 8;
	constexpr size_t heigh_of_field = 8;

	struct Cage_on_field final
	{
	public:
		size_t x{ 0 };
		size_t y{ 0 };
		Cage_on_field(const size_t = 0, const size_t = 0) throw(std::exception&);
		Cage_on_field(const Cage_on_field&) = default;
		Cage_on_field& operator=(const Cage_on_field&);
		friend std::ostream& operator<<(std::ostream&, const Cage_on_field&);
		friend bool operator==(const Cage_on_field&, const Cage_on_field&);
	};

	class Elementary_turn final//перемещение из клетки в клетку
	{
	private:
		Cage_on_field cage_from;
		Cage_on_field cage_to;
	public:
		Elementary_turn() = default;
		Elementary_turn(const Elementary_turn&) = default;
		Elementary_turn& operator=(const Elementary_turn&) = default;
		Elementary_turn(const Cage_on_field&, const Cage_on_field&) noexcept;
		Cage_on_field get_from() const noexcept;
		Cage_on_field get_to() const noexcept;
		friend std::ostream& operator<<(std::ostream&, const Elementary_turn&);
		friend bool operator==(const Elementary_turn&, const Elementary_turn&);
	};

	class Turn//ход
	{
	private:
		std::list<Elementary_turn> parts_of_turn;
	public:
		Turn() = default;
		explicit Turn(const std::initializer_list<Elementary_turn>&) noexcept;
		explicit Turn(const std::initializer_list<Cage_on_field>&) noexcept;
		Turn(const Turn&) = default;
		Turn& operator=(const Turn&) = default;
		void add_part_of_turn(const Elementary_turn&) noexcept;
		std::list<Elementary_turn> get_full_turn() const noexcept;
		bool is_here_this_elementary_turn(const Elementary_turn&) const noexcept;
		friend std::ostream& operator<<(std::ostream&, const Turn&);
	};

}	//namespace turn
