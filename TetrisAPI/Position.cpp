#include "Position.h"

using namespace TetrisAPI;

const Position Position::Origin(0, 0);
const Position Position::Down(0, 1);
const Position Position::Left(-1, 0);
const Position Position::Right(1, 0);

Position::Position(uint16_t x, uint16_t y) : m_x(x), m_y(y)
{}

bool Position::operator==(const Position& other) const
{
	return m_x == other.m_x && m_y == other.m_y;
}

Position Position::operator+(const Position& other) const
{
	Position temp(*this);
	return temp+=other;
}

Position& Position::operator+=(const Position& other)
{
	this->m_x += other.m_x;
	this->m_y += other.m_y;
	return *this;
}
