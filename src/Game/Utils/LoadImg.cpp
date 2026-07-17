#include "Game.hpp"
#include <iostream>
#include <SDL3/SDL.h>

// ------------------------------------------------- TEXTURES --------------------------------------------- //

bool	Game::initPlayerTextureFromSide(TextureID idle, TextureID lift, TextureID walk, TextureID drop)
{
	if (!m_texture->load(idle))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	if (!m_texture->load(lift))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	if (!m_texture->load(walk))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	if (!m_texture->load(drop))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	return (true);
}

bool	Game::loadPlayer()
{
	if (initPlayerTextureFromSide(TextureID::Player_Idle_Down,
		TextureID::Player_Lift_Down,
		TextureID::Player_Walk_Down,
		TextureID::Player_Drop_Down) == false)
			return (false);

	if (initPlayerTextureFromSide(TextureID::Player_Idle_Up,
		TextureID::Player_Lift_Up,
		TextureID::Player_Walk_Up,
		TextureID::Player_Drop_Up) == false)
			return (false);

	if (initPlayerTextureFromSide(TextureID::Player_Idle_Left,
		TextureID::Player_Lift_Left,
		TextureID::Player_Walk_Left,
		TextureID::Player_Drop_Left) == false)
			return (false);

	if (initPlayerTextureFromSide(TextureID::Player_Idle_Right,
		TextureID::Player_Lift_Right,
		TextureID::Player_Walk_Right,
		TextureID::Player_Drop_Right) == false)
			return (false);
	return (true);
}

bool	Game::loadWall()
{
	if (!m_texture->load(TextureID::FrontWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::FrontWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::LeftWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::LeftWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::CornerLeftWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::CornerLeftWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::CornerRightWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::CornerRightWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::DownWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::DownWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::RightWall))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::RightWall2))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Floor))
		return (std::cerr << "Texture not load\n", false);

	return (true);
}

bool	Game::loadDecor()
{
	if (!m_texture->load(TextureID::Chandelier))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::FloatingCandle))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Armure))
		return (std::cerr << "Texture not load\n", false);
	return (true);
}

bool	Game::loadChest()
{
	if (!m_texture->load(TextureID::Chest_Close))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Chest_Opened)) 
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Chest_Opening))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Key_Door))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Potion))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Coin))
		return (std::cerr << "Texture not load\n", false);

	return (true);
}

bool	Game::loadDoor()
{
	if (!m_texture->load(TextureID::Door_Close))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Door_Opened)) 
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Door_Opening))
		return (std::cerr << "Texture not load\n", false);

	return (true);
}

bool	Game::loadUI()
{
	if (!m_texture->load(TextureID::Heart_Empty))
		return (std::cerr << "Texture not load\n", false);

	if (!m_texture->load(TextureID::Heart_Full))
		return (std::cerr << "Texture not load\n", false);

	return (true);
}

bool	Game::loadAllImg()
{
	if (loadPlayer() == false)
		return (false);
	if (loadChest() == false)
		return (false);
	if (loadWall() == false)
		return (false);
	if (loadDecor() == false)
		return (false);
	if (loadDoor() == false)
		return (false);
	if (loadUI() == false)
		return (false);
	return (true);
}
