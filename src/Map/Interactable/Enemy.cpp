#include "Enemy.hpp"
#include "Game.hpp"
#include <cmath>

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Enemy::Enemy(double x, double y,
	int maxHealthPoint, int attackPoint,
	bool isPatroling,
	int dirXPatrol, int dirYPatrol
	) : m_collision({0.25,0.55,0.49,0.45}),
		m_posX(x),
		m_posY(y),
		m_speed(1.5),
		m_state(EnemyState::Idle),
		m_maxHealthPoint(maxHealthPoint),
		m_isPatroling(isPatroling),
		m_dirX(dirXPatrol),
		m_dirY(dirYPatrol),
		m_attackPoint(attackPoint),
		m_hasAttacked(false),
		m_healthPoint(maxHealthPoint),
		m_direction(EnemyDirection::Down),
		m_currentAnimation(EnemyAnimation::Idle)
		
{
	m_animation.reset(1, 0.14);
}

Enemy::~Enemy() {}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //

void	Enemy::setDirection(EnemyDirection direction) { this->m_direction = direction; }

void	Enemy::setAnimation(EnemyAnimation animation)
{
	if (m_currentAnimation == animation)
		return ;

	m_currentAnimation = animation;
	switch (m_currentAnimation)
	{
		case EnemyAnimation::Idle:
			m_animation.reset(1, 0.14);
			break;
		case EnemyAnimation::Walk:
			m_animation.reset(4, 0.14);
			break;
		case EnemyAnimation::Attack:
			m_animation.reset(7, 0.2);
			break;
		case EnemyAnimation::Damage:
			m_animation.reset(2, 0.2);
			break;
		case EnemyAnimation::Dead:
			m_animation.reset(4, 0.2);
			break;
	}
}

// ---------------------------------------------------- GETTER --------------------------------------------------------- //

double	Enemy::getPosX()	const { return (this->m_posX); }
double	Enemy::getPosY()	const { return (this->m_posY); }

Collision &Enemy::getCollision() { return (this->m_collision); }

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

bool	Enemy::canSeePlayer(const Player &player)
{
	// if the ennemy is at 5 case from the player or below he can see him
	if (distToPlayer(player) <= 5) // change later for the wall
		return (true);
	return (false);
}

double	Enemy::dirToPlayerX(const Player &player) { return (player.getPosX() - m_posX); }
double	Enemy::dirToPlayerY(const Player &player) { return (player.getPosY() - m_posY); }

double Enemy::distToPlayer(const Player &player)
{
	// calculate the direction that the ennemy need to go to go to the player
	double dx = dirToPlayerX(player);
	double dy = dirToPlayerY(player);

	// calcule the distance from player throught the hypothenus of the triangle position of the ennemy and aplayer (the diagonal distance between them)
	double dist = std::sqrt(dx * dx + dy * dy);
	return (dist);
}

void 	Enemy::updateDirection(double dirX, double dirY)
{
	// choose axe où le déplacement est le plus grand
	if (std::abs(dirX) > std::abs(dirY))
	{
		if (dirX > 0)
			m_direction = EnemyDirection::Right;
		else if (dirX < 0)
			m_direction = EnemyDirection::Left;
	}
	else
	{
		if (dirY > 0)
			m_direction = EnemyDirection::Down;
		else if (dirY < 0)
			m_direction = EnemyDirection::Up;
	}
}

void Enemy::update(Game &game)
{
	
	switch (m_state)
	{
		case EnemyState::Idle:
			updateIdle(game);
			break;

		case EnemyState::Patrol:
			updatePatrol(game);
			break;

		case EnemyState::Chase:
			updateChase(game);
			break;

		case EnemyState::TakeDamage:
			updateDamage(game);
			break;

		case EnemyState::Attack:
			updateAttack(game);
			break;

		case EnemyState::Dead:
			updateDead(game);
			break;
	}
}

bool	Enemy::anim(double deltaTime)
{
	if (m_currentAnimation == EnemyAnimation::Walk)
		return (m_animation.moveOnLoop(deltaTime));
	if (m_currentAnimation == EnemyAnimation::Attack
		|| m_currentAnimation == EnemyAnimation::Damage
		|| m_currentAnimation == EnemyAnimation::Dead)
		return (m_animation.moveOnce(deltaTime));
	return (false);
}

void	Enemy::updateIdle(Game &game)
{
	setAnimation(EnemyAnimation::Idle);
	if (canSeePlayer(game.getPlayer()))
	{
		m_state = EnemyState::Chase;
		return ;
	}

	if (m_isPatroling)
		m_state = EnemyState::Patrol;
}


// tell the ennemy to go to the player pos 
void	Enemy::updateChase(Game &game)
{
	Player &player = game.getPlayer();
	setAnimation(EnemyAnimation::Walk);

	if (canSeePlayer(player) == false)
	{
		if (m_isPatroling)
			m_state = EnemyState::Patrol;
		else
			m_state = EnemyState::Idle;
		return ;
	}

	// normalise it to avaid the pos to impact the speed of deplacement 
	double dist = distToPlayer(player);

	// to not divide by 0
	if (dist == 0)
		return ;

	// stop the enemy if he is too close to the player 
	if (dist <= 1.0)
	{
		m_state = EnemyState::Attack;
		setAnimation(EnemyAnimation::Attack);
		m_hasAttacked = false;
		return;
	}

	double dx = dirToPlayerX(player);
	double dy = dirToPlayerY(player);
	// now that we have the distance we want to know the direction without the lenght of how far the player is
	// get from -1 to 1 and all in between
	dx /= dist;
	dy /= dist;

// to follow the player
	updateDirection(dx, dy);
	//	make the ennemy go the the player location 
	double nextX = m_posX + dx * m_speed * game.getDeltaTime();
	double nextY = m_posY + dy * m_speed * game.getDeltaTime();

	if (!game.inCollisionWall(getCollision(), nextX, nextY))
	{
		m_posX = nextX;
		m_posY = nextY;
		anim(game.getDeltaTime());
	}
}

