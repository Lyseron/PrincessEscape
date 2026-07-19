#include "Animation.hpp"

// ---------------------------------------------------- CONST/DEST ----------------------------------------------------- //

Animation::Animation(/* args */)
	: m_currentFrame(0),
	m_frameDuration(0),
	m_elapsedTime(0),
	m_nbFrame(0) {}

Animation::~Animation() {}

// ---------------------------------------------------- SETTER --------------------------------------------------------- //

void	Animation::setCurrentFrame(int frame) 	{ this->m_currentFrame = frame; }
void	Animation::setTimerFrame(double duration) { this->m_frameDuration = duration; }
void	Animation::setElapsedTime(double elapsedTime) { this->m_elapsedTime = elapsedTime; }
void	Animation::setNbFrame(int nbOfFrame)	{ this->m_nbFrame = nbOfFrame; }

// ---------------------------------------------------- GETTER --------------------------------------------------------- //

int		Animation::getCurrentFrame()	const { return (m_currentFrame); }
double	Animation::getFrameDuration()	const { return (this->m_frameDuration); }
double	Animation::getElapsedTime()		const { return (this->m_elapsedTime); }
int		Animation::getNbFrame()			const { return (this->m_nbFrame); }

// ---------------------------------------------------- OTHER METHOD --------------------------------------------------- //

bool	Animation::moveOnLoop(double deltaTime)
{
	if (m_frameDuration <= 0 || m_nbFrame <= 0)
		return (false);
	m_elapsedTime += deltaTime;
	bool	frameChanged = false;
	while (m_elapsedTime >= m_frameDuration)
	{
		m_elapsedTime -= m_frameDuration;
		m_currentFrame = (m_currentFrame + 1) % m_nbFrame;
		frameChanged = true;
	}
	return (frameChanged);
}

bool	Animation::moveOnce(double deltaTime)
{
	if (m_frameDuration <= 0 || m_nbFrame <= 0)
		return (false);
	m_elapsedTime += deltaTime;
	while (m_elapsedTime >= m_frameDuration)
	{
		m_elapsedTime -= m_frameDuration;
		m_currentFrame++;
		if (m_currentFrame >= m_nbFrame)
		{
			m_currentFrame = m_nbFrame - 1;
			return (true);
		}
	}
	return (false);
}

void	Animation::reset(int nbFrame, double frameDuration)
{
	m_currentFrame = 0;
	m_frameDuration = frameDuration;
	m_elapsedTime = 0;
	m_nbFrame = nbFrame;
}
