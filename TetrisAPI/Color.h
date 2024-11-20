#pragma once
#include <stdint.h>

namespace TetrisAPI
{
	class Color
	{
	public:
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
		inline uint8_t GetR() const { return m_r; }
		inline uint8_t GetG() const { return m_g; }
		inline uint8_t GetB() const { return m_b; }
		inline uint8_t GetA() const { return m_a; }

		bool operator==(const Color& other) const;

	private:
		uint8_t m_r;
		uint8_t m_g;
		uint8_t m_b;
		uint8_t m_a;

	};
}

