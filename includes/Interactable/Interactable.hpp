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
// ---------------------- CONST/DEST -------------------- //
	Interactable(int caseX, int caseY);
	virtual ~Interactable() = default;

// ---------------------- GETTER ------------------------ //
	int	getCaseX()	const;
	int	getCaseY()	const;

	int	getCurrentFrame()	const;

	const	Collision &getCollision()	const;

// ---------------------- OTHER METHOD ------------------ //

	virtual void interact(Player &player) = 0;
};
