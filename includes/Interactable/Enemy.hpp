#pragma once

#include "Collision.hpp"
#include "Animation.hpp"

class Game;

class Enemy
{
private:
	double	m_posX;
	double	m_posY;

	Collision 	m_collision;
	Animation	m_animation;
public:
// ---------------------- CONST/DEST -------------------- //
	Enemy(/* args */);
	~Enemy();

// ---------------------- OTHER METHOD ------------------ //
	void	update(Game &game);
	void	draw(Game &game);
};


