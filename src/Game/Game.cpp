#include "Game.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Game::Game()
	: m_running(false),
	m_window(nullptr),
	m_renderer(nullptr),
	m_texture(nullptr),
	m_upPressed(false),
	m_leftPressed(false),
	m_rightPressed(false),
	m_downPressed(false),
	m_oPressed(false),
	m_walCollision({0,0,1,1})
{
	if (!initAll())
		return ;
	m_running = true;									// bool to continue the game on a loop
}

Game::~Game()
{
	if (m_renderer)
		SDL_DestroyRenderer(m_renderer);
	if (m_window)
		SDL_DestroyWindow(m_window);			// To destroy the pointer at the end
	delete m_texture;
	SDL_Quit();											// Clean everything
}

// ---------------------------------------------------- GETTER ---------------------------------------------------------- //

Player	&Game::getPlayer() { return (this->m_player); }

SDL_Renderer*	Game::getRenderer() { return (this->m_renderer); }

int	Game::getCaseTile() { return (CASE_TILE); }

bool	Game::isInventoryOpen() { return (this->m_isInventoryOpen); }

// ---------------------------------------------------- OTHER METHOD ---------------------------------------------------- //

void Game::useSelectedItem()
{
	Item item = m_player.getInventory().getSelectedItem();

	switch (item)
	{
		case Item::Potion:
			m_player.heal(2);
			m_player.getInventory().removeItem(item);
			break;

		default:
			break;
	}
}

void	Game::run()
{
	while (m_running)
	{
		this->handleEvent();
		this->VisualChange();
		this->render();
	}
	std::cout << "Game running\n";
}