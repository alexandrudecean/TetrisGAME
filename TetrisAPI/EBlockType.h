#pragma once
#include<random>

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

	const std::vector<EBlockType> blockTypes = { I, L, J, Z, S, T, O };

	inline EBlockType GetRandomBlockType()
	{
		std::random_device rd;  		
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> dist(0, blockTypes.size() - 1);  
		
		uint16_t randomIndex = dist(gen);

		return blockTypes[randomIndex];
	}

}
