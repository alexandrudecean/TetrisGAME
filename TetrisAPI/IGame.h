#pragma once
#include "IInputManager.h"
#include "Observable.h"
#include "Grid.h"

namespace TetrisAPI
{
	class IGame : public Observable
	{
	public:
		virtual void Update() = 0;
		virtual const Block& GetNextBlock() const = 0;
		virtual const Grid& GetGrid() const = 0;
		virtual bool IsGameOver() const = 0;
		virtual bool ShowNextBlocks() const = 0;

		virtual ~IGame() = default;
	};
}

