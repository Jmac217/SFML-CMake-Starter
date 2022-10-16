#pragma once

#include "Communicator.h"
#include "EntityMessages.h"

namespace Mac {

	using Subscribtions = std::unordered_map<EntityMessage, Communicator>;

	struct MessageHandler
	{
		bool Subscribe(const EntityMessage& l_type, Observer* l_observer)
		{
			return m_communicators[l_type].AddObserver(l_observer);
		}

		bool Unsubscribe(const EntityMessage& l_type, Observer* l_observer)
		{
			return m_communicators[l_type].RemoveObserver(l_observer);
		}

		void Dispatch(const Message& l_msg)
		{
			auto itr = m_communicators.find((EntityMessage)l_msg.m_type);
			if (itr == m_communicators.end())
				return;
			itr->second.Broadcast(l_msg);
		}
	private:
		Subscribtions m_communicators;
	};

}