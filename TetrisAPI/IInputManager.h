#pragma once

#include "EInputType.h"

namespace TetrisAPI
{
	class IInputManager
	{
	public:
		virtual bool Check(EInputType inputType) const = 0;
		virtual void Register(EInputType inputType, int key) = 0;
	};
}
