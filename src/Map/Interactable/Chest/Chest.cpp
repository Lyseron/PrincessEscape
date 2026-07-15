#include "Chest.hpp"

Chest::Chest(int x, int y)
	: m_state(ChestState::Closed),
	Interactable(x, y)
{
	m_collision.setHitbox({0, 0, 1, 0.70});
}

//armure m_collision.setHitbox({0.25, 0.3, 0.5, 0.65});
void	Chest::setState(ChestState state)
{
	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	case ChestState::Opened:
		m_animation.reset(1, 400);
		break;
	case ChestState::Closed:
		m_animation.reset(1, 400);
		break;
	case ChestState::Opening:
		m_animation.reset(1, 400);
		break;
	default:
		break;
	}
}

ChestState	Chest::getChestState()		const { return (this->m_state ); }

void	Chest::animChest()
{
	if (m_state == ChestState::Opening)
	{
		if (m_animation.moveOnce())
		{
			m_state = ChestState::Opened;
			m_animation.reset(1, 400);
		}
	}
}

void	Chest::interact(Player &player)
{
	// openChest
	if (m_state == ChestState::Closed)
	{
		m_state = ChestState::Opening;
		m_animation.reset(1, 400);
	}
}

Chest::~Chest() {}