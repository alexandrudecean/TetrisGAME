#pragma once
#include <vector>
#include "Position.h"
#include "Color.h"
#include "IColorManager.h"
#include "EBlockType.h"

namespace TetrisAPI
{
	class Block
	{
	public:
		Block(const Color& color, EBlockType blockType);
		void Rotate();
		void UndoRotate();
		std::vector<Position> GetCurrentRotation() const;
		Color GetColor() const;
	private:
		std::vector<std::vector<Position>> m_rotation;
		int indexState;
		Color m_color;
		EBlockType m_blockType;
	};
}

