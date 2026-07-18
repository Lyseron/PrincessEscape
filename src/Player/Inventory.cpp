#include "Inventory.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //
Inventory::Inventory() {}
Inventory::~Inventory() {}


// ---------------------------------------------------- SETTER ---------------------------------------------------------- //

void Inventory::setSelectedSlot(int slot) { m_selectedSlot = slot; }

// ---------------------------------------------------- GETTER ---------------------------------------------------------- //

int Inventory::getSelectedSlot() const { return (m_selectedSlot); }
Item Inventory::getSelectedItem() const
{
	int slot = 0;

	for (const auto &[item, quantity] : m_items)
	{
		if (slot == m_selectedSlot)
			return item;

		slot++;
	}

	return Item::None;
}

const std::unordered_map<Item, int> &Inventory::getItems() const { return (this->m_items); }

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
void Inventory::removeItem(Item item)
{
	auto it = m_items.find(item);

	if (it == m_items.end())
		return;

	it->second--;
	if (it->second <= 0)
		m_items.erase(it);
}

void Inventory::moveSelection(InventoryDirection direction)
{
	switch (direction)
	{
		case InventoryDirection::Up:
			if (m_selectedSlot >= INVENTORY_COLUMNS)
				m_selectedSlot -= INVENTORY_COLUMNS;
			break;

		case InventoryDirection::Down:
			if (m_selectedSlot + INVENTORY_COLUMNS < INVENTORY_SIZE)
				m_selectedSlot += INVENTORY_COLUMNS;
			break;

		case InventoryDirection::Left:
			if (m_selectedSlot % INVENTORY_COLUMNS != 0)
				m_selectedSlot--;
			break;

		case InventoryDirection::Right:
			if (m_selectedSlot % INVENTORY_COLUMNS != INVENTORY_COLUMNS - 1)
				m_selectedSlot++;
			break;
	}
}

