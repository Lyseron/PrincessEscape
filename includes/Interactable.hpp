#pragma once

#include "Textures.hpp"
#include "Animation.hpp"
#include "Collision.hpp"

class Player;

class Interactable
{
protected:
	int	m_caseX;
	int	m_caseY;

	// TextureID	m_texture;
	Animation	m_animation;
	Collision	m_collision;
public:

	Interactable(int caseX, int caseY);
	virtual ~Interactable() = default;

	int	getCaseX()	const;
	int	getCaseY()	const;

	int	getCurrentFrame()	const;

	const	Collision &getCollision()	const;

	virtual void interact(Player &player) = 0;
};
