#pragma once

#include <vector>
#include "Chest.hpp"

class Map
{
private:
	std::vector<std::string>	m_map;

	int 						firstPlayerPosX;
	int 						firstPlayerPosY;
	Animation					m_animFloatingCandle;

	std::vector<Chest>			m_chest;
public:
	Map();
	~Map();

	char	getCharFromTile(int x, int y)	const;

	int		getWidth()	const;
	int		getHeight()	const;

	int 	getFirstPlayerPosX()	const;
	int		getFirstPlayerPosY()	const;

	int		getCurrentFrame()	const;

	size_t	getChestCount()					const;
	const std::vector<Chest> &getChests()	const;
	std::vector<Chest>		 &getChestsNotConst();

	bool	load(const std::string& filename);
	void	initAnimations();
	void	anim();
};

