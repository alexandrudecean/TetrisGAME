#pragma once

namespace TetrisAPI
{
	class Position
	{
	public:
		Position(int x = 0, int y = 0);
		int GetX() const;
		int GetY() const;
		void SetX(int x);
		void SetY(int y);

		bool operator==(const Position& other);
		Position operator+(const Position& other) const;
		Position& operator+=(const Position& other);
	public:
		static const Position Origin;
	private:
		int m_x;
		int m_y;
	};
}

