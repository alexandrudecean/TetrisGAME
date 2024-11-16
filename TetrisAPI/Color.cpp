#include "Color.h"

using namespace TetrisAPI;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
	m_r(GetValidColorValue(r)),
	m_g(GetValidColorValue(g)),
	m_b(GetValidColorValue(b)),
	m_a(GetValidColorValue(a))
{}

uint8_t Color::GetR() const
{
	return m_r;
}

uint8_t Color::GetG() const
{
	return m_g;
}

uint8_t Color::GetB() const
{
	return m_b;
}

uint8_t Color::GetA() const
{
	return m_a;
}

bool Color::operator==(const Color& other) const
{
	return m_r == other.m_r &&
		m_g == other.m_g &&
		m_b == other.m_b &&
		m_a == other.m_a;
}

uint8_t Color::GetValidColorValue(uint8_t value)
{
	if (value <= MIN_COLOR)
		return MIN_COLOR;
	if (value >= MAX_COLOR)
		return MAX_COLOR;
	return value;
}
