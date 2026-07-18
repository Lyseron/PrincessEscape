#include "Wall.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Wall::Wall(int caseX, int caseY, Collision collision)
	: m_caseX(caseX),
	m_caseY(caseY),
	m_collision(collision)
{}

Wall::~Wall()
{}

// ---------------------------------------------------- GETTER --------------------------------------------------------- //

int	Wall::getCaseX()	const { return (this->m_caseX); }
int	Wall::getCaseY()	const { return (this->m_caseY); }

const Collision	&Wall::getCollision() const { return (this->m_collision); }

