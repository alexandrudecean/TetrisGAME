#pragma once
#include <iostream>

namespace TetrisAPI
{
	class Position
	{
	public:
		Position(uint16_t x = 0, uint16_t y = 0);
		uint16_t GetX() const;
		uint16_t GetY() const;
		void SetX(uint16_t x);
		void SetY(uint16_t y);

		bool operator==(const Position& other) const;
		Position operator+(const Position& other) const;
		Position& operator+=(const Position& other);
	public:
		static const Position Origin;
		static const Position Down;
		static const Position Left;
		static const Position Right;
	private:
		uint16_t m_x;
		uint16_t m_y;
	};
}

