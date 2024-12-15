#include "IGameModeStrategy.h"

namespace TetrisAPI
{
	class EasyModeStrategy : public IGameModeStrategy
	{
	public:
		uint16_t GetMoveDownInterval() const override
		{
			return 1000;
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
			return 500;
		}

		bool ShowNextBlocks() const override
		{
			return false;
		}
	};
}
