#include "Door.hpp"
#include "Game.hpp"
#include "Inventory.hpp"

void	Game::VisualChange()
{
	actionKeyPress();
	m_player.anim();
	m_map.anim();
	for (Chest &chest : m_map.getChestsNotConst())
	{
		chest.animChest();
		if (chest.getChestState() == ChestState::Opened
			&& chest.hasLootBeenTaken() == false)
		{
			m_player.addItem(Item::Key_Door);
			chest.setShowLoot(true);
			chest.setLootTaken(true);
		}
	}
	for (Door &door : m_map.getDoorsNotConst())
	{
		if (door.getDoorState() == DoorState::Closed
			&& m_player.canInteract(door)
			&& m_player.hasItem(Item::Key_Door))
			{
				m_player.removeItem(Item::Key_Door);
				door.interact(m_player);
			}

		door.animDoor();
		if (door.getDoorState() == DoorState::Opened)
		{
			if (m_map.load("mapsFiles/mapLevel_1.txt") == false)
				return ;
			initPlayer();
			return ;
		}
	}
	m_oPressed = false;
}
