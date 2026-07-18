#include "Door.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Door::Door(int caseX, int caseY)
	: Interactable(caseX, caseY),
	m_state(DoorState::Closed)
{
	m_collision.setHitbox({0.2,0.2,0.6,0.6});
}
Door::~Door() {}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //

void	Door::setState(DoorState state)
{
	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	case DoorState::Opened:
		m_animation.reset(1, 400);
		break;
	case DoorState::Closed:
		m_animation.reset(1, 400);
		break;
	case DoorState::Opening:
		m_animation.reset(9, 400);
		break;
	default:
		break;
	}
}


// ---------------------------------------------------- GETTER --------------------------------------------------------- //

DoorState	Door::getDoorState()	const { return (this->m_state ); }

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

void	Door::animDoor()
{
	if (m_state == DoorState::Opening)
	{
		if (m_animation.moveOnce())
		{
			m_state = DoorState::Opened;
			m_animation.reset(1, 400);
		}
		
	}
}

void	Door::interact(Player &player)
{
	// openDoor
	if (m_state == DoorState::Closed)
		this->setState(DoorState::Opening);
}

