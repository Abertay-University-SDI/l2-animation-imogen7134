#include "Level.h"
#include "Player.h"


Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	if (!m_sheep.loadFromFile("gfx/sheep_sheet.png"))
		std::cerr << "No sheep image found\n";
	m_player.setTexture(&m_sheep, true);
	m_player.setPosition({ 0,0 });
	m_player.setSize({ 64, 64 });
	m_player.setTextureRect(sf::IntRect({ 0,0 }, { 64, 64 }));
	m_player.setInput(&m_input);

}

// handle user input
void Level::handleInput(float dt)
{
	if (m_gameOver) return;
	m_player.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	if (m_gameOver) return;

	
	// check wall collision
	sf::Vector2f pos = m_player.getPosition();
	float radius = m_player.getSize().x;

	if (pos.x < 0 || pos.x + radius > m_window.getSize().x || pos.y < 0 || pos.y + radius > m_window.getSize().y)
	{
		m_gameOver = true;
		std::cout << "Game over";
	}
	m_player.update(dt);

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player);
	endDraw();
}

