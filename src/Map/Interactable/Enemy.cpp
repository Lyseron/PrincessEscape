#include "Enemy.hpp"
#include "Game.hpp"

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
		m_healthPoint(maxHealthPoint)
{}

Enemy::~Enemy() {}

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

void	Enemy::updateIdle(Game &game)
{
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
		return;
	}

	double dx = dirToPlayerX(player);
	double dy = dirToPlayerY(player);
	// now that we have the distance we want to know the direction without the lenght of how far the player is
	// get from -1 to 1 and all in between
	dx /= dist;
	dy /= dist;


	//	make the ennemy go the the player location 
	double nextX = m_posX + dx * m_speed * game.getDeltaTime();
	double nextY = m_posY + dy * m_speed * game.getDeltaTime();

	if (!game.inCollisionWall(getCollision(), nextX, nextY))
	{
		m_posX = nextX;
		m_posY = nextY;
	}
}

void	Enemy::updatePatrol(Game &game)
{
	Player &player = game.getPlayer();

	if (canSeePlayer(player))
	{
		m_state = EnemyState::Chase;
		return ;
	}
	double nextX = m_posX + m_dirX * m_speed * game.getDeltaTime();
	double nextY = m_posY + m_dirY * m_speed * game.getDeltaTime();

	if (game.inCollisionWall(m_collision, nextX, nextY))
	{
		// std::cout << "collision wall\n";
		// Demi-tour
		m_dirX *= -1;
		m_dirY *= -1;
		return;
	}
	else
	{
		// std::cout << "moove\n";
		m_posX = nextX;
		m_posY = nextY;
	}
}

void	Enemy::updateDamage(Game &game)
{
	// play anim damage
}

void	Enemy::updateAttack(Game &game)
{
	Player &player = game.getPlayer();

// quand jaurai mis les anim
	// if (m_animation.getCurrentFrame() == 2 && !m_hasAttacked)
	// {
	// 	player.takeDamage(m_attackPoint);
	// 	m_hasAttacked = true;
	// }

	// if (m_animation.getCurrentFrame() == m_animation.getNbFrame() - 1) // replace par if (m_animation.moveOnce()) genre tant quelle est pas fini quoi 
	// {
	// 	m_hasAttacked = false;
	// 	if (canSeePlayer(player))
	// 		m_state = EnemyState::Chase;
	// 	else if (m_isPatroling)
	// 		m_state = EnemyState::Patrol;
	// 	else
	// 		m_state = EnemyState::Idle;
	// }
	if (distToPlayer(player) > 1.0)
	{
		m_state = EnemyState::Chase;
		return;
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
	// play dead anim and disapear
}

void	Enemy::draw(Game &game)
{
	// swicth for each state a different spritesheet
	game.drawTexture(
		m_posX * game.getCaseTile(),
		m_posY * game.getCaseTile(),
		TextureID::Player_Idle_Up,
		0
	);
}
