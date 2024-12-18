/**
 * @file Color.cpp
 * @brief Implementarea clasei Color pentru gestionarea culorilor în jocul Tetris.
 *
 * Aceast? clas? reprezint? o culoare RGBA ?i ofer? func?ionalit??i pentru compararea culorilor.
 */
#include "Color.h"

using namespace TetrisAPI;

/**
 * @brief Constructor pentru clasa Color.
 *
 * Ini?ializeaz? o culoare RGBA cu valorile specificate.
 *
 * @param r Componenta de culoare ro?ie (0-255).
 * @param g Componenta de culoare verde (0-255).
 * @param b Componenta de culoare albastr? (0-255).
 * @param a Componenta de transparen?? (alpha) (0-255).
 */
Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
	m_r{ r },
	m_g{ g },
	m_b{ b },
	m_a{ a }
{}

/**
 * @brief Operator de compara?ie pentru egalitatea a dou? culori.
 *
 * Compar? componentele RGBA ale culorii curente cu cele ale unei alte culori.
 *
 * @param other Referin?? la o alt? culoare care va fi comparat?.
 * @return true dac? toate componentele culorilor sunt egale, false în caz contrar.
 */
bool Color::operator==(const Color& other) const
{
	return m_r == other.m_r &&
		m_g == other.m_g &&
		m_b == other.m_b &&
		m_a == other.m_a;
}

