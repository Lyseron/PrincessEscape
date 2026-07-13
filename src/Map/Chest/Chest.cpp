#include "Chest.hpp"

Chest::Chest(int x, int y)
	: m_posY(y),
	m_posX(x),
	m_isOpen(false),
	m_state(ChestState::Closed)
	{}

void	Chest::setIsOpen(bool isOpen) { this->m_isOpen = isOpen; }

void	Chest::setState(ChestState state)
{
	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	// case PlayerState::Idle_Up:
	// case PlayerState::Idle_Left:
	// case PlayerState::Idle_Right:
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


int		Chest::getCaseX(void)	const { return (this->m_posX); }
int		Chest::getCaseY(void)	const { return (this->m_posY); }

ChestState	Chest::getChestState()		const { return (this->m_state ); }
int			Chest::getCurrentFrame()	const { return (this->m_animation.getCurrentFrame()); }

bool	Chest::getIsOpenState()		const { return (this->m_isOpen); }

void	Chest::anim()
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

void	Chest::open()
{
	if (m_state == ChestState::Closed)
	{
		m_state = ChestState::Opening;
		m_animation.reset(1, 400);
	}
}

void	Chest::render(SDL_Renderer* renderer,
		Textures* texture,
		int caseTile
	)
{
	
}

Chest::~Chest() {}