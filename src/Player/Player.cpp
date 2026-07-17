#include "Player.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //
Player::Player()
	: m_x(0),
	m_y(0),
	m_state(PlayerState::Idle),
	m_direction(Direction::Down),
	m_dirX(0),
	m_dirY(0),
	m_collision({PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH, PLAYER_HEIGHT}),
	m_interaction({0, 0, 0.30, 0.30})
	{}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //
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


// ---------------------------------------------------- GETTER --------------------------------------------------------- //

const 	Collision	&Player::getCollisionValue()	const { return (this->m_collision); }
const 	Collision	&Player::getInteractionValue()	const { return (this->m_interaction); }

double	Player::getPosX()	const { return (m_x); }
double	Player::getPosY()	const { return (m_y); }
int		Player::getDirX()	const { return (this->m_dirX); }
int		Player::getDirY()	const { return (this->m_dirY); }
int		Player::getCaseX()	const { return (static_cast<int>(m_x)); }
int		Player::getCaseY()	const { return (static_cast<int>(m_y)); }

int		Player::getCaseXinFrontOfPlayer()	const { return (this->getCaseX() + this->getDirX()); }
int		Player::getCaseYinFrontOfPlayer()	const { return (this->getCaseY() + this->getDirY()); }

PlayerState	Player::getState()			const { return (m_state); }

Inventory	&Player::getInventory() { return (m_inventory); }

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

int 	Player::getHealthPoint() { return (this->m_healtPoint); }
int		Player::getMaxHealthPoint() { return ( this->m_maxHealthPoint); }

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

void	Player::heal(int amount) { this->m_healtPoint += amount; }
void	Player::takeDamage(int amount) { this->m_healtPoint -= amount; }

bool Player::canInteract(const Interactable &object) const
{
	double interactionX = m_x;
	double interactionY = m_y;

	switch (m_direction)
	{
	case Direction::Up:
		interactionY -= PLAYER_HEIGHT;
		break;

	case Direction::Down:
		interactionY += PLAYER_HEIGHT;
		break;

	case Direction::Left:
		interactionX -= PLAYER_WIDTH;
		break;

	case Direction::Right:
		interactionX += PLAYER_WIDTH;
		break;
	}

	return m_collision.isColliding(
		object.getCollision(),
		interactionX,
		interactionY,
		object.getCaseX(),
		object.getCaseY()
	);
}

void	Player::addItem(Item item) { this->m_inventory.addItem(item); }
bool	Player::hasItem(Item item)	const { return (this->m_inventory.hasItem(item)); }
void	Player::removeItem(Item item) { this->m_inventory.removeItem(item); }


Player::~Player() {}