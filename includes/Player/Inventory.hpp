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
// ---------------------- CONST/DEST -------------------- //

	Inventory(/* args */);
	~Inventory();

// ---------------------- SETTER ------------------------ //

	void	setSelectedSlot(int slot);

// ---------------------- GETTER ------------------------ //

	Item	getSelectedItem()	const;
	int		getSelectedSlot()	const;

	const std::unordered_map<Item, int> &getItems() const;

// ---------------------- OTHER METHOD ------------------ //

	void	addItem(Item item);
	bool	hasItem(Item item)	const;
	void	removeItem(Item itemp);
	void 	moveSelection(InventoryDirection dir);

	
};

