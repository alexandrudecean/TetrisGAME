#include <gtest/gtest.h>
#include "Color.h"

using namespace TetrisAPI;

namespace ColorTests
{
	TEST(ColorTest, CheckConstructor)
	{
		uint8_t m_r = 0;
		uint8_t m_g = 25;
		uint8_t m_b = 30;
		uint8_t m_a = 255;

		Color color{ m_r,m_g,m_b,m_a };

		ASSERT_EQ(color.GetR(), m_r);
		ASSERT_EQ(color.GetG(), m_g);
		ASSERT_EQ(color.GetB(), m_b);
		ASSERT_EQ(color.GetA(), m_a);
	}

	TEST(ColorTest, CheckEqualsOperator)
	{
		uint8_t m_r = 0;
		uint8_t m_g = 25;
		uint8_t m_b = 30;
		uint8_t m_a = 255;

		Color color1{ m_r,m_g,m_b,m_a };
		Color color2{ m_r,m_g,m_b,m_a };

		ASSERT_EQ(color1, color2);
	}
}
