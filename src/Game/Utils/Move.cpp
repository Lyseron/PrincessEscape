#include "Game.hpp"

bool	Game::inCollisionChest(double nextX, double nextY)
{
	double	playerTop		= nextY - 0.0;
	double	playerLeft		= nextX - 0.2;
	double	playerRight		= nextX + 0.2;
	double	playerBottom	= nextY + 0.2;

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
			return (true);
	}
	return (false);
}

bool	Game::inCollisionWall(double nextX, double nextY)
{
	double	playerTop		= nextY - 0.0;
	double	playerLeft		= nextX - 0.4;
	double	playerRight		= nextX + 0.2;
	double	playerBottom	= nextY + 0.5;

	int		intPlayerTop	= static_cast<int>(playerTop);
	int		intPlayerLeft	= static_cast<int>(playerLeft);
	int		intPlayerRight	= static_cast<int>(playerRight);
	int		intPlayerBottom	= static_cast<int>(playerBottom);

	if (m_map.getCharFromTile(intPlayerLeft, intPlayerTop) == '1'
		|| m_map.getCharFromTile(intPlayerRight, intPlayerTop) == '1'
		|| m_map.getCharFromTile(intPlayerLeft, intPlayerBottom) == '1'
		|| m_map.getCharFromTile(intPlayerRight, intPlayerBottom) == '1')
		return (true);
	return (false);
}

bool	Game::collisionPlayer(double nextX, double nextY)
{
	return (inCollisionWall(nextX, nextY)
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

bool Game::movePlayer(
	double dirX,
	double dirY,
	PlayerState idle,
	PlayerState lift,
	PlayerState walk,
	PlayerState drop)
{
	
	if (move(dirX, dirY))
	{
		if (m_player.getState() == idle)
			m_player.setState(lift);
		return (true);
	}
	return (false);
}
