#include "Game.hpp"

void	Game::update()
{
	actionInMap();
	m_player.anim();
	for (Chest &chest : m_map.getChestsNotConst())
		chest.anim();
}
