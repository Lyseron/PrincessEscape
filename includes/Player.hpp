#pragma once

#include "Animation.hpp"
#include "Textures.hpp"
#include <filesystem>

enum class PlayerState
{
	Idle,
	Lift,
	Walk,
	Drop
};

enum class Direction
{
	Up,
	Left,
	Right,
	Down
};

class Player
{
private:

	static constexpr	int	TIMER_DURATION_IDLE = 0;
	static constexpr	int	TIMER_DURATION_LIFT = 400;
	static constexpr	int	TIMER_DURATION_WALK = 400;
	static constexpr	int	TIMER_DURATION_DROP = 400;

	double		m_x;
	double		m_y;
	int			m_dirX;
	int			m_dirY;

	PlayerState	m_state;
	Direction	m_direction;
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
	void	setDirection(Direction direction, int dirX, int dirY);

// ---------------------- GETTER ------------------------ //
	double	getPosX()	const;
	double	getPosY()	const;

	PlayerState	getState()		const;
	TextureID	getTexture()	const;
	int		getCurrentFrame()	const;

	int		getDirY()	const;
	int		getDirX()	const;
	

// ---------------------- OTHER METHOD ------------------ //
	
	void	anim();

	int	getCaseXinFrontOfPlayer() const;
	int	getCaseYinFrontOfPlayer() const;

};
