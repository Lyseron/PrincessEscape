#include "Game.hpp"
#include "Textures.hpp"

void	Game::drawRectangle(int x_win, int y_win,
	SDL_Color color)
{
	// if (x_win < 0 
	// 	|| x_win > MAP_WIDTH)
	// 	return ;
	// if (y_win < 0 
	// 	|| y_win > MAP_HEIGHT)
	// 	return ;
	if ((color.r < 0 || color.r > 255)
		|| (color.g < 0 || color.g > 255)
		|| (color.b < 0 || color.b > 255)
		|| (color.a < 0 || color.a > 255))
		return ;

	SDL_FRect	rect;

	rect.x = x_win;
	rect.y = y_win;
	rect.w = CASE_TILE;
	rect.h = CASE_TILE;

	SDL_SetRenderDrawColor(
		m_renderer,
		color.r, color.g, color.b, color.a
	);
	SDL_RenderFillRect(
		m_renderer,
		&rect
	);
}

void	Game::drawTexture(int win_x, int win_y, TextureID id, int frame)
{
	// SDL_Texture *tex = m_texture->get(id);
	// if (tex == nullptr)
	// {
	// 	std::cout << "Texture NULL !" << std::endl;
	// 	return ;
	// }
	SDL_FRect	src;

	src.x = frame * SPRITE_WIDTH;
	src.y = 0;
	src.w = SPRITE_WIDTH;
	src.h = SPRITE_HEIGHT;

	SDL_FRect	dst;

	dst.x = win_x;
	dst.y = win_y;
	dst.w = CASE_TILE;
	dst.h = CASE_TILE;
	SDL_RenderTexture(
		m_renderer,
		m_texture->get(id),
		&src,
		&dst
	);
}

void	Game::drawMapComponent(int x, int y, TextureID texture, char c, int frame)
{
	int	win_x = x * CASE_TILE;
	int	win_y = y * CASE_TILE;

	if (m_map.getCharFromTile(x, y) == c)
		drawTexture(
			win_x,
			win_y,
			texture,
			frame
		);
}

void	Game::drawMap()
{
	for (int y = 0; y < m_map.getHeight(); y++)
	{
		for (int x = 0; x < m_map.getWidth(); x++)
		{
			int	win_x = x * CASE_TILE;
			int	win_y = y * CASE_TILE;
			drawMapComponent(x, y, TextureID::FrontWall, 'h', 0);
			drawMapComponent(x, y, TextureID::FrontWall2, 'H', 0);
			drawMapComponent(x, y, TextureID::LeftWall, 'L', 0);
			drawMapComponent(x, y, TextureID::LeftWall2, 'l', 0);
			drawMapComponent(x, y, TextureID::CornerLeftWall, '{', 0);
			drawMapComponent(x, y, TextureID::CornerRightWall2, '}', 0);
			drawMapComponent(x, y, TextureID::CornerLeftWall2, '(', 0);
			drawMapComponent(x, y, TextureID::CornerRightWall, ')', 0);
			drawMapComponent(x, y, TextureID::FrontMovingCandle, 'Q', m_map.getCurrentFrame());
			drawMapComponent(x, y, TextureID::Floor, '.', 0);
			drawMapComponent(x, y, TextureID::DownWall, 'b', 0);
			drawMapComponent(x, y, TextureID::DownWall2, 'B', 0);
			drawMapComponent(x, y, TextureID::RightWall, 'r', 0);
			drawMapComponent(x, y, TextureID::RightWall2, 'R', 0);
		}
	}
}

void	Game::drawPlayer()
{
	TextureID	texture;

	switch (m_player.getState())
	{
		case PlayerState::Idle_Down:
			texture = TextureID::Player_Idle_Down;
			break;
		case PlayerState::Lift_Down:
			texture = TextureID::Player_Lift_Down;
			break;
		case PlayerState::Walk_Down:
			texture = TextureID::Player_Walk_Down;
			break;
		case PlayerState::Drop_Down:
			texture = TextureID::Player_Drop_Down;
			break;

		// case PlayerState::Idle_Up:
		// 	texture = TextureID::Player_Idle_up;
		// 	break;
		// case PlayerState::Lift_Up:
		// 	texture = TextureID::Player_Lift_up;
		// 	break;
		// case PlayerState::Walk_Up:
		// 	texture = TextureID::Player_Walk_up;
		// 	break;
		// case PlayerState::Drop_Up:
		// 	texture = TextureID::Player_Drop_up;
		// 	break;

		// case PlayerState::Idle_Right:
		// 	texture = TextureID::Player_Idle_Right;
		// 	break;
		// case PlayerState::Lift_Right:
		// 	texture = TextureID::Player_Lift_Right;
		// 	break;
		// case PlayerState::Walk_Right:
		// 	texture = TextureID::Player_Walk_Right;
		// 	break;
		// case PlayerState::Drop_Right:
		// 	texture = TextureID::Player_Drop_Right;
		// 	break;

		// case PlayerState::Idle_Left:
		// 	texture = TextureID::Player_Idle_Left;
		// 	break;
		// case PlayerState::Lift_Left:
		// 	texture = TextureID::Player_Lift_Left;
		// 	break;
		// case PlayerState::Walk_Left:
		// 	texture = TextureID::Player_Walk_Left;
		// 	break;
		// case PlayerState::Drop_Left:
		// 	texture = TextureID::Player_Drop_Left;
		// 	break;
	}
	drawTexture((
				m_player.getPosX() - 0.5) * CASE_TILE,
				(m_player.getPosY() - 0.5) * CASE_TILE, 
				texture,
				m_player.getCurrentFrame()
			);
}

void	Game::drawChests()
{
	TextureID	texture;

	for (const Chest &chest : m_map.getChests())
	{
		switch (chest.getChestState())
		{
		case ChestState::Closed:
			texture = TextureID::Chest_Close;
			break;
		case ChestState::Opening:
			texture = TextureID::Chest_Opening;
			break;
		case ChestState::Opened:
			texture = TextureID::Chest_Opened;
			break;
		}
			drawTexture(
				chest.getCaseX() * CASE_TILE,
				chest.getCaseY() * CASE_TILE,
				texture,
				chest.getCurrentFrame()
			);
	}
}
