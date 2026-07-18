#pragma once

#include "Collision.hpp"
class Wall
{
private:
	int	m_caseX;
	int	m_caseY;

	Collision	m_collision;
public:

// ---------------------- CONST/DEST -------------------- //
	Wall(int caseXX, int caseY, Collision collision);
	~Wall();

// ---------------------- GETTER ------------------------ //
	int	getCaseX()	const;
	int	getCaseY()	const;

	const Collision	&getCollision()	const;
};

