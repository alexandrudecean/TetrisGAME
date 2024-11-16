#pragma once
#include <stdint.h>
#include "EInputType.h"

namespace TetrisAPI
{
	class IInputManager
	{
	public:
		virtual bool Check(EInputType inputType) const = 0;
		virtual void Register(EInputType inputType, uint16_t key) = 0;

		virtual ~IInputManager() = default;
	};
}
