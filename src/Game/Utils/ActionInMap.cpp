#include "Game.hpp"

void	Game::actionInMap()
{
	handleMovement();
	if (m_openChest)
	{
		for (Chest &chest : m_map.getChestsNotConst())
		{
			if (m_player.getCaseXinFrontOfPlayer() == chest.getCaseX()
				&& m_player.getCaseYinFrontOfPlayer() == chest.getCaseY())
			{
				chest.interact(m_player);
				return ;
			}
		}
	}
}