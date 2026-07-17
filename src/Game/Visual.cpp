#include "Game.hpp"

void	Game::render()
{
	SDL_SetRenderDrawColor(
		m_renderer,
		40,							// Red
		40,							// Green
		70,							// Blue
		255							// Transparenci
	);
	SDL_RenderClear(m_renderer);	// Clear the img

	drawMap();
	// drawShadowDecor();
	drawDecor();
	drawChests();
	drawDoors();
	drawPlayer();
	// drawDebugInteraction();
	m_ui.drawUI(*this);
	SDL_RenderPresent(m_renderer);	// Display the img
}