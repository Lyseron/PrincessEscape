#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <memory>
#include "Textures.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Collision.hpp"
#include "UI.hpp"

class	Game
{
private:

	static constexpr	double	SPRITE_WIDTH = 56;
	static constexpr	double	SPRITE_HEIGHT = 56;
	static constexpr	int		CASE_TILE = 64;
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
	bool		loadDecor();
	bool		loadDoor();
	bool		loadUI();
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
	bool	m_oPressed;

	void	handleEvent();								// for the event like keypress, mouse ect
	void	keyPress(SDL_Event event);
	void	keyRelease(SDL_Event event);
	bool 	movePlayer(double dirX, double dirY);
	void	actionKeyPress();

// ---------------------- UPDATE ------------------------ //

	void	VisualChange();									// to utpdate the value after an event
	void	handleMovement();

// ---------------------- RENDER ------------------------- //

	UI		m_ui;
	void	render();									// to display the element in the window

	void	drawMapComponent(int x, int y, TextureID texture, char c, int frame);
	void	drawMap();
	void	drawDecor();
	void	drawPlayer();
	void	drawChests();
	void	drawLoot(Chest &chest);
	void	drawDoors();

// DEBUG
	void	drawDebugCollision(const Collision &collision, double posX, double posY);
	void	drawDebugCase(double caseX, double caseY);
	void	drawDebugInteraction();

// ---------------------- PLAYER ------------------------ //
	Player	m_player;
	Collision	m_walCollision;


	bool	move(double dirX, double dirY);
	bool	inCollisionWall(double nextX, double nextY);
	bool	inCollisionDecor(double nextX, double nextY);
	bool	inCollisionChest(double nextX, double nextY);
	bool	inCollisionDoor(double nextX, double nextY);
	bool	collisionPlayer(double nextX, double nextY);

	bool	m_isInventoryOpen = false;

public:
// ---------------------- CONST/DEST -------------------- //
	Game();												// Game constructor
	~Game();											// Game destructor

	Player	&getPlayer();
	SDL_Renderer*	getRenderer();
	int	getCaseTile();
	bool	isInventoryOpen();

// ---------------------- OTHER METHOC ------------------ //
	void run();											// Master fonction
	void	drawTexture(int win_x,
		int win_y,
		TextureID id,
		int frame
	);

// ---------------------- OTHER METHOD ------------------ //

	void	useSelectedItem();

	void	drawTextureScale(float win_x,
		float win_y,
		TextureID id,
		int frame,
		float scale
	);
};
