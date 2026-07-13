#include "Animation.hpp"

Animation::Animation(/* args */)
	: m_currentFrame(0),
	m_frameDuration(0),
	m_nbLoop(0),
	m_nbFrame(0) {}

void	Animation::setCurrentFrame(int frame) 	{ this->m_currentFrame = frame; }
void	Animation::setTimerFrame(int timer) 	{ this->m_frameDuration = timer; }
void	Animation::setNbLoop(int nbLoop) 		{ this->m_nbLoop = nbLoop; }
void	Animation::setNbFrame(int nbOfFrame)	{ this->m_nbFrame = nbOfFrame; }


int		Animation::getCurrentFrame()	const { return (m_currentFrame); }
int		Animation::getFrameDuration()	const { return (this->m_frameDuration); }
int		Animation::getNbLoop()			const { return (this->m_nbLoop); }
int		Animation::getNbFrame()			const { return (this->m_nbFrame); }

bool	Animation::moveOnLoop()
{
	this->m_nbLoop++;
	if (this->m_nbLoop >= this->m_frameDuration)
	{
		this->m_nbLoop = 0;
		this->m_currentFrame++;
		if (this->m_currentFrame >= this->m_nbFrame)
			this->m_currentFrame = 0;
		return (true);
	}
	return (false);
}

bool	Animation::moveOnce()
{
	this->m_nbLoop++;
	if (this->m_nbLoop >= this->m_frameDuration)
	{
		this->m_nbLoop = 0;
		this->m_currentFrame++;
		if (this->m_currentFrame >= this->m_nbFrame)
		{
			this->m_currentFrame = this->m_nbFrame -1;
			return (true);
		}
	}
	return (false);
}

void	Animation::reset(int nbFrame, int timerDuration)
{
	m_currentFrame = 0;
	m_frameDuration = timerDuration;
	m_nbLoop = 0;
	m_nbFrame = nbFrame;
}

Animation::~Animation() {}