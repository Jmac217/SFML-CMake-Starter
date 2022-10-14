#include "pch.cpp"
#include "EventManager.h"

namespace Mac {
    
	EventManager::EventManager()
		: m_currentState(StateType(0))
		, m_hasFocus(true)
	{
		LoadBindings();
	}

	EventManager::~EventManager() {
		for (auto& itr : m_bindings)
			delete itr.second;
	}

	bool EventManager::AddBinding(Binding* l_binding)
	{
		if (m_bindings.find(l_binding->m_name) != m_bindings.end())
			return false;

		return m_bindings.emplace(l_binding->m_name, l_binding).second;
	}

	bool EventManager::RemoveBinding(std::string l_name)
	{
		auto i = m_bindings.find(l_name);
		
		if (i == m_bindings.end())
			return false;

		delete i->second;
		m_bindings.erase(i);

		return true;
	}

	void EventManager::SetCurrentState(StateType l_state)
	{
		m_currentState = l_state;
	}

	void EventManager::SetFocus(const bool& l_focus)
	{
		m_hasFocus = l_focus;
	}

	void EventManager::HandleEvent(sf::Event& l_event)
	{
		for (auto& b : m_bindings)
		{
			Binding* bind = b.second;

			for (auto& e : bind->m_events)
			{
				// WARNING: C-Style cast needs to be dealt with
				// ===========================================
				EventType sfmlEvent = (EventType)l_event.type;
				// ===========================================

				if (e.first != sfmlEvent)
					continue;

				if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
				{
					if (e.second.m_code == l_event.key.code)
					{
						if (bind->m_details.m_keyCode != -1)
						{
							bind->m_details.m_keyCode = e.second.m_code;
						}

						++(bind->count);
						break;
					}
				}
				else if
					(sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
				{
					if (e.second.m_code == l_event.mouseButton.button)
					{
						bind->m_details.m_mouse.x = l_event.mouseButton.x;
						bind->m_details.m_mouse.y = l_event.mouseButton.y;

						if (bind->m_details.m_keyCode != -1)
						{
							bind->m_details.m_keyCode = e.second.m_code;
						}

						++(bind->count);
					}
				}
				else
				{
					if (sfmlEvent == EventType::MouseWheel)
						bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
					else if
						(sfmlEvent == EventType::WindowResized)
					{
						bind->m_details.m_size.x = l_event.size.width;
						bind->m_details.m_size.y = l_event.size.height;
					}
					else if
						(sfmlEvent == EventType::TextEntered)
					{
						bind->m_details.m_textEntered = l_event.text.unicode;
					}

					++(bind->count);
				}
			}
		}
	}

	void EventManager::Update()
	{
		if (!m_hasFocus)
			return;

		for (auto& b : m_bindings)
		{
			Binding* bind = b.second;
			
			for (auto& e : bind->m_events)
			{
				switch (e.first)
				{
					case(EventType::Keyboard):
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e.second.m_code)))
						{
							if (bind->m_details.m_keyCode != -1)
								bind->m_details.m_keyCode = e.second.m_code;
							
							++(bind->count);
						}
						break;

					case(EventType::Mouse):
						if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e.second.m_code)))
						{
							if (bind->m_details.m_keyCode != -1)
								bind->m_details.m_keyCode = e.second.m_code;
							
							++(bind->count);
						}
						break;

					case(EventType::Joystick):
						break;
				}
			}

			if (bind->m_events.size() == bind->count) {
				auto stateCallbacks = m_callbacks.find(m_currentState);
				auto otherCallbacks = m_callbacks.find(StateType(0));

				if (stateCallbacks != m_callbacks.end()) {
					auto i = stateCallbacks->second.find(bind->m_name);
					if (i != stateCallbacks->second.end()) {
						// Pass in information about events.
						i->second(&bind->m_details);
					}
				}

				if (otherCallbacks != m_callbacks.end()) {
					auto i = otherCallbacks->second.find(bind->m_name);
					if (i != otherCallbacks->second.end()) {
						// Pass in information about events.
						i->second(&bind->m_details);
					}
				}
			}

			bind->count = 0;
			bind->m_details.Clear();
		}
	}

	void EventManager::LoadBindings()
	{
		std::string delimiter = ":";

		std::ifstream bindings;
		bindings.open("Resources/keys.cfg");

		if (!bindings.is_open())
		{
			std::cout << "Failed loading keys.cfg." << std::endl;
			return;
		}

		std::string line;

		while (std::getline(bindings, line))
		{
			std::stringstream keystream(line);
			std::string callbackName;
			keystream >> callbackName;
			Binding* bind = new Binding(callbackName);

			while (!keystream.eof())
			{
				std::string keyval;
				keystream >> keyval;

				if (keystream.fail())
				{
					keystream.clear();
					break;
				}

				int start = 0;
				int end = keyval.find(delimiter);

				if (end == std::string::npos)
				{
					delete bind;
					bind = nullptr;
					break;
				}

				EventType type = EventType(stoi(keyval.substr(start, end - start)));
				int code = stoi(
					keyval.substr(
						end + delimiter.length(),
						keyval.find(
							delimiter,
							end + delimiter.length()
						)
					)
				);

				EventInfo eventInfo;
				eventInfo.m_code = code;

				bind->BindEvent(type, eventInfo);
			}

			if (!AddBinding(bind))
				delete bind;

			bind = nullptr;
		}

		bindings.close();
	}
}