#pragma once
#include <stdint.h>

namespace TetrisAPI
{
    class IGameModeStrategy
    {
    public:
        virtual uint16_t GetMoveDownInterval() const = 0;
        virtual bool ShowNextBlocks() const = 0;
        virtual ~IGameModeStrategy() = default;
    };
}
