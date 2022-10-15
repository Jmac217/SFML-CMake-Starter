#pragma once
#include <SFML/Graphics.hpp>

namespace Mac {
	struct StateManager;

	struct BaseState
	{ 
		BaseState(StateManager* l_stateManager)
			: m_stateManager(l_stateManager)
			, m_transparent(false)
			, m_transcendent(false)
		{
		}

		virtual ~BaseState() {}

		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;

		virtual void Activate() = 0;
		virtual void Deactivate() = 0;

		virtual void Update(const sf::Time& l_time) = 0;
		virtual void Draw() = 0;

		inline void SetTransparent(const bool& l_transparent)
		{
			m_transparent = l_transparent;
		}

		inline bool IsTransparent() const
		{
			return m_transparent;
		}

		inline void SetTranscendent(const bool& l_transcendence)
		{
			m_transcendent = l_transcendence;
		}

		bool IsTranscendent() const
		{
			return m_transcendent;
		}

		StateManager* GetStateManager()
		{
			return m_stateManager;
		}

	protected:
		StateManager* m_stateManager;
		bool m_transparent;
		bool m_transcendent;

	private:
		friend struct StateManager;
	};
}