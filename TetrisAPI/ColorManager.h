#pragma once
#include <vector>
#include "IColorManager.h"

namespace TetrisAPI
{
	class ColorManager : public IColorManager
	{
	public:
		ColorManager();

		Color GetRandomBlockColor() const;
		Color GetEmptyCellColor() const;

	private:
		static const Color Green;
		static const Color Red;
		static const Color Orange;
		static const Color Yellow;
		static const Color Purple;
		static const Color Cyan;
		static const Color Blue;
		static const Color LightBlue;
		static const Color DarkBlue;

	private:
		std::vector<Color> m_colors;
	};

}

