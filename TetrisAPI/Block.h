#pragma once
#include <vector>
#include "Position.h"
#include "Color.h"

namespace TetrisAPI
{
	class Block
	{
	public:
		void Rotate();
		void UndoRotate();
		std::vector<Position> GetCurrentRotation() const;
		Color GetColor() const;
	private:

	};
}

