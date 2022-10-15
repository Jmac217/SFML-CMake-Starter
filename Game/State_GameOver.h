#pragma once
#include "BaseState.h"
#include "StateManager.h"

namespace Mac {

	struct State_GameOver
		: public BaseState
	{
		State_GameOver(StateManager* l_stateManager);
		~State_GameOver() = default;

		void OnCreate();
		void OnDestroy();

		void Activate();
		void Deactivate();

		void Update(const sf::Time& l_time);
		void Draw();
	private:
		sf::Font m_font;
		sf::Text m_text;
		float m_elapsed;
	};

}