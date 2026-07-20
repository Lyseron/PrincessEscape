#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "Interactable.hpp"
#include "Inventory.hpp"

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
	Item		m_loot;

	void	setAnimation(ChestState state);

public:
// ---------------------- CONST/DEST -------------------- //
	Chest(int x, int y, Item loot = Item::None);
	~Chest();

// ---------------------- SETTER ------------------------ //
	void	setState(ChestState state);
	void	setShowLoot(bool showLoot);
	void	setLootTaken(bool lootTaken);

// ---------------------- GETTER ------------------------ //

	ChestState	getChestState()		const;
	bool		hasLootBeenTaken()	const;
	bool		showLoot()			const;
	Item		getLoot()			const;

// ---------------------- OTHER METHOD ------------------ //

	void	animChest(double deltaTime);
	void	interact(Player &player);
	
};
