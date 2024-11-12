#pragma once

namespace TetrisAPI
{
	enum EResult
	{
		Succes,
		Collision,
		OutOfBounds,
		CollisionWithRight,
		CollisionWithLeft,
		CollisionWithBottom
	};
}