#include "Collision.hpp"

Collision::Collision(const  Hitbox &hitbox) 
	:m_hitbox(hitbox)
	{}

void	Collision::setHitbox(const Hitbox &hitbox)
{
	this->m_hitbox = hitbox;
}
// to calculate cactly the pos of a given pos objet 
Bound	Collision::getBoundsObjectInCase(double posX, double posY)	const 
{
	Bound	bound;

	bound.left = posX + m_hitbox.offsetX;
	bound.top = posY + m_hitbox.offsetY;
	bound.right = bound.left + m_hitbox.width;
	bound.bottom = bound.top + m_hitbox.height;

	return (bound);
}


bool	Collision::isColliding(const Collision &hitBoxToTest,
		double posX,
		double posY,
		double testPosX,
		double testPosY
	)	const
{
	Bound	bound = this->getBoundsObjectInCase(posX, posY);
	Bound	testBound = hitBoxToTest.getBoundsObjectInCase(testPosX, testPosY);

	if (bound.right <= testBound.left
		|| bound.left >= testBound.right
		|| bound.bottom <= testBound.top
		|| bound.top >= testBound.bottom)
		return (false);
	return (true);
}

Collision::~Collision() {}