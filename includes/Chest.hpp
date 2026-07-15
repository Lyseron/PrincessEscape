#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "Interactable.hpp"

enum class	ChestState
{
	Closed,
	Opening,
	Opened
};

class Chest : public Interactable
{
private:
	ChestState	m_state;

public:
// ---------------------- CONST/DEST -------------------- //
	Chest(int x, int y);
	~Chest();

// ---------------------- SETTER ------------------------ //
	void	setState(ChestState state);

// ---------------------- GETTER ------------------------ //

	ChestState	getChestState()		const;

// ---------------------- OTHER METHOD ------------------ //

	void	animChest();
	void	interact(Player &player);
	
};

