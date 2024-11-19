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
		inline const std::vector<Position>& GetCurrentRotation() const { return m_rotation[m_indexState]; }
		inline EBlockType GetBlockType() const { return m_blockType; }
		inline Color GetColor() const { return m_color; }

	private:
		void IBlock();
		void LBlock();
		void JBlock();
		void ZBlock();
		void SBlock();
		void TBlock();
		void OBlock();

	private:
		std::vector<std::vector<Position>> m_rotation;
		uint16_t m_indexState;
		Color m_color;
		EBlockType m_blockType;
	};
}

