#pragma once
#include <vector>
#include "Position.h"
#include "Color.h"

class Block
{
public:
	std::vector<Position> GetCurrentRotation() const;
	Color GetColor() const;
private:

};

