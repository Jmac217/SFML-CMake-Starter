#include "pch.h"
#include "StateManager.h"

namespace Mac {

	StateManager::StateManager(SharedContext* l_shared)
		: m_shared(l_shared)
	{
		RegisterState<State_Intro>(StateType::Intro);
		RegisterState<State_MainMenu>(StateType::MainMenu);
		RegisterState<State_Game>(StateType::Game);
		RegisterState<State_Paused>(StateType::Paused);
		RegisterState<State_GameOver>(StateType::GameOver);
	}

	StateManager::~StateManager()
	{
		for (auto& i : m_states)
		{
			i.second->OnDestroy();
			delete i.second;
		}
	}

	void StateManager::Update(const sf::Time& l_time)
	{
		if (m_states.empty())
			return;

		if (m_states.back().second->IsTranscendent()
			&& m_states.size() > 1)
		{
			auto i = m_states.end();

			while (i != m_states.begin())
			{
				if (i != m_states.end())
					if (!i->second->IsTranscendent())
						break;
				--i;
			}

			for (; i != m_states.end(); ++i)
				i->second->Update(l_time);
		}
		else
			m_states.back().second->Update(l_time);
	}

	void StateManager::Draw()
	{
		if (m_states.empty())
			return;

		if (m_states.back().second->IsTransparent()
			&& m_states.size() > 1)
		{
			auto i = m_states.end();

			while (i != m_states.begin())
			{
				if (i != m_states.end())
					if (!i->second->IsTransparent())
						break;
				--i;
			}

			for (; i != m_states.end(); ++i)
				i->second->Draw();
		}
		else
			m_states.back().second->Draw();
	}

	void StateManager::ProcessRequests()
	{
		while (m_toRemove.begin() != m_toRemove.end())
		{
			RemoveState(*m_toRemove.begin());
			m_toRemove.erase(m_toRemove.begin());
		}
	}

	Mac::SharedContext* StateManager::GetContext()
	{
		return m_shared;
	}

	bool StateManager::HasState(const StateType& l_type)
	{
		for (auto i = m_states.begin(); i != m_states.end(); ++i)
			if (i->first == l_type)
			{
				auto removed = std::find(m_toRemove.begin(), m_toRemove.end(), l_type);
				
				if (removed == m_toRemove.end())
					return true;

				return false;
			}
	}

	void StateManager::SwitchTo(const StateType& l_type)
	{
		m_shared->m_eventManager->SetCurrentState(l_type);

		for (auto i = m_states.begin(); i != m_states.end(); ++i)
			if (i->first == l_type)
			{
				m_states.back().second->Deactivate();
				StateType tmp_type = i->first;
				BaseState* tmp_state = i->second;
				m_states.erase(i);
				m_states.emplace_back(tmp_type, tmp_state);
				tmp_state->Activate();
				return;

			}
		if (!m_states.empty())
			m_states.back().second->Deactivate();

		CreateState(l_type);

		m_states.back().second->Activate();
	}

	void StateManager::Remove(const StateType& l_type)
	{
		m_toRemove.push_back(l_type);
	}

	void StateManager::CreateState(const StateType& l_type)
	{
		auto newState = m_stateFactory.find(l_type);
		if (newState == m_stateFactory.end())
			return;
		BaseState* state = newState->second();
		m_states.emplace_back(l_type, state);
		state->OnCreate();
	}

	void StateManager::RemoveState(const StateType& l_type)
	{
		for (auto i = m_states.begin(); i != m_states.end(); ++i)
			if (i->first == l_type)
			{
				i->second->OnDestroy();
				delete i->second;
				m_states.erase(i);
				return;
			}
	}

}