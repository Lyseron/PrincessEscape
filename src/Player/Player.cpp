#include "Player.hpp"

Player::Player()
	: m_x(0),
	m_y(0),
	m_state(PlayerState::Idle),
	m_direction(Direction::Down),
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

void	Player::setDirection(Direction direction, int dirX, int dirY)
{ 
	this->m_direction = direction; 
	this->setDirX(dirX);
	this->setDirY(dirY);
}
void	Player::setState(PlayerState state) {

	if (m_state == state)
		return ;
	this->m_state = state;
	
	switch (state)
	{
	case PlayerState::Idle:
		m_animation.reset(1, TIMER_DURATION_IDLE);
		break;
	case PlayerState::Lift:
		m_animation.reset(3, TIMER_DURATION_LIFT);
		break;
	case PlayerState::Walk:
		m_animation.reset(4, TIMER_DURATION_WALK);
		break;
	case PlayerState::Drop:
		m_animation.reset(2, TIMER_DURATION_DROP);
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

TextureID Player::getTexture()	const 
{
	
	if (m_state == PlayerState::Idle)
	{
		switch (m_direction)
		{
			case Direction::Up:
				return TextureID::Player_Idle_Up;
			case Direction::Right:
				return TextureID::Player_Idle_Right;
			case Direction::Left:
				return TextureID::Player_Idle_Left;
			case Direction::Down:
				return TextureID::Player_Idle_Down;
		}
	}
	if (m_state == PlayerState::Lift)
	{
		switch (m_direction)
		{
			case Direction::Up:
				return TextureID::Player_Lift_Up;
			case Direction::Right:
				return TextureID::Player_Lift_Right;
			case Direction::Left:
				return TextureID::Player_Lift_Left;
			case Direction::Down:
				return TextureID::Player_Lift_Down;
		}
	}
	if (m_state == PlayerState::Walk)
	{
		switch (m_direction)
		{
			case Direction::Up:
				return TextureID::Player_Walk_Up;
			case Direction::Right:
				return TextureID::Player_Walk_Right;
			case Direction::Left:
				return TextureID::Player_Walk_Left;
			case Direction::Down:
				return TextureID::Player_Walk_Down;
		}
	}
	if (m_state == PlayerState::Drop)
	{
		switch (m_direction)
		{
			case Direction::Up:
				return TextureID::Player_Drop_Up;
			case Direction::Right:
				return TextureID::Player_Drop_Right;
			case Direction::Left:
				return TextureID::Player_Drop_Left;
			case Direction::Down:
				return TextureID::Player_Drop_Down;
		}
	}
	return TextureID::Player_Idle_Down;
}

int			Player::getCurrentFrame()	const { return (m_animation.getCurrentFrame()); }

void	Player::anim()
{
	switch (this->m_state)
	{
		case PlayerState::Idle:
			break;
		case PlayerState::Lift:
			if (m_animation.moveOnce())
			{
				setState(PlayerState::Walk);
				m_animation.reset(2, TIMER_DURATION_WALK);
			}
			break;
		case PlayerState::Walk:
			m_animation.moveOnLoop();
			break;
		case PlayerState::Drop:
			if (m_animation.moveOnce())
			{
				setState(PlayerState::Idle);
				m_animation.reset(3, TIMER_DURATION_IDLE);
			}
			break;
	}
}

Player::~Player() {}