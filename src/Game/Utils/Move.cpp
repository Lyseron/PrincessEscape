#include "Game.hpp"

bool	Game::inCollisionDecor(double nextX, double nextY)
{
	for (const Decor &decor :m_map.getDecors())
	{
		if (decor.isblockingObject() == false)
			continue;
		if (m_player.getCollision().isColliding(
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
	double	playerTop		= nextY - 0.0;
	double	playerLeft		= nextX - 0.0;
	double	playerRight		= nextX + 0.0;
	double	playerBottom	= nextY + 0.0;

	int		intPlayerTop	= static_cast<int>(playerTop);
	int		intPlayerLeft	= static_cast<int>(playerLeft);
	int		intPlayerRight	= static_cast<int>(playerRight);
	int		intPlayerBottom	= static_cast<int>(playerBottom);

	for (const Chest &chest : m_map.getChests())
	{
		if ((chest.getCaseX() == intPlayerLeft
			|| chest.getCaseX() == intPlayerRight)
			&& (chest.getCaseY() == intPlayerTop
			|| chest.getCaseY() == intPlayerBottom))
			return true;
	}
	return (false);
}

bool	isWall(char c)
{
	if (c == 'h' || c == 'H'
		|| c == 'l' || c == 'L'
		|| c == 'R' || c == 'r'
		|| c == '{' || c == '}'
		|| c == '(' || c == ')'
		|| c == 'Q'
		|| c == 'b' || c == 'B')
		return (true);
	return (false);
}

bool	Game::inCollisionWall(double nextX, double nextY)
{
	Bound player = m_player.getCollision().getBounds(nextX, nextY);

	int		intPlayerTop	= static_cast<int>(player.top);
	int		intPlayerLeft	= static_cast<int>(player.left);
	int		intPlayerRight	= static_cast<int>(player.right);
	int		intPlayerBottom	= static_cast<int>(player.bottom);

	if (isWall(m_map.getCharFromTile(intPlayerLeft, intPlayerTop))
		|| isWall(m_map.getCharFromTile(intPlayerRight, intPlayerTop))
		|| isWall(m_map.getCharFromTile(intPlayerLeft, intPlayerBottom))
		|| isWall(m_map.getCharFromTile(intPlayerRight, intPlayerBottom)))
		return (true);
	return (false);
}

bool	Game::collisionPlayer(double nextX, double nextY)
{
	return (inCollisionWall(nextX, nextY)
		|| inCollisionDecor(nextX, nextY)
		|| inCollisionChest(nextX, nextY));
}

bool	Game::move(double dirX, double dirY)
{
	bool	moved;
	double	posX = m_player.getPosX();
	double	posY = m_player.getPosY();
	double	nextPosX = posX + dirX * SPEED_PLAYER;
	double	nextPosY = posY + dirY * SPEED_PLAYER;

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
	bool	moving = false;

	if (m_upPressed)
	{
		m_player.setDirection(Direction::Up, 0, -1);
		moving = movePlayer(0, -1);
	}

	if (m_leftPressed)
	{
		m_player.setDirection(Direction::Left, -1, 0);
		moving = movePlayer(-1, 0);
	}

	if (m_rightPressed)
	{
		m_player.setDirection(Direction::Right, 1, 0);
		moving = movePlayer(1, 0);
	}

	if (m_downPressed)
	{
		m_player.setDirection(Direction::Down, 0, 1);
		moving = movePlayer(0, 1);
	}

	if (moving == false)
	{
		if (m_player.getState() == PlayerState::Walk)
			m_player.setState(PlayerState::Drop);
	}
}
