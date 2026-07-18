#include "UI.hpp"
#include "Game.hpp"

// ---------------------------------------------------- GETTER ---------------------------------------------------------- //

TextureID UI::getTextureFromItem(Item item) const
{
	switch (item)
	{
		case Item::Key_Door:
			return TextureID::Key_Door;
		case Item::Coin:
			return TextureID::Coin;
		case Item::Potion:
			return TextureID::Potion;
		default:
			return TextureID::Heart_Empty; // Temporaire
	}
}

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

void	UI::drawUI(Game &game)
{
	drawHealthBar(game);
	if (game.isInventoryOpen())
		drawInventory(game);
}
