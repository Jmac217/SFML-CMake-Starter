#pragma once

namespace Mac {

	using ComponentType = unsigned;

	enum class Component
	{
			Position = 0
		,	SpriteSheet
		,	State
		,	Movable
		,	Controller
		,	Collidable
	};

	enum class System
	{
			Renderer = 0
		,	Movement
		,	Collision
		,	Control
		,	State
		,	SheetAnimation
	};
}