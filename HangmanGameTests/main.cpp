#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Grid.h"

using testing::Return;
using namespace TetrisAPI;

class ColorManagerMock : public IColorManager
{
public:
	MOCK_METHOD(Color, GetEmptyCellColor, (), (const override));
	MOCK_METHOD(Color, GetRandomBlockColor, (), (const override));
};

TEST(AnotherTest, TTestName) {
	ColorManagerMock colorManagerMock;
	
	EXPECT_CALL(colorManagerMock, GetEmptyCellColor())
		.WillOnce(Return(Color(0, 0, 0, 0)));
	
	Grid grid(&colorManagerMock);

	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
