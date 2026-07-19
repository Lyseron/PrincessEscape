#include "Game.hpp"

bool	Game::inCollisionDecor(double nextX, double nextY)
{
	for (const Decor &decor :m_map.getDecors())
	{
		if (decor.isblockingObject() == false)
			continue;
		if (m_player.getCollisionValue().isColliding(
			decor.getCollision(),
			nextX,
			nextY,
			decor.getCaseX(),
			decor.getCaseY()
		))
			return (true);
	}
	return (false);
}

bool	Game::inCollisionChest(double nextX, double nextY)
{
	for (const Chest &chest : m_map.getChests())
	{
		if (m_player.getCollisionValue().isColliding(
				chest.getCollision(),
				nextX,
				nextY,
				chest.getCaseX(),
				chest.getCaseY()))
			return (true);
	}
	return (false);
}

bool Game::inCollisionDoor(double nextX, double nextY)
{
	for (const Door &door : m_map.getDoors())
	{
		if (m_player.getCollisionValue().isColliding(
				door.getCollision(),
				nextX,
				nextY,
				door.getCaseX(),
				door.getCaseY()))
			return (true);
	}
	return false;
}

// bool	isWall(char c)
// {
// 	if (c == 'h' || c == 'H'
// 		|| c == 'l' || c == 'L'
// 		|| c == 'R' || c == 'r'
// 		|| c == '{' || c == '}'
// 		|| c == '(' || c == ')'
// 		|| c == 'Q'
// 		|| c == 'b' || c == 'B')
// 		return (true);
// 	return (false);
// }

bool	Game::inCollisionWall(const Collision &collision, double nextX, double nextY)
{
	for (const Wall &wall : m_map.getWalls())
	{
		if (collision.isColliding(
				wall.getCollision(),
				nextX,
				nextY,
				wall.getCaseX(),
				wall.getCaseY()))
			return true;
	}
	return (false);
}

bool	Game::collisionPlayer(double nextX, double nextY)
{
	return (inCollisionWall(m_player.getCollisionValue() ,nextX, nextY)
		|| inCollisionDecor(nextX, nextY)
		|| inCollisionChest(nextX, nextY)
		|| inCollisionDoor(nextX, nextY));
}

bool	Game::move(double dirX, double dirY)
{
	bool	moved;
	double	posX = m_player.getPosX();
	double	posY = m_player.getPosY();
	double	nextPosX = posX + dirX * SPEED_PLAYER * m_deltaTime;
	double	nextPosY = posY + dirY * SPEED_PLAYER * m_deltaTime;

	moved = false;
	if (nextPosX < 0 || nextPosY < 0)
		return (false);
	if (nextPosX >= m_map.getWidth() || nextPosY >= m_map.getHeight())
		return (false);
	if (collisionPlayer(nextPosX, posY) == false)
	{
		m_player.setX(nextPosX);
		moved = true;
	}
	if (collisionPlayer(posX, nextPosY) == false)
	{
		m_player.setY(nextPosY);
		moved = true;
	}
	return (moved);
}

bool Game::movePlayer(double dirX, double dirY)
{
	
	if (move(dirX, dirY))
	{
		if (m_player.getState() == PlayerState::Idle)
			m_player.setState(PlayerState::Lift);
		return (true);
	}
	return (false);
}

void	Game::handleMovement()
{
	double	dirX = 0.0;
	double	dirY = 0.0;

	if (m_leftPressed)
		dirX -= 1.0;
	if (m_rightPressed)
		dirX += 1.0;
	if (m_upPressed)
		dirY -= 1.0;
	if (m_downPressed)
		dirY += 1.0;

	bool	moving = false;
	if (dirX != 0.0 || dirY != 0.0)
	{
		// Keep the same total speed when moving diagonally.
		if (dirX != 0.0 && dirY != 0.0)
		{
			constexpr double diagonalFactor = 0.70710678118;
			dirX *= diagonalFactor;
			dirY *= diagonalFactor;
		}

		if (dirY > 0.0)
			m_player.setDirection(Direction::Down, 0, 1);
		else if (dirY < 0.0)
			m_player.setDirection(Direction::Up, 0, -1);
		else if (dirX > 0.0)
			m_player.setDirection(Direction::Right, 1, 0);
		else
			m_player.setDirection(Direction::Left, -1, 0);
		moving = movePlayer(dirX, dirY);
	}

	if (moving == false)
	{
		if (m_player.getState() == PlayerState::Walk)
			m_player.setState(PlayerState::Drop);
	}
}
