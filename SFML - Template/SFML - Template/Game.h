#pragma once
#include "Window.h"
#include "Snake.h"
#include "World.h"



class Game
{
public:

	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();
	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;

private:

	void MoveMushroom();
	Window m_window;

	World m_world;
	Snake m_snake;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2i m_incriment;

};