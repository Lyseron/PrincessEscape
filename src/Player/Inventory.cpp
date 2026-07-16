#include "Inventory.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //
Inventory::Inventory() {}
Inventory::~Inventory() {}


// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

void	Inventory::addItem(Item item) { this->m_items[item]++; }
bool	Inventory::hasItem(Item item)	const 
{
// find to go through the unordered map to find the item
//	auto -> deduce the type by itselft (can be anything find return)
// it is like a pointeur to the element of the unordered map to access first second
	auto it = this->m_items.find(item);
	if (it != m_items.end()
		&& it->second > 0) // second for the second  line : Item -> firt ; int -> second
		return (true);
	return (false);
}
void	Inventory::removeItem(Item item) { this->m_items[item]--; }


