#include "Player.hpp"

Player::Player()
	: m_x(0),
	m_y(0),
	m_state(PlayerState::Idle_Down),
	m_dirX(0),
	m_dirY(0) {}

void	Player::setX(double x)
{
	if (x < 0)
		return ;
	this->m_x = x;
}

void	Player::setY(double y)
{
	if (y < 0)
		return ;
	this->m_y = y;
}

void	Player::setDirX(int dirX) { this->m_dirX = dirX; }
void	Player::setDirY(int dirY) { this->m_dirY = dirY; }

void	Player::setState(PlayerState state) {

	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	// case PlayerState::Idle_Up:
	// case PlayerState::Idle_Left:
	// case PlayerState::Idle_Right:
	case PlayerState::Idle_Down:
		m_animation.reset(1, 400);
		break;
	// case PlayerState::Lift_Up:
	// case PlayerState::Lift_Left:
	// case PlayerState::Lift_Right:
	case PlayerState::Lift_Down:
		m_animation.reset(3, 400);
		break;
	// case PlayerState::Walk_Up:
	// case PlayerState::Walk_Left:
	// case PlayerState::Walk_Right:
	case PlayerState::Walk_Down:
		m_animation.reset(4, 400);
		break;
	// case PlayerState::Drop_Up:
	// case PlayerState::Drop_Left:
	// case PlayerState::Drop_Right:
	case PlayerState::Drop_Down:
		m_animation.reset(2, 400);
		break;
	default:
		break;
	}
}

double	Player::getPosX()	const { return (m_x); }
double	Player::getPosY()	const { return (m_y); }
int		Player::getDirX()	const { return (this->m_dirX); }
int		Player::getDirY()	const { return (this->m_dirY); }

int		Player::getCaseXinFrontOfPlayer()	const { return (this->getPosX() + this->getDirX()); }
int		Player::getCaseYinFrontOfPlayer()	const { return (this->getPosY() + this->getDirY()); }

PlayerState	Player::getState()			const { return (m_state); }
int			Player::getCurrentFrame()	const { return (m_animation.getCurrentFrame()); }

void	Player::anim()
{
	switch (this->m_state)
	{
		case PlayerState::Idle_Down:
			break;
		case PlayerState::Lift_Down:
			if (m_animation.moveOnce())
			{
				m_state = PlayerState::Walk_Down;
				m_animation.reset(2, 400);
			}
			break;
		case PlayerState::Walk_Down:
			m_animation.moveOnLoop();
			break;
		case PlayerState::Drop_Down:
			if (m_animation.moveOnce())
			{
				m_state = PlayerState::Idle_Down;
				m_animation.reset(3, 400);
			}
			break;
	}
}

Player::~Player() {}