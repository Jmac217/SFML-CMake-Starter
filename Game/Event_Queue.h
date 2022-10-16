#pragma once

namespace Mac {

	using EventID = unsigned int;

	struct EventQueue {

		void AddEvent(const EventID& l_event)
		{
			m_queue.push(l_event);
		}

		bool ProcessEvents(EventID& l_id)
		{
			if (m_queue.empty())
				return false;

			l_id = m_queue.front();
			m_queue.pop();

			return true;
		}

		void Clear()
		{
			while (!m_queue.empty())
				m_queue.pop();
		}

	private:
		std::queue<EventID> m_queue;
	};

}