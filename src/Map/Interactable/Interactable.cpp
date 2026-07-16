#include "Interactable.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Interactable::Interactable(int caseX, int caseY) 
	: m_collision({0, 0, 0, 0}),
	m_caseX(caseX),
	m_caseY(caseY)
{}

// ---------------------------------------------------- GETTER --------------------------------------------------------- //

int	Interactable::getCaseX()	const { return (this->m_caseX); }
int	Interactable::getCaseY()	const { return (this->m_caseY); }

int	Interactable::getCurrentFrame()	const { return (this->m_animation.getCurrentFrame()); }

const	Collision &Interactable::getCollision()	const { return (this->m_collision); }
