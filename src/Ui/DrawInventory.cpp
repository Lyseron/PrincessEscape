#include "UI.hpp"
#include "Game.hpp"

void UI::drawInventory(Game &game)
{
	drawInventoryBackground(game);
	drawInventoryLayout(game);
	drawInventoryGrid(game);
	drawInventoryItems(game);
	drawCharacterPreview(game);
	drawItemDescription(game);
}

// void UI::drawItemDescription(Game &game)
// {
// 	SDL_SetRenderDrawColor(
// 		game.getRenderer(),
// 		200,
// 		200,
// 		200,
// 		255
// 	);

// 	SDL_RenderRect(
// 		game.getRenderer(),
// 		&m_descriptionRect
// 	);

// 	const Item *selected = game.getPlayer()
// 		.getInventory()
// 		.getSelectedItem();

// 	if (!selected)
// 		return;

// 	drawText(selected->getName(), ...);

// 	drawText(selected->getDescription(), ...);
// }

void UI::drawItemDescription(Game &game)
{
	SDL_SetRenderDrawColor(
		game.getRenderer(),
		200,
		200,
		200,
		255
	);

// grid desciption
	SDL_RenderRect(
		game.getRenderer(),
		&m_descriptionRect
	);
}

void UI::drawCharacterPreview(Game &game)
{
	SDL_SetRenderDrawColor(
		game.getRenderer(),
		200,
		200,
		200,
		255
	);

// // player grid
	// SDL_RenderRect(
	// 	game.getRenderer(),
	// 	&m_playerRect
	// );

	float scale = 2.5f;

	float spriteSize = game.getCaseTile() * scale;

	float playerX = m_playerRect.x + (m_playerRect.w - spriteSize) / 2.0f;
	float playerY = m_playerRect.y + (m_playerRect.h - spriteSize) / 2.0f;

	game.drawTextureScale(
		playerX,
		playerY,
		TextureID::Player_Idle_Down,
		0,
		scale
	);
}

void UI::drawInventoryBackground(Game &game)
{
	int width;
	int height;

	SDL_GetRenderOutputSize(game.getRenderer(), &width, &height);

	float inventoryWidth = width * INVENTORY_WIDTH_RATIO;
	float inventoryHeight = height * INVENTORY_HEIGHT_RATIO;

	m_inventoryRect.w = inventoryWidth;
	m_inventoryRect.h = inventoryHeight;
	m_inventoryRect.x = (width - m_inventoryRect.w) / 2.0f;
	m_inventoryRect.y = (height - m_inventoryRect.h) / 2.0f;

// background color
	SDL_SetRenderDrawColor(
		game.getRenderer(),
		35,
		35,
		35,
		240
	);

	SDL_RenderFillRect(game.getRenderer(), &m_inventoryRect);
	SDL_RenderRect(game.getRenderer(), &m_inventoryRect);
}

void 	UI::drawInventoryLayout(Game &game)
{
	float padding = 25.0f;
	float titleHeight = 40.0f;

// grid 
	m_gridRect.x = m_inventoryRect.x + padding;
	m_gridRect.y = m_inventoryRect.y + padding + titleHeight;
	m_gridRect.w = m_inventoryRect.w * 0.55f;
	m_gridRect.h = m_inventoryRect.h - padding * 2 - titleHeight;
// right side
	float rightX = m_gridRect.x + m_gridRect.w + padding;
	float rightWidth = m_inventoryRect.w - m_gridRect.w - padding * 3;
// player 
	m_playerRect.x = rightX;
	m_playerRect.y = m_inventoryRect.y + padding  + titleHeight;
	m_playerRect.w = rightWidth;
	m_playerRect.h = m_inventoryRect.h * 0.60f - titleHeight;
// description
	m_descriptionRect.x = rightX;
	m_descriptionRect.y = m_playerRect.y + m_playerRect.h + padding;
	m_descriptionRect.w = rightWidth;
	m_descriptionRect.h =
	m_inventoryRect.h - m_playerRect.h - padding * 3 - titleHeight;

// render the grid 
	SDL_SetRenderDrawColor(
		game.getRenderer(),
		255,
		0,
		0,
		255
	);
	SDL_RenderRect(game.getRenderer(), &m_gridRect);
}

void UI::drawInventoryItems(Game &game)
{
	const auto &items = game.getPlayer().getInventory().getItems();

	float margin = 20.0f;

	float usableWidth = m_gridRect.w - margin * 2;
	float usableHeight = m_gridRect.h - margin * 2;

	float cellWidth = usableWidth / INVENTORY_COLUMNS;
	float cellHeight = usableHeight / INVENTORY_ROWS;

	int slot = 0;

	for (const auto &[item, quantity] : items)
	{
		int row = slot / INVENTORY_COLUMNS;
		int col = slot % INVENTORY_COLUMNS;

		float cellX = m_gridRect.x + margin + col * cellWidth;
		float cellY = m_gridRect.y + margin + row * cellHeight;

		float itemX = cellX + (cellWidth - game.getCaseTile()) / 2.0f;
		float itemY = cellY + (cellHeight - game.getCaseTile()) / 2.0f;

		game.drawTexture(
			itemX,
			itemY,
			getTextureFromItem(item),
			0
		);

		slot++;
	}
}

void UI::drawInventoryGrid(Game &game)
{
	float margin = 20.0f;

	float usableWidth = m_gridRect.w - margin * 2;
	float usableHeight = m_gridRect.h - margin * 2;

	float cellWidth = usableWidth / INVENTORY_COLUMNS;
	float cellHeight = usableHeight / INVENTORY_ROWS;

// red square around grid
	SDL_SetRenderDrawColor(
		game.getRenderer(),
		200,
		200,
		200,
		255
	);

	int slot = 0;

	for (int row = 0; row < INVENTORY_ROWS; row++)
	{
		for (int col = 0; col < INVENTORY_COLUMNS; col++)
		{
			SDL_FRect cell;

			cell.x = m_gridRect.x + margin + col * cellWidth;
			cell.y = m_gridRect.y + margin + row * cellHeight;
			cell.w = cellWidth;
			cell.h = cellHeight;

			SDL_RenderRect(
				game.getRenderer(),
				&cell
			);
			if (slot == game.getPlayer().getInventory().getSelectedSlot())
			{
				// draw the grid yellow
				SDL_SetRenderDrawColor(
					game.getRenderer(),
					255,
					215,
					0,
					255
				);

				// draw the grid 
				SDL_RenderRect(
					game.getRenderer(),
					&cell
				);

				// draw the rest grey 
				SDL_SetRenderDrawColor(
					game.getRenderer(),
					200,
					200,
					200,
					255
				);
			}
			slot++;
		}
	}
}

void	UI::drawHealthBar(Game &game)
{
	Player	&player = game.getPlayer();
	int	width;
	int	height;

	SDL_GetRenderOutputSize(game.getRenderer(), &width, &height);		// to fill the height and width of the window
	int startX = width - player.getMaxHealthPoint() * 32;
	int startY = height - game.getCaseTile() - 20;

	for (int i = 0; i <  player.getMaxHealthPoint(); i++)
	{
		TextureID texture = TextureID::Heart_Empty;
		if (i < player.getHealthPoint())
			texture = TextureID::Heart_Full;
		game.drawTexture(
			startX + i * 20,
			startY,
			texture,
			0
		);
	}
}