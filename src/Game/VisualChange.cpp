#include "Door.hpp"
#include "Game.hpp"
#include "Inventory.hpp"

void	Game::VisualChange()
{
	actionKeyPress();
	m_player.anim(m_deltaTime);
	m_map.anim(m_deltaTime);
	for (Chest &chest : m_map.getChests())
	{
		chest.animChest(m_deltaTime);
		if (chest.getChestState() == ChestState::Opened
			&& chest.hasLootBeenTaken() == false)
		{
			m_player.addItem(chest.getLoot());
			chest.setShowLoot(true);
			chest.setLootTaken(true);
		}
	}
	for (Door &door : m_map.getDoors())
	{
		if (door.getDoorState() == DoorState::Closed
			&& m_player.canInteract(door)
			&& m_player.hasItem(Item::Key_Door))
			{
				m_player.removeItem(Item::Key_Door);
				door.interact(m_player);
			}

		door.animDoor(m_deltaTime);
		if (door.getDoorState() == DoorState::Opened)
		{
			if (m_map.load("mapsFiles/mapLevel_1.txt") == false)
				return ;
			initPlayer();
			return ;
		}
	}
	m_enemy.update(*this);
	m_oPressed = false;
}
