#include "Color.h"

using namespace TetrisAPI;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
	m_r{ r },
	m_g{ g },
	m_b{ b },
	m_a{ a }
{}

bool Color::operator==(const Color& other) const
{
	return m_r == other.m_r &&
		m_g == other.m_g &&
		m_b == other.m_b &&
		m_a == other.m_a;
}

