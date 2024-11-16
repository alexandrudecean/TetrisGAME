#pragma once
#include <ctime>
#include<vector>

namespace TetrisAPI
{
	enum EBlockType
	{
		I,
		L,
		J,
		Z,
		S,
		T,
		O
	};

	inline EBlockType GetRandomBlockType()
	{
		std::vector<EBlockType> blocks = { I,L,J,Z,S,T,O };
		srand(static_cast<unsigned int>(time(nullptr)));
		uint16_t randomIndex = rand() % (sizeof(blocks) / sizeof(blocks[0]));

		return blocks[randomIndex];
	}

}
