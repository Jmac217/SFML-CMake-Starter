#include "pch.h"
#include "Window.h"

namespace Mac {


	Window::Window()
	{
		Setup("Window", sf::Vector2u(640, 480));
	}

	Window::Window(const sf::String& title, const sf::Vector2u& size)
	{
		Setup(title, size);
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::BeginDraw()
	{
		m_window.clear(sf::Color(40, 40, 50));
	}

	void Window::EndDraw()
	{
		m_window.display();
	}

	void Window::Update()
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				m_isDone = true;
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::F5)
				{
					ToggleFullscreen();
				}
				else if
					(event.key.code == sf::Keyboard::Escape)
				{
					m_isDone = true;
				}
			}
		}
	}

	bool Window::IsDone()
	{
		return m_isDone;
	}

	bool Window::IsFullscreen()
	{
		return m_isFullscreen;
	}

	sf::RenderWindow* Window::GetRenderWindow()
	{
		return &m_window;
	}

	sf::Vector2u Window::GetWindowSize()
	{
		return m_windowSize;
	}

	void Window::ToggleFullscreen()
	{
		m_isFullscreen = !m_isFullscreen;
		Destroy();
		Create();
	}

	void Window::Draw(sf::Drawable& l_drawable)
	{
		m_window.draw(l_drawable);
	}

	void Window::Setup(const std::string title, const sf::Vector2u& size)
	{
		m_windowTitle = title;
		m_windowSize = size;
		m_isFullscreen = false;
		m_isDone = false;
		m_window.setFramerateLimit(60);
		Create();
	}

	void Window::Create()
	{
		auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);

		m_window.create({ m_windowSize.x, m_windowSize.y, 32}
		, m_windowTitle
		, style);
	}

	void Window::Destroy()
	{
		m_window.close();
	}

}