void	Enemy::updatePatrol(Game &game)
{
	Player &player = game.getPlayer();
	setAnimation(EnemyAnimation::Walk);

	if (canSeePlayer(player))
	{
		m_state = EnemyState::Chase;
		return ;
	}
	updateDirection(m_dirX, m_dirY);
	double nextX = m_posX + m_dirX * m_speed * game.getDeltaTime();
	double nextY = m_posY + m_dirY * m_speed * game.getDeltaTime();

	if (game.inCollisionWall(m_collision, nextX, nextY))
	{
		// std::cout << "collision wall\n";
		// Demi tour
		m_dirX *= -1;
		m_dirY *= -1;
		return;
	}
	else
	{
		// std::cout << "moove\n";
		m_posX = nextX;
		m_posY = nextY;
		anim(game.getDeltaTime());
	}
}

void	Enemy::updateDamage(Game &game)
{
	setAnimation(EnemyAnimation::Damage);
	if (anim(game.getDeltaTime()))
	{
		if (canSeePlayer(game.getPlayer()))
			m_state = EnemyState::Chase;
		else if (m_isPatroling)
			m_state = EnemyState::Patrol;
		else
			m_state = EnemyState::Idle;
	}
}

void	Enemy::updateAttack(Game &game)
{
	Player &player = game.getPlayer();
	setAnimation(EnemyAnimation::Attack);

	if (m_animation.getCurrentFrame() >= 2 && !m_hasAttacked)
	{
		player.takeDamage(m_attackPoint);
		m_hasAttacked = true;
	}

	if (anim(game.getDeltaTime()))
	{
		m_hasAttacked = false;
		if (canSeePlayer(player))
			m_state = EnemyState::Chase;
		else if (m_isPatroling)
			m_state = EnemyState::Patrol;
		else
			m_state = EnemyState::Idle;
	}
}

void	Enemy::takeDamage(int amount) 
{
	if (m_state == EnemyState::Dead)
		return ;
	this->m_healthPoint -= amount; 
	if (m_healthPoint <= 0)
	{
		m_healthPoint = 0;
		m_state = EnemyState::Dead;
		return ;
	}
	m_state = EnemyState::TakeDamage;
}

void	Enemy::updateDead(Game &game)
{
	setAnimation(EnemyAnimation::Dead);
	anim(game.getDeltaTime());
}

void	Enemy::draw(Game &game)
{
	TextureID	texture;

	if (m_currentAnimation == EnemyAnimation::Attack)
	{
		// if (m_direction == EnemyDirection::Left)
		// 	texture = TextureID::Player_Attack_Left;
		// else if (m_direction == EnemyDirection::Right)
		// 	texture = TextureID::Player_Attack_Right;
		// else if (m_direction == EnemyDirection::Up)
		// 	texture = TextureID::Player_Attack_Up;
		// else if (m_direction == EnemyDirection::Down)
		// 	texture = TextureID::Player_Attack_Down;
		texture = TextureID::Player_Attack_Down;
	}
	else if (m_currentAnimation == EnemyAnimation::Damage)
	{
		// if (m_direction == EnemyDirection::Left)
		// 	texture = TextureID::Player_Damage_Left;
		// else if (m_direction == EnemyDirection::Right)
		// 	texture = TextureID::Player_Damage_Right;
		// else if (m_direction == EnemyDirection::Up)
		// 	texture = TextureID::Player_Damage_Up;
		// else if (m_direction == EnemyDirection::Down)
		// 	texture = TextureID::Player_Damage_Down;
		texture = TextureID::Player_Damage_Down;
	}
	else if (m_currentAnimation == EnemyAnimation::Dead)
		texture = TextureID::Player_Dead;
	else
	{
		switch (m_direction)
		{
			case EnemyDirection::Up:
				texture = (m_currentAnimation == EnemyAnimation::Walk)
					? TextureID::Player_Walk_Up : TextureID::Player_Idle_Up;
				break;
			case EnemyDirection::Left:
				texture = (m_currentAnimation == EnemyAnimation::Walk)
					? TextureID::Player_Walk_Left : TextureID::Player_Idle_Left;
				break;
			case EnemyDirection::Right:
				texture = (m_currentAnimation == EnemyAnimation::Walk)
					? TextureID::Player_Walk_Right : TextureID::Player_Idle_Right;
				break;
			case EnemyDirection::Down:
				texture = (m_currentAnimation == EnemyAnimation::Walk)
					? TextureID::Player_Walk_Down : TextureID::Player_Idle_Down;
				break;
			default:
				texture = TextureID::Player_Idle_Down;
				break;
		}
	}
	// swicth for each state a different spritesheet
	game.drawTexture(
		m_posX * game.getCaseTile(),
		m_posY * game.getCaseTile(),
		texture,
		m_animation.getCurrentFrame()
	);
}
