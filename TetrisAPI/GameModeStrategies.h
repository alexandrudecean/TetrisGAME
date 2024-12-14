#include "IGameModeStrategy.h"

namespace TetrisAPI
{
	class EasyModeStrategy : public IGameModeStrategy
	{
	public:
		uint16_t GetMoveDownInterval() const override
		{
			return 1;
		}

		bool ShowNextBlocks() const override
		{
			return true;
		}
	};

	class HardModeStrategy : public IGameModeStrategy
	{
	public:
		uint16_t GetMoveDownInterval() const override
		{
			return 0.9998;
		}

		bool ShowNextBlocks() const override
		{
			return false;
		}
	};
}
