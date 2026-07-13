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


bool	Game::loadAllImg()
{
	
	if (initPlayerTextureFromSide(TextureID::Player_Idle_Down,
		TextureID::Player_Lift_Down,
		TextureID::Player_Walk_Down,
		TextureID::Player_Drop_Down) == false)
		return (false);
	m_texture->load(TextureID::Chest_Close);
	if (!m_texture->load(TextureID::Chest_Close))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	m_texture->load(TextureID::Chest_Opened);
	if (!m_texture->load(TextureID::Chest_Opened))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	m_texture->load(TextureID::Chest_Opening);
	if (!m_texture->load(TextureID::Chest_Opening))
		return (
			std::cerr << "Texture not load\n",
			false
		);
	// if (initPlayerTextureFromSide(TextureID::Player_Idle_up,
	// 	TextureID::Player_Lift_up,
	// 	TextureID::Player_Walk_up,
	// 	TextureID::Player_Drop_up) == false)
	// 	return (false);
	// if (initPlayerTextureFromSide(TextureID::Player_Idle_Left,
	// 	TextureID::Player_Lift_Left,
	// 	TextureID::Player_Walk_Left,
	// 	TextureID::Player_Drop_Left) == false)
	// 	return (false);
	// if (initPlayerTextureFromSide(TextureID::Player_Idle_Right,
	// 	TextureID::Player_Lift_Right,
	// 	TextureID::Player_Walk_Right,
	// 	TextureID::Player_Drop_Right) == false)
	// 	return (false);
	return (true);
}
