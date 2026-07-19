#pragma once

class Animation
{
private:

	int		m_currentFrame;
	double	m_frameDuration;
	double	m_elapsedTime;
	int		m_nbFrame;

public:

// ---------------------- CONST/DEST -------------------- //
	Animation(/* args */);
	~Animation();

// ---------------------- SETTER ------------------------ //
	void	setCurrentFrame(int frame);
	void	setTimerFrame(double duration);
	void	setElapsedTime(double elapsedTime);
	void	setNbFrame(int nbOfFrame);

// ---------------------- GETTER ------------------------ //
	int	getCurrentFrame()	const;
	double	getFrameDuration()	const;
	double	getElapsedTime()	const;
	int	getNbFrame()		const;

// ---------------------- OTHER METHOD ------------------ //
	bool	moveOnLoop(double deltaTime);
	bool	moveOnce(double deltaTime);

	void	reset(int nbFrame, double frameDuration);

};

