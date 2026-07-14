#include "Game.hpp"
#include <iostream>
#include <SDL3/SDL.h>

// ------------------------------------------------- TEXTURES --------------------------------------------- //

bool	Game::initPlayerTextureFromSide(TextureID idle, TextureID lift, TextureID walk, TextureID drop)
{
	m_texture->load(idle);						// load a texture
	if (!m_texture->load(idle))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	m_texture->load(lift);						// load a texture
	if (!m_texture->load(lift))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	m_texture->load(walk);						// load a texture
	if (!m_texture->load(walk))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	m_texture->load(drop);						// load a texture
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
	m_texture->load(TextureID::FrontWall);
	if (!m_texture->load(TextureID::FrontWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::FrontWall2);
	if (!m_texture->load(TextureID::FrontWall2))
		return (std::cerr << "Texture not load\n", false);
	
	m_texture->load(TextureID::FrontMovingCandle);
	if (!m_texture->load(TextureID::FrontMovingCandle))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::LeftWall);
	if (!m_texture->load(TextureID::LeftWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::LeftWall2);
	if (!m_texture->load(TextureID::LeftWall2))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::CornerLeftWall);
	if (!m_texture->load(TextureID::CornerLeftWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::CornerLeftWall2);
	if (!m_texture->load(TextureID::CornerLeftWall2))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::CornerRightWall);
	if (!m_texture->load(TextureID::CornerRightWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::CornerRightWall2);
	if (!m_texture->load(TextureID::CornerRightWall2))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::DownWall);
	if (!m_texture->load(TextureID::DownWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::DownWall2);
	if (!m_texture->load(TextureID::DownWall2))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::RightWall);
	if (!m_texture->load(TextureID::RightWall))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::RightWall2);
	if (!m_texture->load(TextureID::RightWall2))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::Floor);
	if (!m_texture->load(TextureID::Floor))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::Chandelier);
	if (!m_texture->load(TextureID::Chandelier))
		return (std::cerr << "Texture not load\n", false);
	return (true);
}

bool	Game::loadChest()
{
	m_texture->load(TextureID::Chest_Close);
	if (!m_texture->load(TextureID::Chest_Close))
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::Chest_Opened);
	if (!m_texture->load(TextureID::Chest_Opened)) 
		return (std::cerr << "Texture not load\n", false);

	m_texture->load(TextureID::Chest_Opening);
	if (!m_texture->load(TextureID::Chest_Opening))
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
	return (true);
}
