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

	bool		m_showLoot;
	bool		m_lootTaken;

public:
// ---------------------- CONST/DEST -------------------- //
	Chest(int x, int y);
	~Chest();

// ---------------------- SETTER ------------------------ //
	void	setState(ChestState state);
	void	setShowLoot(bool showLoot);
	void	setLootTaken(bool lootTaken);

// ---------------------- GETTER ------------------------ //

	ChestState	getChestState()		const;
	bool		hasLootBeenTaken()	const;
	bool		showLoot()			const;

// ---------------------- OTHER METHOD ------------------ //

	void	animChest();
	void	interact(Player &player);
	
};

