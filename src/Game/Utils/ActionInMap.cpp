#include "Game.hpp"

void	Game::handleMovement()
{
	bool	moving = false;

	if (m_upPressed)
	{
		m_player.setDirX(0);
			m_player.setDirY(-1);
			// movePlayer(
			// 	0,
			// 	-1,
			// 	PlayerState::Idle_Up,
			// 	PlayerState::Lift_Up,
			// 	PlayerState::Walk_Up,
			// 	PlayerState::Drop_Up
			// );
			moving = movePlayer(
				0,
				-1,
				PlayerState::Idle_Down,
				PlayerState::Lift_Down,
				PlayerState::Walk_Down,
				PlayerState::Drop_Down
			);
	}

	if (m_leftPressed)
	{
		m_player.setDirX(-1);
			m_player.setDirY(0);
			// movePlayer(
			// 	-1,
			// 	0,
			// 	PlayerState::Idle_Left,
			// 	PlayerState::Lift_Left,
			// 	PlayerState::Walk_Left,
			// 	PlayerState::Drop_Left
			// );
			moving = movePlayer(
				-1,
				0,
				PlayerState::Idle_Down,
				PlayerState::Lift_Down,
				PlayerState::Walk_Down,
				PlayerState::Drop_Down
			);
	}

	if (m_rightPressed)
	{
		m_player.setDirX(1);
			m_player.setDirY(0);
			// movePlayer(
			// 	1,
			// 	0,
			// 	PlayerState::Idle_Right,
			// 	PlayerState::Lift_Right,
			// 	PlayerState::Walk_Right,
			// 	PlayerState::Drop_Right
			// );
			moving = movePlayer(
				1,
				0,
				PlayerState::Idle_Down,
				PlayerState::Lift_Down,
				PlayerState::Walk_Down,
				PlayerState::Drop_Down
			);
	}

	if (m_downPressed)
	{
		m_player.setDirX(0);
		m_player.setDirY(1);
		moving = movePlayer(
			0,
			1,
			PlayerState::Idle_Down,
			PlayerState::Lift_Down,
			PlayerState::Walk_Down,
			PlayerState::Drop_Down
		);
	}
	if (moving == false)
	{
		if (m_player.getState() == PlayerState::Walk_Down)
			m_player.setState(PlayerState::Drop_Down);
	}
}

void	Game::actionInMap()
{
	handleMovement();
	if (m_openChest)
	{
		for (Chest &chest : m_map.getChestsNotConst())
		{
			if (m_player.getCaseXinFrontOfPlayer() == chest.getCaseX()
				&& m_player.getCaseYinFrontOfPlayer() == chest.getCaseY())
			{
				chest.open();
				return ;
			}
		}
	}
}