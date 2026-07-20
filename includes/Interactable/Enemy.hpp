#pragma once

#include "Collision.hpp"
#include "Animation.hpp"
#include "Player.hpp"

class Game;

enum class EnemyState
{
	Idle,
	Patrol,
	Chase,
	Attack,
	TakeDamage,
	Dead
};

enum class EnemyDirection
{
	Up,
	Down,
	Left,
	Right
};

// L'animation visuelle est séparée de l'état de jeu : Patrol et Chase,
// par exemple, utilisent tous les deux l'animation Walk.
enum class EnemyAnimation
{
	Idle,
	Walk,
	Attack,
	Damage,
	Dead
};

class Enemy
{
private:

	double	m_posX;
	double	m_posY;

	double	m_dirX;
	double	m_dirY;

	double	m_distFromPlayer;

	double	m_speed;
	bool	m_isPatroling;

	EnemyState		m_state;
	EnemyDirection	m_direction;
	EnemyAnimation	m_currentAnimation;

	int 	m_healthPoint;
	int 	m_maxHealthPoint;

	int		m_attackPoint;
	bool	m_hasAttacked;

	Collision 	m_collision;
	Animation	m_animation;

public:

// ---------------------- CONST/DEST -------------------- //
	Enemy(double x, double y,
		int maxHealthPoint, int attackPoint,
		bool isPatroling,
		int dirXPatrol, int dirYPatrol
		);
	~Enemy();

// ---------------------- SETTER ------------------------ //

	// void	setState(EnemyState state);
	void	setDirection(EnemyDirection direction);
	void	setAnimation(EnemyAnimation animation);

// ---------------------- GETTER ------------------------ //

	double	getPosX()	const;
	double	getPosY()	const;

	double	getDistFromPlayer()	const;

	Collision &getCollision();

// ---------------------- OTHER METHOD ------------------ //
	
	bool	canSeePlayer(const Player &player);

	double	dirToPlayerX(const Player &player);
	double	dirToPlayerY(const Player &player);
	double	distToPlayer(const Player &player);

	void 	updateDirection(double dirX, double dirY);

	void	updateIdle(Game &game);
	void	updatePatrol(Game &game);
	void	updateChase(Game &game);
	void	updateAttack(Game &game);
	void	updateDamage(Game &game);
	void	updateDead(Game &game);
	void	update(Game &game);

	void	takeDamage(int amount);

	bool	anim(double deltaTime);

	void	draw(Game &game);
};
