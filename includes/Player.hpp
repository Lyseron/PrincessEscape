#pragma once

#include "Animation.hpp"
#include "Textures.hpp"
#include <filesystem>
#include "Collision.hpp"
#include "Interactable.hpp"
#include "Inventory.hpp"

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

	static constexpr	double	PLAYER_OFFSET_X = 0.25;
	static constexpr	double	PLAYER_OFFSET_Y = 0.55;
	static constexpr	double	PLAYER_WIDTH = 0.49;
	static constexpr	double	PLAYER_HEIGHT = 0.45;

	double		m_x;
	double		m_y;
	int			m_dirX;
	int			m_dirY;

	int 		m_healtPoint = 4;
	int			m_maxHealthPoint = 5;
	bool		m_tookDamage = false;

	PlayerState	m_state;
	Direction	m_direction;
	Animation	m_animation;

	Collision	m_collision;
	Collision	m_interaction;

	Inventory	m_inventory;

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
	int		getCaseX()	const;
	int		getCaseY()	const;

	PlayerState	getState()		const;
	TextureID	getTexture()	const;
	int		getCurrentFrame()	const;

	int		getDirY()	const;
	int		getDirX()	const;

	int 	getHealthPoint();
	int		getMaxHealthPoint();

	const 	Collision	&getCollisionValue()	const;
	const 	Collision	&getInteractionValue()	const;

	Inventory	&getInventory();


// ---------------------- OTHER METHOD ------------------ //
	
	void	anim();

	int	getCaseXinFrontOfPlayer() const;
	int	getCaseYinFrontOfPlayer() const;

	bool 	canInteract(const Interactable &object) const;

	void	addItem(Item item);
	bool	hasItem(Item item)	const;
	void	removeItem(Item item);

	void	heal(int amount);
	void	takeDamage(int amount);

};
