#pragma once
#include "Anim_Base.h"
#include "Directions.h"
#include "SpriteSheet.h"

namespace Mac {

	struct Anim_Directional : public Anim_Base
	{
	protected:
		void FrameStep();
		void CropSprite();
		void ReadIn(std::stringstream& l_stream);
	};
}