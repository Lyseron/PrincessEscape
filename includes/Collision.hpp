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
	Collision(const  Hitbox &hitbox);

	Bound	getBoundsObjectInCase(double posX, double posY)	const;

	void	setHitbox(const Hitbox &hitbox);
	bool	isColliding(
		const Collision &hitBoxToTest,
		double posX,
		double posY,
		double testPosX,
		double testPosY
	)	const;

	void 	setOffset(double x, double y);
	~Collision();
};


