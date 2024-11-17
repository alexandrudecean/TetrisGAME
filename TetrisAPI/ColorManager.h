#pragma once
#include <vector>
#include "IColorManager.h"


namespace TetrisAPI
{
	class ColorManager : public IColorManager
	{
	public:
		Color GetRandomBlockColor() const;
		Color GetEmptyCellColor() const;

	private:
		const  Color GREEN = Color( 47, 230, 23, 255 );
		const  Color RED = Color(232, 18, 18, 255 );
		const  Color ORANGE = Color(226, 116, 17, 255 );
		const  Color YELLOW = Color(237, 234, 4, 255 );
		const  Color PURPLE = Color(166, 0, 247, 255 );
		const  Color CYAN = Color(21, 204, 209, 255 );
		const  Color BLUE = Color(13, 64, 216, 255 );
		const  Color LIGHT_BLUE = Color( 59, 85, 162, 255 );
		const  Color DARK_BLUE = Color( 44, 44, 127, 255 );

	private:
		std::vector<Color> m_colors{GREEN,RED,ORANGE,YELLOW,PURPLE,CYAN,BLUE,LIGHT_BLUE,DARK_BLUE};
	};

}

