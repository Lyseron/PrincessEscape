#pragma once

#include <SDL3/SDL.h>
#include <array>
#include <iostream>
#include <string>
#include <SDL3_image/SDL_image.h>

enum	class TextureID			// class -> use TextureID::
{
	Player_Idle_Down,
	Player_Lift_Down,
	Player_Walk_Down,
	Player_Drop_Down,

	// Player_Idle_up,
	// Player_Lift_up,
	// Player_Walk_up,
	// Player_Drop_up,

	// Player_Idle_Left,
	// Player_Lift_Left,
	// Player_Walk_Left,
	// Player_Drop_Left,

	// Player_Idle_Right,
	// Player_Lift_Right,
	// Player_Walk_Right,
	// Player_Drop_Right,

	FrontMovingCandle,
	FrontWall,
	FrontWall2,
	CornerLeftWall,
	CornerLeftWall2,
	LeftWall,
	LeftWall2,
	CornerRightWall,
	CornerRightWall2,
	RightWall,
	RightWall2,
	DownWall,
	DownWall2,

	Chest_Close,
	Chest_Opening,
	Chest_Opened,
	Enemy,
	Wall,
	Floor,
	Door,
	Count
};

class Textures
{
private:
	SDL_Renderer*							m_renderer;
	std::array<SDL_Texture*,
	static_cast<size_t>(TextureID::Count)>	m_textures;
	
public:
	Textures(SDL_Renderer*	renderer);
	~Textures();

	bool			load(TextureID id);
	SDL_Texture*	get(TextureID id)	const;
};
