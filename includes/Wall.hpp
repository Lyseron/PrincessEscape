#pragma once

#include "Collision.hpp"
class Wall
{
private:
	int	m_caseX;
	int	m_caseY;

	Collision	m_collision;
public:
	Wall(int caseXX, int caseY, Collision collision);
	~Wall();

	int	getCaseX()	const;
	int	getCaseY()	const;

	const Collision	&getCollision()	const;
};

