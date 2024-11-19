#pragma once
#include <stdint.h>

namespace TetrisAPI
{
	class Position
	{
	public:
		Position(uint16_t x = 0, uint16_t y = 0);
		inline uint16_t GetX() const { return m_x; }
		inline uint16_t GetY() const { return m_y; }
		inline void SetX(uint16_t x) { m_x = x; }
		inline void SetY(uint16_t y) { m_y = y; }

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

