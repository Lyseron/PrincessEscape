#pragma once

struct Hitbox
{
	double		offsetX;
	double		offsetY;

	double		width;
	double		height;
};

struct Bound
{
	double	left;
	double	top;
	double	right;
	double	bottom;
};

class Collision
{
private:
	Hitbox	m_hitbox;
public:

// ---------------------- CONST/DEST -------------------- //
	Collision(const  Hitbox &hitbox);
	~Collision();

// ---------------------- SETTER ------------------------ //

	void	setHitbox(const Hitbox &hitbox);
	void 	setOffset(double x, double y);

// ---------------------- GETTER ------------------------ //

	Bound	getBoundsObjectInCase(double posX, double posY)	const;

// ---------------------- OTHER METHOD ------------------ //

	bool	isColliding(
		const Collision &hitBoxToTest,
		double posX,
		double posY,
		double testPosX,
		double testPosY
	)	const;
	
};


