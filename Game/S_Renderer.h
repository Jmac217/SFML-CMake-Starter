#pragma once

#include "S_Base.h"
#include "Window.h"

namespace Mac {

	struct S_Renderer
		: public S_Base
	{
		S_Renderer(SystemManager* l_systemMgr);
		~S_Renderer();

		void Update(float l_deltaTime);
		void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event);
		void Notify(const Message& l_message);
		void Render(Window* l_wind, unsigned int l_layer);

	private:
		void SetSheetDirection(const EntityId& l_entity, const Direction& l_dir);
		void SortDrawables();
	};

}