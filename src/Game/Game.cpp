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

// ---------------------------------------------------- OTHER METHOD ---------------------------------------------------- //

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