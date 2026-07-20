#include "Door.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Door::Door(int caseX, int caseY)
	: Interactable(caseX, caseY),
	m_state(DoorState::Closed)
{
	m_collision.setHitbox({0.2,0.2,0.6,0.6});
	setAnimation(m_state);
}
Door::~Door() {}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //

void	Door::setAnimation(DoorState state)
{
	switch (state)
	{
	case DoorState::Opened:
		m_animation.reset(1, 0.2);
		break;
	case DoorState::Closed:
		m_animation.reset(1, 0.2);
		break;
	case DoorState::Opening:
		m_animation.reset(9, 0.2);
		break;
	default:
		break;
	}
}

void	Door::setState(DoorState state)
{
	if (m_state == state)
		return ;
	this->m_state = state;
	setAnimation(state);
}


// ---------------------------------------------------- GETTER --------------------------------------------------------- //

DoorState	Door::getDoorState()	const { return (this->m_state ); }

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

void	Door::animDoor(double deltaTime)
{
	if (m_state == DoorState::Opening)
	{
		if (m_animation.moveOnce(deltaTime))
			this->setState(DoorState::Opened);
	}
}

void	Door::interact(Player &player)
{
	if (m_state == DoorState::Closed)
		this->setState(DoorState::Opening);
}
