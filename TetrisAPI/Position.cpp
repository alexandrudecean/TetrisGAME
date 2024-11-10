#include "Position.h"

using namespace TetrisAPI;

const Position Position::Origin(0, 0);

Position::Position(int x, int y) : m_x(x), m_y(y)
{}

int Position::GetX() const
{
	return m_x;
}

int Position::GetY() const
{
	return m_y;
}

void Position::SetX(int x)
{
	m_x = x;
}

void Position::SetY(int y)
{
	m_y = y;
}

bool Position::operator==(const Position& other)
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
