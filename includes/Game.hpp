#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include "Textures.hpp"
#include "Player.hpp"
#include "Map.hpp"

class	Game
{
private:

	static constexpr	double	SPRITE_WIDTH = 56;
	static constexpr	double	SPRITE_HEIGHT = 56;
	static constexpr	int		CASE_TILE = 64;
	// static constexpr	double	PLAYER_FRONT_COLLISION_RIGHT = 64;
	// static constexpr	double	PLAYER_FRONT_COLLISION_LEFT = 64;
	// static constexpr	double	PLAYER_FRONT_COLLISION_TOP = 0.3;
	// static constexpr	double	PLAYER_FRONT_COLLISION_BOTTOMM = 64;
	static constexpr	double	SPEED_PLAYER = 0.001;
	

	Map 	m_map;

// ---------------------- INIT ------------------------ //
	SDL_Color 	m_wallColor;
	SDL_Color 	m_floorColor;

	bool	initSDL();									// init the SDL librairy
	bool	initWindow();								// init the window
	bool	initRenderer();								// init the display
	void	initColors();
	void	initPlayer();
	bool	initMaps();

	Textures*	m_texture;								// pointeur to the Textures class
	bool		loadChest();
	bool		loadPlayer();
	bool		loadWall();
	bool		loadAllImg();								// load all the necessary img once
	bool		initPlayerTextureFromSide(
			TextureID idle,
			TextureID lift,
			TextureID walk,
			TextureID drop
		);

	bool		initAll();

// ---------------------- WINDOW ----------------------- //
	bool			m_running;							// to continue the loop until it's false
	SDL_Window*		m_window;							// pointeur to create the window
	SDL_Renderer*	m_renderer;							// pointeur to draw int the window

// ---------------------- EVENT ------------------------ //
	bool	m_upPressed;
	bool	m_leftPressed;
	bool	m_rightPressed;
	bool	m_downPressed;
	bool	m_openChest;

	void	handleEvent();								// for the event like keypress, mouse ect
	void	keyPress(SDL_Event event);
	void	keyRelease(SDL_Event event);
	bool 	movePlayer(
		double dirX,
		double dirY,
		PlayerState idle,
		PlayerState lift,
		PlayerState walk,
		PlayerState drop
	);
	void	actionInMap();

// ---------------------- UPDATE ------------------------ //

	void	update();									// to utpdate the value after an event
	void	handleMovement();

// ---------------------- RENDER ------------------------- //
	void	render();									// to display the element in the window
	void	drawRectangle(
		int x,
		int y,
		SDL_Color color
	);
	void	drawTexture(int win_x,
		int win_y,
		TextureID id,
		int frame
	);
	void	drawMapComponent(int x, int y, TextureID texture, char c, int frame);
	void	drawMap();
	void	drawPlayer();
	void	drawChests();

// ---------------------- PLAYER ------------------------ //
	Player	m_player;

	bool	move(double dirX, double dirY);
	bool	inCollisionWall(double nextX, double nextY);
	bool	inCollisionChest(double nextX, double nextY);
	bool	collisionPlayer(double nextX, double nextY);

public:
// ---------------------- CONST/DEST -------------------- //
	Game();												// Game constructor
	~Game();											// Game destructor

// ---------------------- OTHER METHOC ------------------ //
	void run();											// Master fonction

};
