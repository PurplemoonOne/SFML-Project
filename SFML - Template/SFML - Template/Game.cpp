#include "Game.h"

Game::Game() : m_window("SNAKE", sf::Vector2u(800, 600)),
m_snake(m_world.GetBlockSize()), m_world(sf::Vector2u(800, 600))
{
	m_texture.loadFromFile("Ron_Swanson.png");
	m_sprite.setTexture(m_texture);
	m_incriment = sf::Vector2i(10, 10);
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update();
	MoveMushroom();
	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed >= timestep)
	{
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= timestep;
		if (m_snake.HasLost())
		{
			m_snake.Reset();
		}
	}
}

void Game::MoveMushroom()
{
	sf::Vector2u l_windSize = m_window.GetWindowsSize();
	sf::Vector2u l_textSize = m_texture.getSize();

	float fElasped = m_elapsed.asSeconds();

	if ((m_sprite.getPosition().x > l_windSize.x - l_textSize.x && m_incriment.x > 0)
		||
		(m_sprite.getPosition().x < 0 && m_incriment.x < 0))
	{
		m_incriment.x = -m_incriment.x;
	}

	if ((m_sprite.getPosition().y > l_windSize.y - l_textSize.y && m_incriment.y > 0)
		||
		(m_sprite.getPosition().y < 0 && m_incriment.y < 0))
	{
		m_incriment.y = -m_incriment.y;
	}

	m_sprite.setPosition(m_sprite.getPosition().x + (m_incriment.x * fElasped), m_sprite.getPosition().y + (m_incriment.y * fElasped));


}

Window* Game::GetWindow()
{

	return &m_window;
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetDirection() != Direction::Down)
	{
		m_snake.SetDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetDirection() != Direction::Up)
	{
		m_snake.SetDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetDirection() != Direction::Right)
	{
		m_snake.SetDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetDirection() != Direction::Left)
	{
		m_snake.SetDirection(Direction::Right);
	}
}

void Game::Render()
{
	m_window.BeginDraw();
	//m_window.Draw(m_sprite);

	m_world.Render(*m_window);
	m_snake.Render(*m_window);
	m_window.EndDraw();
}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed = m_clock.getElapsedTime();
}