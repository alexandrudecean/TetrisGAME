#pragma once
#include <iostream>

namespace TetrisAPI
{
	class Color
	{
	public:
		Color(uint16_t r, uint16_t g, uint16_t b, uint16_t a = MAX_COLOR);
		uint16_t GetR()const;
		uint16_t GetG()const;
		uint16_t GetB()const;
		uint16_t GetA()const;

		bool operator==(const Color& other) const;
	private:
		uint16_t GetValidColorValue(uint16_t value);
	private:
		uint16_t m_r;
		uint16_t m_g;
		uint16_t m_b;
		uint16_t m_a;

		static inline const uint16_t MIN_COLOR = 0;
		static inline const uint16_t MAX_COLOR = 255;
	};
}

