#include "Map.hpp"

#include <fstream>
#include <string>

Map::Map() {}
Map::~Map() {}

int		Map::getWidth()		const 
{
	if (this->m_map.empty())
		return (0);
	return (this->m_map[0].size()); 
}

int		Map::getHeight()	const { return (this->m_map.size()); }

char	Map::getCharFromTile(int x, int y)	const { return (this->m_map[y][x]); }
int 	Map::getFirstPlayerPosX()			const { return (this->firstPlayerPosX); }
int		Map::getFirstPlayerPosY()			const { return (this->firstPlayerPosY); }

int		Map::getCurrentFrame()	const { return (m_animFloatingCandle.getCurrentFrame()); }

size_t	Map::getChestCount()					const { return (this->m_chest.size()); }
const	std::vector<Chest> &Map::getChests()	const { return (this->m_chest); }
std::vector<Chest> &Map::getChestsNotConst() { return (this->m_chest); }

void	Map::anim()
{
	m_animFloatingCandle.moveOnLoop();
}

void	Map::initAnimations()
{
	m_animFloatingCandle.reset(4, 1600);
}

bool	Map::load(const std::string& filename)
{
	std::ifstream	file(filename);
	if (!file)
		return (false);
	std::string	line;
	while (std::getline(file, line))
		this->m_map.push_back(line);
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0;x < getWidth(); x++)
		{
			if (getCharFromTile(x, y) == 'P')
			{
				this->firstPlayerPosX = x;
				this->firstPlayerPosY = y;
				this->m_map[y][x] = '.';
			}
			if (getCharFromTile(x, y) == 'C')
			{
				m_chest.emplace_back(x, y);
				this->m_map[y][x] = '.';
			}
		}
	}
	return (true);
}
