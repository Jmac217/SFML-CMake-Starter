#include "Game.h"

namespace Mac {

	Game::Game()
	{
		this->initWindow();
		this->initTextures();
		this->initGUI();
		this->initWorld();
		this->initSystems();
		this->initPlayer();
		this->initEnemies();
	}

	Game::~Game()
	{
		delete this->window;
		delete this->player;

		for (auto& t : this->textures)
		{
			delete t.second;
		}

		for (auto* b : this->bullets)
		{
			delete b;
		}

		for (auto* e : this->enemies)
		{
			delete e;
		}
	}

	void Game::Run()
	{
		while (this->window->isOpen())
		{
			this->UpdatePollEvents();

			if (this->player->getHP() > 0)
				this->Update();

			this->Render();
		}
	}

	void Game::UpdatePollEvents()
	{
		sf::Event e;
		while (this->window->pollEvent(e))
		{
			if (e.Event::type == sf::Event::Closed
				|| (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape))
				this->window->close();
		}
	}

	void Game::UpdateInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->player->Move(-1.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->player->Move(1.0f, 0.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			this->player->Move(0.0f, -1.0f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			this->player->Move(0.0f, 1.0f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
		{
			this->bullets.push_back(
					new Bullet(
						this->textures["BULLET"]	// Texture
					,	this->player->getPos().x
					+	this->player->getBounds()
					.	width/2.0f					// X Spawn Position
					,	this->player->getPos().y	// Y Spawn Position
					,	 0.0f						// X Velocity
					,	-1.0f						// Y Velocity
					,	 8.0f						// Speed
				)
			);
		}
		
	}

	void Game::UpdateGUI()
	{
		std::stringstream ss;
		ss << "Points: " << this->points << std::endl;
		this->pointText.setString(ss.str());

		float HPPercent = static_cast<float>(this->player->getHP()) / this->player->getHPMax();
		this->PlayerHPBar.setSize(sf::Vector2f(300.0f * HPPercent, this->PlayerHPBar.getSize().y));
	}

	void Game::UpdateBullets()
	{
		unsigned int counter = 0;
		for (auto* bullet : this->bullets)
		{
			bullet->Update();

			// cull top of screen
			if (bullet->getBounds().top + bullet->getBounds().height < 0.0f)
			{
				delete this->bullets.at(counter);
				this->bullets.erase(this->bullets.begin() + counter);
				--counter;
			}
			++counter;
		}
	}

	void Game::UpdateEnemies()
	{
		//Spawning
		this->spawnTimer += 0.5f;
		if (this->spawnTimer >= this->spawnTimerMax)
		{
			this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
			this->spawnTimer = 0.f;
		}

		// Update
		unsigned counter = 0;
		for (auto* enemy : this->enemies)
		{
			enemy->update();

			// Bullet culling
			if (enemy->getBounds().top > this->window->getSize().y)
			{
				// Delete bullet
				delete this->enemies.at(counter);
				this->enemies.erase(this->enemies.begin() + counter);
			}
			else if (enemy->getBounds().intersects(this->player->getBounds()))
			{
				this->player->loseHP(this->enemies.at(counter)->getDamage());
				delete this->enemies.at(counter);
				this->enemies.erase(this->enemies.begin() + counter);
			}

			++counter;
		}
	}

	void Game::UpdateCombat()
	{
		for (int i = 0; i < this->enemies.size(); ++i)
		{
			bool enemy_deleted = false;
			for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
			{
				if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
				{
					// Add Points
					this->points += this->enemies[i]->getPoints();

					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);

					delete this->bullets[k];
					this->bullets.erase(this->bullets.begin() + k);

					enemy_deleted = true;
				}
			}
		}
	}

	void Game::UpdateWorld()
	{

	}

	void Game::UpdateCollision()
	{
		if (this->player->getBounds().left < 0.0f)
			this->player->setPosition(0.0f, this->player->getBounds().top);
		else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
			this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
		if (this->player->getBounds().top < 0.0f)
			this->player->setPosition(this->player->getBounds().left, 0.0f);
		else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
			this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);


	}

	void Game::Update()
	{
		this->UpdateInput();
		this->player->Update();
		this->UpdateCollision();
		this->UpdateBullets();
		this->UpdateEnemies();
		this->UpdateCombat();
		this->UpdateGUI();
		this->UpdateWorld();
	}

	void Game::RenderGUI()
	{
		this->window->draw(this->pointText);
		this->window->draw(this->PlayerHPBarBack);
		this->window->draw(this->PlayerHPBar);
	}

	void Game::RenderWorld()
	{
		this->window->draw(this->WorldSprite);
	}

	void Game::Render()
	{	
		// Begin Loop
		this->window->clear();
		// -------------------

		this->RenderWorld();

		// GAME LOOP HERE
		this->player->Render(*this->window);

		for (auto* bullet : this->bullets)
		{
			bullet->Render(this->window);
		}

		//Delete enemies
		for (auto* enemy : this->enemies)
		{
			enemy->render(this->window);
		}

		this->RenderGUI();

		if (this->player->getHP() <= 0)
			this->window->draw(this->GameOverText);

		// -------------------
		this->window->display();
		// End Loop
	}

	void Game::initWindow()
	{
		this->window = new sf::RenderWindow(
			sf::VideoMode(800, 600)
			, "SFML - Space Shooter"
			, sf::Style::Close | sf::Style::Titlebar);

		this->window->setFramerateLimit(60);
		this->window->setVerticalSyncEnabled(false);
	}

	void Game::initTextures()
	{
		this->textures["BULLET"] = new sf::Texture();
		this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	}

	void Game::initWorld()
	{
		this->WorldTexture.loadFromFile("Textures/background.png");
		this->WorldSprite.setTexture(WorldTexture);
	}

	void Game::initSystems()
	{
		this->points = 0;
	}

	void Game::initPlayer()
	{
		this->player = new Player();
		this->player->setPosition(400.0f, 700.0f);
	}

	void Game::initEnemies()
	{
		this->spawnTimerMax = 5.0f;
		this->spawnTimer = this->spawnTimerMax;
	}

	void Game::initGUI()
	{
		this->font.loadFromFile("Fonts/FiraCode-Bold.ttf");

		this->pointText.setFont(font);
		this->pointText.setCharacterSize(28);
		this->pointText.setPosition(550.0f, 5.0f);
		this->pointText.setColor(sf::Color::White);
		this->pointText.setString("Points: 0");

		this->GameOverText.setFont(font);
		this->GameOverText.setCharacterSize(60);
		this->GameOverText.setPosition(
			this->window->getSize().x / 3.25f - this->GameOverText.getGlobalBounds().width / 2.0f,
			this->window->getSize().y / 2.0f - this->GameOverText.getGlobalBounds().height / 2.0f);
		this->GameOverText.setColor(sf::Color::Red);
		this->GameOverText.setString("Game Over!");

		this->PlayerHPBar.setSize(sf::Vector2f(300.0f, 28.0f));
		this->PlayerHPBar.setFillColor(sf::Color::Red);
		this->PlayerHPBar.setPosition(sf::Vector2f(60.0f, 5.0f));

		this->PlayerHPBarBack = this->PlayerHPBar;
		this->PlayerHPBarBack.setFillColor(sf::Color(25, 25, 25, 200));
	}

}