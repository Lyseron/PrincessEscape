#pragma once

#include "Animation.hpp"

enum class PlayerState
{
	Idle_Down,
	Lift_Down,
	Walk_Down,
	Drop_Down

	// Idle_Up,
	// Lift_Up,
	// Walk_Up,
	// Drop_Up,

	// Idle_Left,
	// Lift_Left,
	// Walk_Left,
	// Drop_Left,

	// Idle_Right,
	// Lift_Right,
	// Walk_Right,
	// Drop_Right
};

class Player
{
private:
	double		m_x;
	double		m_y;
	int			m_dirX;
	int			m_dirY;

	PlayerState	m_state;
	Animation	m_animation;

public:
// ---------------------- CONST/DEST -------------------- //
	Player();
	~Player();

// ---------------------- SETTER ------------------------ //
	void	setX(double x);
	void	setY(double y);
	void	setDirX(int dirX);
	void	setDirY(int dirY);

	void	setState(PlayerState state);

// ---------------------- GETTER ------------------------ //
	double	getPosX()	const;
	double	getPosY()	const;

	PlayerState	getState()		const;
	int		getCurrentFrame()	const;

	int		getDirY()	const;
	int		getDirX()	const;
	

// ---------------------- OTHER METHOD ------------------ //
	
	void	anim();

	int	getCaseXinFrontOfPlayer() const;
	int	getCaseYinFrontOfPlayer() const;

};
