#include "Game.hpp"

void	Game::update()
{
	actionInMap();
	m_player.anim();
	m_map.anim();
	for (Chest &chest : m_map.getChestsNotConst())
	{
		chest.anim();
		m_openChest = false;
	}
	
}
