#pragma once

#include "Textures.hpp"
#include "Animation.hpp"
#include "Collision.hpp"

enum class DecorType
{
	Chandelier,
	FloatingCandle,
	Armure
};

class Decor
{
private:

	int	m_caseY;
	int	m_caseX;

	int	m_offsetX;
	int	m_offsetY;

	DecorType	m_decorType;
	TextureID	m_texture;

	bool		m_blockingObject;
	Animation	m_animation;
	Collision	m_collision;
public:

// ---------------------- CONST/DEST -------------------- //
	Decor(DecorType decor, int caseX, int caseY);
	~Decor();

// ---------------------- GETTER ------------------------ //
	int		getCaseX()	const;
	int		getCaseY()	const;

	TextureID	getTexture()	const;

	int			getCurrentFrame()	const;

	int		getOffsetX()	const;
	int		getOffsetY()	const;

	const	Collision &getCollision()	const;

// ---------------------- OTHER METHOD ------------------ //

	void	update(double deltaTime);
	bool	isblockingObject()	const;

};
