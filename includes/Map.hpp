#pragma once

#include <vector>
#include "Chest.hpp"
#include "Decor.hpp"
#include "Door.hpp"
#include "Wall.hpp"

class Map
{
private:
	std::vector<std::string>	m_map;

	int 						firstPlayerPosX;
	int 						firstPlayerPosY;

	std::vector<Chest>			m_chest;
	std::vector<Decor>			m_decors;
	std::vector<Door>			m_doors;
	std::vector<Wall>			m_walls;
public:
	Map();
	~Map();

	char	getCharFromTile(int x, int y)	const;

	int		getWidth()	const;
	int		getHeight()	const;

	int 	getFirstPlayerPosX()	const;
	int		getFirstPlayerPosY()	const;
	
	const	std::vector<Decor>	&getDecors()	const;
	std::vector<Decor>			&getDecorsNotConst();

	size_t	getChestCount()					const;

	const	std::vector<Chest> &getChests()	const;
	std::vector<Chest>			&getChestsNotConst();

	const	std::vector<Door>	&getDoors()	const;
	std::vector<Door>			&getDoorsNotConst();

	const	std::vector<Wall> &getWalls()	const;
	std::vector<Wall>			&getWallsNotConst();

	bool	load(const std::string& filename);
	void	anim();
	void	createDecor(char tile, int x, int y);
};

