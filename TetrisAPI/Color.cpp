#include "Color.h"

Color::Color(int r, int g, int b, int a) :
	m_r(GetValidColorValue(r)),
	m_g(GetValidColorValue(g)),
	m_b(GetValidColorValue(b)),
	m_a(GetValidColorValue(a))
{}

int Color::GetR() const
{
	return m_r;
}

int Color::GetG() const
{
	return m_g;
}

int Color::GetB() const
{
	return m_b;
}

int Color::GetA() const
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

int Color::GetValidColorValue(int value)
{
	if (value <= MIN_COLOR)
		return MIN_COLOR;
	if (value >= MAX_COLOR)
		return MAX_COLOR;
	return value;
}
