#pragma once

#include "Interactable.hpp"

class	Player;

enum class DoorState
{
	Closed,
	Opening,
	Opened
};

class Door : public Interactable
{
private:
	DoorState	m_state;
public:
// ---------------------- CONST/DEST -------------------- //
	Door(int caseX, int caseY);
	~Door();

// ---------------------- SETTER ------------------------ //
	void	setState(DoorState state);

// ---------------------- GETTER ------------------------ //

	DoorState	getDoorState()		const;

// ---------------------- OTHER METHOD ------------------ //

// override to say that i changed the heritade fonction tp this one
	void	interact(Player &player)	override;
	void	animDoor();
};
