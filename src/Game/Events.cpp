#include "Game.hpp"

void	Game::handleEvent()
{
	SDL_Event	event;

	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT)		// .type == type of event (here -> close window)
			m_running = false;
		keyPress(event);
		keyRelease(event);
	}
}
