#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "Animation.hpp"

class Textures;

enum class	ChestState
{
	Closed,
	Opening,
	Opened
};

class Chest
{
private:
	int	m_posX;
	int	m_posY;

	ChestState	m_state;
	bool		m_isOpen;

	Animation	m_animation;

public:
// ---------------------- CONST/DEST -------------------- //
	Chest(int x, int y);
	~Chest();

// ---------------------- SETTER ------------------------ //
	void	setIsOpen(bool isOpen);

	void	setState(ChestState state);
	void	setCurrentFrame(int frame);
	void	setTimerFrame(int timer);
	void	setNbLoop(int nbLoop);
	void	setNbFrame(int nbOfFrame);

// ---------------------- GETTER ------------------------ //
	int	getCaseX()	const;
	int	getCaseY()	const;

	ChestState	getChestState()		const;
	int			getCurrentFrame()	const;
	int			getAnimationTimer()	const;
	int			getNbLoop()			const;
	int			getNbFrame()		const;

	bool		getIsOpenState()	const;

// ---------------------- OTHER METHOD ------------------ //
	void	render(SDL_Renderer* renderer,
		Textures* texture,
		int caseTile
	);
	bool	moveAnimLoop();
	bool	moveAnimOnce();
	void	updatenNbFrameInEachState();
	void	open();
	void	anim();
	
};

