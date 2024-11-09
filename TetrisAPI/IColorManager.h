#pragma once
#include "Color.h"

class IColorManager
{
public:
	virtual Color GetRandomBlockColor() const = 0;
	virtual Color GetEmptyCellColor() const = 0;
	
	virtual ~IColorManager() = default;
};

