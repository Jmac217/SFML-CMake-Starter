#pragma once

#include "BaseState.h"
#include "EventManager.h"

namespace Mac {

	struct State_Intro
		: public BaseState
	{
		State_Intro(StateManager* l_stateManager);

		void OnCreate();
		void OnDestroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& l_time);
		void Draw();

		void Continue(EventDetails* l_details);
	private:
		sf::Texture m_introTexture;
		sf::Sprite m_introSprite;
		sf::Font m_font;
		sf::Text m_text;

		float m_timePassed;
	};
}