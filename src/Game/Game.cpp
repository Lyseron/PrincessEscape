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
	m_walCollision({0,0,1,1}),
	m_enemy(1, 1, 5, 1, true, 1, 0)
{
	if (!initAll())
		return ;
	m_running = true;									// bool to continue the game on a loop
}

Game::~Game()
{
	delete m_texture;
	if (m_renderer)
		SDL_DestroyRenderer(m_renderer);
	if (m_window)
		SDL_DestroyWindow(m_window);			// To destroy the pointer at the end
	SDL_Quit();											// Clean everything
}

// ---------------------------------------------------- GETTER ---------------------------------------------------------- //

Player	&Game::getPlayer() { return (this->m_player); }

SDL_Renderer*	Game::getRenderer() { return (this->m_renderer); }

int	Game::getCaseTile() { return (CASE_TILE); }

bool	Game::isInventoryOpen() { return (this->m_isInventoryOpen); }

double	Game::getDeltaTime() const { return (this->m_deltaTime); }

// ---------------------------------------------------- OTHER METHOD ---------------------------------------------------- //

void Game::useSelectedItem()
{
	Item item = m_player.getInventory().getSelectedItem();

	switch (item)
	{
		case Item::Potion:
			m_player.heal(1);
			m_player.getInventory().removeItem(item);
			break;

		default:
			break;
	}
}

void	Game::run()
{
	Uint64	lastTime = SDL_GetTicks();

	while (m_running)
	{
		const Uint64	currentTime = SDL_GetTicks();
		m_deltaTime = static_cast<double>(currentTime - lastTime) / 1000.0;
		lastTime = currentTime;

		// Avoid a large movement jump after a temporary pause.
		if (m_deltaTime > 0.05)
			m_deltaTime = 0.05;

		this->handleEvent();
		this->VisualChange();
		this->render();
	}
	std::cout << "Game running\n";
}
