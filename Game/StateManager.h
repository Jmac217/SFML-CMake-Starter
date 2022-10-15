#pragma once

#include "State_Intro.h"
#include "State_MainMenu.h"
#include "State_Game.h"
#include "State_Paused.h"
#include "State_GameOver.h"
#include "SharedContext.h"

namespace Mac
{

	enum class StateType
	{
		Intro = 1,
		MainMenu,
		Game,
		Paused,
		GameOver,
		Credits
	};

	using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

	using TypeContainer = std::vector<StateType>;

	using StateFactory = std::unordered_map<StateType, std::function<BaseState* (void)>>;

	struct StateManager
	{
		StateManager(SharedContext* l_shared);
		~StateManager();

		void Update(const sf::Time& l_time);
		void Draw();

		void ProcessRequests();

		SharedContext* GetContext();
		bool HasState(const StateType& l_type);

		void SwitchTo(const StateType& l_type);
		void Remove(const StateType& l_type);
	private:
		void CreateState(const StateType& l_type);
		void RemoveState(const StateType& l_type);

		template<typename T>
		void RegisterState(const StateType& l_type) {
			m_stateFactory[l_type] = [this]() -> BaseState*
			{
				return new T(this);
			};
		}

		SharedContext* m_shared;
		StateContainer m_states;
		TypeContainer m_toRemove;
		StateFactory m_stateFactory;
	};
}