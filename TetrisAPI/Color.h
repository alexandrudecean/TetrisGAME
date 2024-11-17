#pragma once
#include <stdint.h>

namespace TetrisAPI
{
	class Color
	{
	public:
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = MAX_COLOR);
		uint8_t GetR() const;
		uint8_t GetG() const;
		uint8_t GetB() const;
		uint8_t GetA() const;

		bool operator==(const Color& other) const;
	private:
		uint8_t GetValidColorValue(uint8_t value);
	private:
		uint8_t m_r;
		uint8_t m_g;
		uint8_t m_b;
		uint8_t m_a;

		static constexpr uint8_t MIN_COLOR = 0;
		static constexpr uint8_t MAX_COLOR = 255;
	};
}

