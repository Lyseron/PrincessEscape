#include "Game.hpp"
#include <iostream>
#include <SDL3/SDL.h>


// ------------------------------------------------- INIT ------------------------------------------------- //

bool	Game::initMaps()
{
	if (m_map.load("mapsFiles/mapLevel_0.txt") == false)
		return (false);
	return (true);
}

void	Game::initColors()
{
	m_wallColor = {51, 0, 102, 255};
	m_floorColor = {96, 96, 96, 255};
}

bool	Game::initSDL()
{
	if (!SDL_Init(SDL_INIT_VIDEO))					// Init
		return (
			std::cerr << "SDL_Init failed: " 
				<< SDL_GetError() << std::endl,		// Get the right ERROR string
			false
		);
	return (true);
}

bool	Game::initWindow()
{
	this->m_window = SDL_CreateWindow(			// To create the window -> return a pointer
		"Princess Escape",						// Title of the window
		m_map.getWidth() * CASE_TILE,								// Width of the window
		m_map.getHeight() * CASE_TILE,								// Height of the window
		SDL_WINDOW_RESIZABLE					// Option to be able the resize the window
	);
	if (!this->m_window) 						// Check if the pointer is NULL
		return (
			std::cerr << "SDL_CreateWindow failed: " 
				<< SDL_GetError() << std::endl,		// Get the right ERROR string
			SDL_Quit(),
		false
		);
	return (true);
}

bool	Game::initRenderer()
{
	this->m_renderer = SDL_CreateRenderer(this->m_window, nullptr);	// Create an pointer to draw in the window
	if (!m_renderer) 												// Check if the pointer is NULL
		return (
			std::cerr << "SDL_CreateRenderer failed: "
				<< SDL_GetError() << std::endl,						// Get the right ERROR string
			SDL_DestroyWindow(this->m_window),
			SDL_Quit(), 
			false
		);
	return (true);
}

void	Game::initPlayer()
{
	m_player.setX(static_cast<double>(m_map.getFirstPlayerPosX()));
	m_player.setY(static_cast<double>(m_map.getFirstPlayerPosY()));
}

bool	Game::initAll()
{
	if (!initMaps())
	{
		std::cout << "ERROR: Map not found or Player not there\n";
		return (false);
	}
	std::cout << "CHest nb: " << m_map.getChestCount() << std::endl;
	initColors();
	initPlayer();
	if (!initSDL() || !initWindow() || !initRenderer())			// in GameUtils.cpp
		return (false);
	m_texture = new Textures(m_renderer);						// allocate the class Textures
	if (!m_texture)
	{
		std::cerr << "ERROR: Cannot create texture class\n";
		return (false);
	}
	if (!loadAllImg())
		return (false);
	return (true);
}