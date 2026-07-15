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

const	std::vector<Decor>		&Map::getDecors()	const { return (this->m_decors); }
std::vector<Decor>				&Map::getDecorsNotConst() { return (this->m_decors); }

size_t	Map::getChestCount()					const { return (this->m_chest.size()); }
const	std::vector<Chest> &Map::getChests()	const { return (this->m_chest); }
std::vector<Chest> 			&Map::getChestsNotConst() { return (this->m_chest); }

const	std::vector<Door> &Map::getDoors()	const { return (this->m_doors); }
std::vector<Door> 			&Map::getDoorsNotConst() { return (this->m_doors); }

void	Map::anim()
{
	for (Decor &decor : m_decors)
		decor.update();
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
			char	charCase = getCharFromTile(x, y);
			if (charCase == 'P')
			{
				this->firstPlayerPosX = x;
				this->firstPlayerPosY = y;
				this->m_map[y][x] = '.';
			}
			if (charCase == 'C')
			{
				m_chest.emplace_back(x, y);
				this->m_map[y][x] = '.';
			}
			if (charCase == 'D')
			{
				m_doors.emplace_back(x, y);
				this->m_map[y][x] = '.';
			}
			createDecor(charCase, x, y);
		}
	}
	return (true);
}

void	Map::createDecor(char tile, int x, int y)
{
	switch (tile)
	{
	case 'K':
		m_decors.emplace_back(
			DecorType::Chandelier,
			x,
			y
		);
		m_map[y][x] = '.';
		break;
	case 'A':
		m_decors.emplace_back(
			DecorType::Armure,
			x,
			y
		);
		m_map[y][x] = '.';
		break ;
	case 'Q':
		m_decors.emplace_back(
			DecorType::FloatingCandle,
			x,
			y
		);
		m_map[y][x] = '.';
	default:
		break;
	}
}
