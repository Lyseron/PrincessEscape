#include "Game.hpp"
#include "Textures.hpp"

void Game::drawDebugInteraction()
{
	double posX = m_player.getPosX() + m_player.getDirX();
	double posY = m_player.getPosY() + m_player.getDirY();

	drawDebugCollision(
	m_player.getCollisionValue(),
	posX,
	posY
);
}

void Game::drawDebugCollision(const Collision &collision, double posX, double posY)
{
	Bound bound = collision.getBoundsObjectInCase(posX, posY);

	SDL_FRect rect;

	rect.x = bound.left * CASE_TILE;
	rect.y = bound.top * CASE_TILE;
	rect.w = (bound.right - bound.left) * CASE_TILE;
	rect.h = (bound.bottom - bound.top) * CASE_TILE;

	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderRect(m_renderer, &rect);
}

void Game::drawDebugCase(double caseX, double caseY)
{
	SDL_FRect rect;

	rect.x = caseX * CASE_TILE;
	rect.y = caseY * CASE_TILE;
	rect.w = CASE_TILE;
	rect.h = CASE_TILE;

	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	SDL_RenderRect(m_renderer, &rect);
}

void	Game::drawTexture(float win_x, float win_y, TextureID id, int frame)
{
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

void	Game::drawTextureScale(float win_x, float win_y, TextureID id, int frame, float scale)
{
	SDL_FRect	src;

	src.x = frame * SPRITE_WIDTH;
	src.y = 0;
	src.w = SPRITE_WIDTH;
	src.h = SPRITE_HEIGHT;

	SDL_FRect	dst;

	dst.x = win_x;
	dst.y = win_y;
	dst.w = CASE_TILE * scale;
	dst.h = CASE_TILE * scale;
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
// ---------------------------------------------------- WALL ---------------------------------------------------- //
			drawMapComponent(x, y, TextureID::FrontWall, 'h', 0);
			drawMapComponent(x, y, TextureID::FrontWall2, 'H', 0);
			drawMapComponent(x, y, TextureID::LeftWall, 'L', 0);
			drawMapComponent(x, y, TextureID::LeftWall2, 'l', 0);
			drawMapComponent(x, y, TextureID::CornerLeftWall, '{', 0);
			drawMapComponent(x, y, TextureID::CornerRightWall2, '}', 0);
			drawMapComponent(x, y, TextureID::CornerLeftWall2, '(', 0);
			drawMapComponent(x, y, TextureID::CornerRightWall, ')', 0);
			drawMapComponent(x, y, TextureID::DownWall, 'b', 0);
			drawMapComponent(x, y, TextureID::DownWall2, 'B', 0);
			drawMapComponent(x, y, TextureID::RightWall, 'r', 0);
			drawMapComponent(x, y, TextureID::RightWall2, 'R', 0);
			// drawDebugCase(
			// x,
			// y
			// );
			// for (const Wall &wall : m_map.getWalls())
			// {
			// 	drawDebugCollision(
			// 		wall.getCollision(),
			// 		wall.getCaseX(),
			// 		wall.getCaseY()
			// 	);
			// }

// ---------------------------------------------------- FLOOR ---------------------------------------------------- //
			drawMapComponent(x, y, TextureID::Floor, '.', 0);
		}
	}
}

void	Game::drawPlayer()
{
	drawTexture((
		m_player.getPosX()) * CASE_TILE,
		(m_player.getPosY()) * CASE_TILE, 
		m_player.getTexture(),
		m_player.getCurrentFrame()
	);
	// drawDebugCollision(
	// 	m_player.getCollisionValue(),
	// 	m_player.getCaseX(),
	// 	m_player.getCaseY()
	// );
	
}

void	Game::drawChests()
{
	TextureID	texture;

	for (Chest &chest : m_map.getChests())
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
			chest.getCaseY() * CASE_TILE + -20,
			texture,
			chest.getCurrentFrame()
		);
		if (chest.getChestState() == ChestState::Opened)
			drawLoot(chest);
		// drawDebugCollision(
		// 	chest.getCollision(),
		// 	chest.getCaseX(),
		// 	chest.getCaseY()
		// );
		// drawDebugCase(
		// 	chest.getCaseX(),
		// 	chest.getCaseY()
		// );
	}
}

void	Game::drawDoors()
{
	TextureID	texture;

	for (const Door &door : m_map.getDoors())
	{
		switch (door.getDoorState())
		{
		case DoorState::Closed:
			texture = TextureID::Door_Close;
			break;
		case DoorState::Opening:
			texture = TextureID::Door_Opening;
			break;
		case DoorState::Opened:
			texture = TextureID::Door_Opened;
			break;
		}
		drawTexture(
			door.getCaseX() * CASE_TILE,
			door.getCaseY() * CASE_TILE,
			texture,
			door.getCurrentFrame()
		);
		// drawDebugCollision(
		// door.getCollision(),
		// door.getCaseX(),
		// door.getCaseY()
		// );
	}
}

void	Game::drawDecor()
{
	for (const Decor &decor : m_map.getDecors())
	{
		drawTexture(
			decor.getCaseX() * CASE_TILE + decor.getOffsetX(),
			decor.getCaseY() * CASE_TILE + decor.getOffsetY(),
			decor.getTexture(),
			decor.getCurrentFrame()
		);
		// drawDebugCase(
		// 	decor.getCaseX(),
		// 	decor.getCaseY()
		// 	);
		// 	drawDebugCollision(
		// 		decor.getCollision(),
		// 		decor.getCaseX(),
		// 	decor.getCaseY()
		// 	);
	}
}

void	Game::drawLoot(Chest &chest)
{
	TextureID	texture;
	int			offsetY;

	switch (chest.getLoot())
	{
	case Item::Key_Door:
		texture = TextureID::Key_Door;
		offsetY = -40;
		break;
	case Item::Potion:
		texture = TextureID::Potion;
		offsetY = -40;
		break;
	case Item::Coin:
		texture = TextureID::Coin;
		offsetY = -40;
		break;
	
	default:
		break;
	}
	drawTexture(
			chest.getCaseX() * CASE_TILE,
			chest.getCaseY() * CASE_TILE + offsetY,
			texture,
			0
		);
}
