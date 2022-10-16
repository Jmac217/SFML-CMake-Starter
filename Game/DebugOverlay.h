#pragma once

namespace Mac {

	struct DebugOverlay
	{
		DebugOverlay()
		{
			m_debug = false;
		}

		void Add(sf::Drawable* l_drawable)
		{
			m_drawables.push_back(l_drawable);
		}

		void Draw(sf::RenderWindow* l_window)
		{
			while (m_drawables.begin() != m_drawables.end())
			{
				l_window->draw(*m_drawables.back());
				delete m_drawables.back();
				m_drawables.pop_back();
			}
		}

		bool Debug()
		{
			return m_debug;
		}

		void SetDebug(const bool& l_value)
		{
			m_debug = l_value;
		}

	private:
		std::vector<sf::Drawable*> m_drawables;
		bool m_debug;
	};
}