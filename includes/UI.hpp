#pragma once

class Game;
#include "Textures.hpp"
#include "Player.hpp"

class UI
{
private:
	void	drawHealthBar(Game &game);
	void	drawInventory(Game &game);

	 TextureID getTextureFromItem(Item item) const;

	static constexpr float	INVENTORY_WIDTH_RATIO = 0.70f;
	static constexpr float	INVENTORY_HEIGHT_RATIO = 0.75f;

	static constexpr int	INVENTORY_COLUMNS = 5;
	static constexpr int	INVENTORY_ROWS = 4;

	SDL_FRect	m_inventoryRect;
	SDL_FRect	m_gridRect;
	SDL_FRect	m_playerRect;
	SDL_FRect	m_descriptionRect;

	void	drawInventoryBackground(Game &game);
	void	drawInventoryLayout(Game &game);
	void	drawInventoryGrid(Game &game);
	void	drawInventoryItems(Game &game);
	void	drawCharacterPreview(Game &game);
	void	drawItemDescription(Game &game);


public:

// default tell the compilateur that there is nothing in it
	UI() = default;
	~UI() = default;

	

	void	drawUI(Game &game);

};

