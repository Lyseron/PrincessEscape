#pragma once
#include <unordered_map>

enum class Item
{
	Key_Door,
	Potion,
	Coin
};

class Inventory
{
private:
	std::unordered_map<Item, int>	m_items;

public:
	Inventory(/* args */);
	~Inventory();

	void	addItem(Item item);
	bool	hasItem(Item item)	const;
	void	removeItem(Item itemp);
};

