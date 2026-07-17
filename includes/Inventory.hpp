#pragma once
#include <unordered_map>

class Player;

enum class Item
{
	Key_Door,
	Potion,
	Coin,
	None
};

enum class InventoryDirection
{
	Up,
	Down,
	Left,
	Right
};

struct InventorySlot
{
	Item item = Item::None;
	int	quantity = 0;
};


class Inventory
{
private:
	std::unordered_map<Item, int>	m_items;
	int 	m_selectedSlot = 0;

	static constexpr int	INVENTORY_COLUMNS = 5;
	static constexpr int	INVENTORY_ROWS = 4;

	static constexpr int INVENTORY_SIZE = INVENTORY_ROWS * INVENTORY_COLUMNS;
public:
	Inventory(/* args */);
	~Inventory();

	void	addItem(Item item);
	bool	hasItem(Item item)	const;
	void	removeItem(Item itemp);

	void	setSelectedSlot(int slot);
	int 	getSelectedSlot()	const;

	Item	 getSelectedItem() const;

	void 	moveSelection(InventoryDirection dir);

	const std::unordered_map<Item, int> &getItems() const;
};

