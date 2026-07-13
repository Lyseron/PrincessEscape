#include "Textures.hpp"

Textures::Textures(SDL_Renderer* renderer)
	: m_renderer(renderer)
{
	m_textures.fill(nullptr);
}

bool	Textures::load(TextureID id)
{
	std::string	path;

	switch (id)
	{
		case TextureID::Player_Idle_Down:
			path = "assets/Player/idle_armed.png";
			break;
		case TextureID::Player_Lift_Down:
			path = "assets/Player/lift_down.png";
			break;
		case TextureID::Player_Walk_Down:
			path = "assets/Player/walk_down.png";
			break;
		case TextureID::Player_Drop_Down:
			path = "assets/Player/drop_down.png";
			break;
		case TextureID::Chest_Close:
			path = "assets/Chest/chest_close.png";
			break;
		case TextureID::Chest_Opening:
			path = "assets/Chest/chest_opening.png";
			break;
		case TextureID::Chest_Opened:
			path = "assets/Chest/chest_open.png";
			break;
		// case TextureID::Player_Idle_up:
		// 	path = "assets/sprites/idle_armed.png";
		// 	break;
		// case TextureID::Player_Lift_up:
		// 	path = "assets/sprites/lift_up.png";
		// 	break;
		// case TextureID::Player_Walk_up:
		// 	path = "assets/sprites/walk_up.png";
		// 	break;
		// case TextureID::Player_Drop_up:
		// 	path = "assets/sprites/drop_up.png";
		// 	break;

		// case TextureID::Player_Idle_Right:
		// 	path = "assets/sprites/idle_armed.png";
		// 	break;
		// case TextureID::Player_Lift_Right:
		// 	path = "assets/sprites/lift_right.png";
		// 	break;
		// case TextureID::Player_Walk_Right:
		// 	path = "assets/sprites/walk_right.png";
		// 	break;
		// case TextureID::Player_Drop_Right:
		// 	path = "assets/sprites/drop_right.png";
		// 	break;

		// case TextureID::Player_Idle_Left:
		// 	path = "assets/sprites/idle_armed.png";
		// 	break;
		// case TextureID::Player_Lift_Left:
		// 	path = "assets/sprites/lift_left.png";
		// 	break;
		// case TextureID::Player_Walk_Left:
		// 	path = "assets/sprites/walk_left.png";
		// 	break;
		// case TextureID::Player_Drop_Left:
		// 	path = "assets/sprites/drop_left.png";
		// 	break;
		default:
			return (false);
	}
	SDL_Surface*	surface = IMG_Load(path.c_str());			// img store in RAM
	if (surface == nullptr)
		return (false);
	SDL_Texture*	texture = SDL_CreateTextureFromSurface(		// create the img from the surface
		m_renderer,
		surface
	);
	if (texture == nullptr)
	{
		std::cerr << "texture not charged\n";
		SDL_DestroySurface(surface);							// Free the memory
		return (false);
	}
	SDL_DestroySurface(surface);
	m_textures[static_cast<size_t>(id)] = texture;
	return (true);
}

SDL_Texture*	Textures::get(TextureID id)	const
{
	return (m_textures[static_cast<size_t>(id)]);
}

Textures::~Textures()
{
	for (SDL_Texture* texture : m_textures)						// range-based loop for to parcours all element of a tab
	{
		if (texture != nullptr)						
			SDL_DestroyTexture(texture);
	}
}