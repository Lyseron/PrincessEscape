#pragma once

class Animation
{
private:

	int		m_currentFrame;
	int		m_frameDuration;
	int		m_nbLoop;
	int		m_nbFrame;

public:

// ---------------------- CONST/DEST -------------------- //
	Animation(/* args */);
	~Animation();

// ---------------------- SETTER ------------------------ //
	void	setCurrentFrame(int frame);
	void	setTimerFrame(int timer);
	void	setNbLoop(int nbLoop);
	void	setNbFrame(int nbOfFrame);

// ---------------------- GETTER ------------------------ //
	int	getCurrentFrame()	const;
	int	getFrameDuration()	const;
	int	getNbLoop()			const;
	int	getNbFrame()		const;

// ---------------------- OTHER METHOD ------------------ //
	bool	moveOnLoop();
	bool	moveOnce();

	void	reset(int nbFrame, int timerDuration);

};


