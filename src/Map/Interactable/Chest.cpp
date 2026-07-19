#include "Chest.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Chest::Chest(int x, int y, Item loot)
	: m_state(ChestState::Closed),
	Interactable(x, y),
	m_showLoot(false),
	m_lootTaken(false),
	m_loot(loot)
{
	m_collision.setHitbox({0, 0, 1, 0.70});
}

Chest::~Chest() {}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //

//armure m_collision.setHitbox({0.25, 0.3, 0.5, 0.65});
void	Chest::setState(ChestState state)
{
	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	case ChestState::Opened:
		m_animation.reset(1, 0.1);
		break;
	case ChestState::Closed:
		m_animation.reset(1, 0.1);
		break;
	case ChestState::Opening:
		m_animation.reset(1, 0.1);
		break;
	default:
		break;
	}
}

void 	Chest::setShowLoot(bool showLoot)	{ this->m_showLoot = showLoot; }
void	Chest::setLootTaken(bool lootTaken) { this->m_lootTaken = lootTaken; }

// ---------------------------------------------------- GETTER --------------------------------------------------------- //

ChestState	Chest::getChestState()		const { return (this->m_state ); }

void	Chest::animChest(double deltaTime)
{
	if (m_state == ChestState::Opening)
	{
		if (m_animation.moveOnce(deltaTime))
		{
			m_state = ChestState::Opened;
			m_animation.reset(1, 0.4);
		}
	}
}

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

bool	Chest::hasLootBeenTaken()	const { return (this->m_lootTaken); }
bool	Chest::showLoot()			const { return (this->m_showLoot); }
Item Chest::getLoot() const { return m_loot; }

void	Chest::interact(Player &player)
{
	// openChest
	if (m_state == ChestState::Closed)
	{
		setState(ChestState::Opening);
		m_animation.reset(1, 0.1);
	}
}
