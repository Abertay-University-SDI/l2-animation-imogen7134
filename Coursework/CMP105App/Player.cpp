#include "Player.h"

Player::Player()
{
	for (int i = 0; i < 4; i++)
	{
		m_walkDown.addFrame(sf::IntRect({ i * 64,0 }, { 64,64 }));
	}
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(1.f / 4.f);
	

	for (int i = 4; i < 8; i++)
	{
		m_walkUp.addFrame(sf::IntRect({ i * 64,0 }, { 64,64 }));
	}
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(1.f / 4.f);
	

	for (int i = 4; i < 8; i++)
	{
		m_walkRight.addFrame(sf::IntRect({ (i * 64),65 }, { 64,64 }));
	}
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(1.f / 4.f);
	

	for (int i = 0; i < 4; i++)
	{
		m_walkDownRight.addFrame(sf::IntRect({ (i * 64),129 }, { 64,64 }));
	}
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(1.f / 4.f);
	

	for (int i = 0; i < 4; i++)
	{
		m_walkUpRight.addFrame(sf::IntRect({ (i * 64),65 }, { 64,64 }));
	}
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(1.f / 4.f);
	

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

void Player::update(float dt)
{
	
	m_currentAnimation->animate(dt);
	setTextureRect(m_currentAnimation->getCurrentFrame());

	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		move({ 0, -orthog_speed });
		m_currentAnimation = &m_walkUp;
		break;
	case Direction::UP_RIGHT:
		move({ diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpRight;
		m_currentAnimation->setFlipped(false);
		break;
	case Direction::RIGHT:
		move({ orthog_speed,0 });
		m_currentAnimation = &m_walkRight;
		m_currentAnimation->setFlipped(false);
		break;
	case Direction::DOWN_RIGHT:
		move({ diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownRight;
		m_currentAnimation->setFlipped(false);
		break;
	case Direction::DOWN:
		move({ 0, orthog_speed });
		m_currentAnimation = &m_walkDown;
		break;
	case Direction::DOWN_LEFT:
		move({ -diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownRight;
		m_currentAnimation->setFlipped(true);
		break;
	case Direction::LEFT:
		move({ -orthog_speed,0 });
		m_currentAnimation = &m_walkRight;
		m_currentAnimation->setFlipped(true);
		break;
	case Direction::UP_LEFT:
		move({ -diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpRight;
		m_currentAnimation->setFlipped(true);
		break;
	}

}

void Player::handleInput(float dt)
{
	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}

	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir)
		m_inputBuffer = INPUT_BUFFER_LENGTH;
}

