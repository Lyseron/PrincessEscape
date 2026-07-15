#include "Game.hpp"

void	Game::VisualChange()
{
	actionInMap();
	m_player.anim();
	m_map.anim();
	for (Chest &chest : m_map.getChestsNotConst())
		chest.animChest();
	for(Door &door : m_map.getDoorsNotConst())
		door.animDoor();
	m_openChest = false;
}
