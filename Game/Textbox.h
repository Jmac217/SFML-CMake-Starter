#pragma once

namespace Mac {

	using MessageContainer = std::vector<std::string>;

	struct Textbox
	{
		Textbox();
		Textbox(int l_visible,
				int l_charSize,
				int l_width,
				sf::Vector2f l_screenPos);
		~Textbox();

		void Setup(	int l_visible,
					int l_charSize,
					int l_width,
					sf::Vector2f l_screenPos);

		void Add(std::string l_message);
		void Clear();

		void Render(sf::RenderWindow& l_window);
	private:
		MessageContainer m_messages;
		int m_numVisible;

		sf::RectangleShape m_backdrop;
		sf::Font m_font;
		sf::Text m_content;
	};
}