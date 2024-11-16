#pragma once
#include <optional>
#include "Block.h"
#include "EResult.h"

namespace TetrisAPI
{
	class Grid
	{
	public:
		Grid(const Color& emptyCellColor);

		bool BlockCanMove() const;
		std::vector<std::vector<Color>> GetGrid() const;

		uint16_t ClearLastLines();
		void Rotate();
		void Move(const Position& pos);
		void MoveDown();
		void SpawnBlock(const Block& block);
		 
	public:
		static inline const uint16_t WIDTH = 15;
		static inline const uint16_t HEIGHT = 15;

	private:
		bool LastLineFull() const;
		void ClearLastLine();
		EResult TrySpawnCurrentBlock(const Position& offset) const;
		EResult TrySpawnAt(const Position& pos) const;
		void SetCurrentBlockCells(const Color& color);
		void SpawnCurrentBlock();
		void RemoveCurrentBlock();
		bool IsPositionEmpty(const Position& pos) const;
		bool IsPositionInGrid(const Position& pos) const;

		Color& operator[](const Position& pos);
		const Color& operator[](const Position& pos) const;

	private:
		std::vector<std::vector<Color>> m_grid;
		std::optional<Block> m_currentBlock;
		Position m_currentBlockOffset;
		bool m_blockCanMove;

		const Color m_emptyCellColor;
	};
}

