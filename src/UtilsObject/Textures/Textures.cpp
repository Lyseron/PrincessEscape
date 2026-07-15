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
// ---------------------------- PLAYER ------------------------------ //
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

		case TextureID::Player_Idle_Up:
			path = "assets/Player/idle_up.png";
			break;
		case TextureID::Player_Lift_Up:
			path = "assets/Player/lift_up.png";
			break;
		case TextureID::Player_Walk_Up:
			path = "assets/Player/walk_up.png";
			break;
		case TextureID::Player_Drop_Up:
			path = "assets/Player/drop_up.png";
			break;

		case TextureID::Player_Idle_Right:
			path = "assets/Player/idle_right.png";
			break;
		case TextureID::Player_Lift_Right:
			path = "assets/Player/lift_right.png";
			break;
		case TextureID::Player_Walk_Right:
			path = "assets/Player/walk_right.png";
			break;
		case TextureID::Player_Drop_Right:
			path = "assets/Player/drop_right.png";
			break;

		case TextureID::Player_Idle_Left:
			path = "assets/Player/idle_left.png";
			break;
		case TextureID::Player_Lift_Left:
			path = "assets/Player/lift_left.png";
			break;
		case TextureID::Player_Walk_Left:
			path = "assets/Player/walk_left.png";
			break;
		case TextureID::Player_Drop_Left:
			path = "assets/Player/drop_left.png";
			break;

// ---------------------------- WALL ------------------------------ //
		case TextureID::FrontWall:
			path = "assets/Wall/front/FrontWall.png";
			break;
		case TextureID::FrontWall2:
			path = "assets/Wall/front/FrontWall2.png";
			break;
		case TextureID::LeftWall:
			path = "assets/Wall/left/wall_left.png";
			break;
		case TextureID::LeftWall2:
			path = "assets/Wall/left/wall_left2.png";
			break;

		case TextureID::CornerLeftWall:
			path = "assets/Wall/left/corner_left.png";
			break;
		case TextureID::CornerLeftWall2:
			path = "assets/Wall/left/corner_left2.png";
			break;

		case TextureID::CornerRightWall:
			path = "assets/Wall/right/corner_right.png";
			break;
		case TextureID::CornerRightWall2:
			path = "assets/Wall/right/corner_right2.png";
			break;
		case TextureID::RightWall:
			path = "assets/Wall/right/wall_right.png";
			break;
		case TextureID::RightWall2:
			path = "assets/Wall/right/wall_right2.png";
			break;
		case TextureID::DownWall:
			path = "assets/Wall/Down/wall_down.png";
			break;
		case TextureID::DownWall2:
			path = "assets/Wall/Down/wall_down2.png";
			break;

// ---------------------------- FLOOR ------------------------------ //
		case TextureID::Floor:
			path = "assets/floor/floor.png";
			break;

// ---------------------------- DECOR ------------------------------ //

		case TextureID::Chest_Close:
			path = "assets/Chest/chest_close.png";
			break;
		case TextureID::Chest_Opening:
			path = "assets/Chest/chest_opening.png";
			break;
		case TextureID::Chest_Opened:
			path = "assets/Chest/chest_open.png";
			break;
		
		case TextureID::Door_Close:
			path = "assets/Door/door_close.png";
			break;
		case TextureID::Door_Opening:
			path = "assets/Door/door_opening.png";
			break;
		case TextureID::Door_Opened:
			path = "assets/Door/door_open.png";
			break;

		case TextureID::FloatingCandle:
			path = "assets/decor/moving_candle.png";
			break;
		case TextureID::Chandelier:
			path = "assets/decor/chandelier.png";
			break;
		case TextureID::Armure:
			path = "assets/decor/armure.png";
			break;
		default:
			break;
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
		std::cerr << "texture not charged\n" << path << std::endl;
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