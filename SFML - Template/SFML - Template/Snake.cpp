#include "Snake.h"

Snake::Snake(int l_blockSize)
{
	m_size = l_blockSize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset();
}

Snake::~Snake()
{}

void Snake::Reset()
{
	m_snakeBody.clear();

	m_snakeBody.push_back(SnakeSegement(5, 7));
	m_snakeBody.push_back(SnakeSegement(5, 6));
	m_snakeBody.push_back(SnakeSegement(5, 5));

	SetDirection(Direction::None);

	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::SetDirection(Direction l_dir) { m_dir = l_dir; }

Direction Snake::GetDirection() { return m_dir; }

int Snake::GetSpeed() { return m_speed; }

sf::Vector2i Snake::GetPosition()
{
	return (!m_snakeBody.empty() ? m_snakeBody.front().position : sf::Vector2i(1, 1));
}

int Snake::GetScore() { return m_score; }

int Snake::GetLives() { return m_lives; }

void Snake::IncreaseScore() { m_score += 10; }

bool Snake::HasLost() { return m_lost; }

void Snake::Lose() { m_lost = true; }

void Snake::ToggleLost() { m_lost = !m_lost; }


void Snake::Extend()
{
	if (m_snakeBody.empty()) { return; }
	SnakeSegement& tail_head = m_snakeBody[m_snakeBody.size() - 1];

	if (m_snakeBody.size() > 1)
	{
		SnakeSegement& tail_bone = m_snakeBody[m_snakeBody.size() - 2];


		if (tail_head.position.x == tail_bone.position.x)
		{

			if (tail_head.position.y > tail_bone.position.y)
			{
				m_snakeBody.push_back(SnakeSegement(tail_head.position.x, tail_head.position.y + 1));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegement(tail_head.position.x, tail_head.position.y - 1));
			}
		
		}
		else if (tail_head.position.y == tail_bone.position.y)
		{
			if (tail_head.position.x > tail_bone.position.x)
			{
				m_snakeBody.push_back(SnakeSegement(tail_head.position.x + 1, tail_head.position.y));
			}
			else
			{
				m_snakeBody.push_back(SnakeSegement(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else
	{
		if (m_dir == Direction::Up)
		{
			m_snakeBody.push_back(SnakeSegement(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (m_dir == Direction::Down)
		{
			m_snakeBody.push_back(SnakeSegement(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (m_dir == Direction::Left)
		{
			m_snakeBody.push_back(SnakeSegement(tail_head.position.x + 1, tail_head.position.y));
		}
		else if (m_dir == Direction::Right)
		{
			m_snakeBody.push_back(SnakeSegement(tail_head.position.x, tail_head.position.y));
		}
	}
}


void Snake::Tick()
{
	if (m_snakeBody.empty()) { return; }
	if (m_dir == Direction::None) { return; }

	Move();
	CheckCollision();
}

void Snake::Move()
{
	for (int i = m_snakeBody.size() - 1; i > 0; --i)
	{
		m_snakeBody[i].poistion = m_snakeBody[i - 1].position;
	}
	if (m_dir == Direction::Left)
	{
		--m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Right)
	{
		++m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Up)
	{
		--m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Right)
	{
		++m_snakeBody[0].position.y;
	}
}

void Snake::CheckCollision()
{
	if (m_snakeBody.size() < 5) { return; }

	SnakeSegement& head = m_snakeBody.front() + 1;
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		if (itr->postion == head.position)
		{
			int segements = m_snakeBody.end() - itr;
			Cut(segements);
			break;
		}
	}
}

void Snake::Cut(int l_segements)
{
	for (int i = 0; i < l_segements; ++i)
	{
		m_snakeBody.pop_back();
	}
	--m_lives;
	if (!m_lives) { Lose(); return; }
}

void Snake::Render(sf::RenderWindow& l_window)
{
	if (m_snakeBody.empty()) { return; }

	auto head = m_snakeBody.begin();
	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);
	l_window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr)
	{
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		l_window.draw(m_bodyRect);
	}

}