#pragma once

namespace TetrisAPI 
{
	class IColorManager
	{
	public:
		virtual Color GetRandomBlockColor() const = 0;
		virtual Color GetEmptyCellColor() const = 0;

		virtual ~IColorManager() = default;
	};
}

