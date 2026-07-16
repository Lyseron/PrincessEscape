#include "Game.hpp"

void	Game::keyPress(SDL_Event event)
{
	if (event.type == SDL_EVENT_KEY_DOWN)
	{
		if (event.key.key == SDLK_UP || event.key.key == SDLK_W)
			m_upPressed = true;
		else if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S)
			m_downPressed = true;
		else if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
			m_leftPressed = true;
		else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
			m_rightPressed = true;
		else if (event.key.key == SDLK_O)
			m_oPressed = true;
	}
}

void	Game::keyRelease(SDL_Event event)
{
	if (event.type == SDL_EVENT_KEY_UP)
	{
		if (event.key.key == SDLK_UP || event.key.key == SDLK_W)
			m_upPressed = false;
		else if (event.key.key == SDLK_LEFT || event.key.key == SDLK_A)
			m_leftPressed = false;
		else if (event.key.key == SDLK_RIGHT || event.key.key == SDLK_D)
			m_rightPressed = false;
		else if (event.key.key == SDLK_DOWN || event.key.key == SDLK_S)
			m_downPressed = false;
	}
}

void	Game::actionKeyPress()
{
	handleMovement();
	if (m_oPressed)
	{
		for (Chest &chest : m_map.getChestsNotConst())
		{
			if (m_player.canInteract(chest))
			{
				chest.interact(m_player);
				return ;
			}
		}
	}
}
