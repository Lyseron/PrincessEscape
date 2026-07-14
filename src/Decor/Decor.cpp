#include "Decor.hpp"

Decor::Decor(DecorType decor, int caseX, int caseY)
	:m_decorType(decor),
	m_caseX(caseX),
	m_caseY(caseY),
	m_offsetX(0),
	m_offsetY(0)
{
	switch (m_decorType)
	{
	case DecorType::Chandelier:
		m_texture = TextureID::Chandelier;
		m_animation.reset(2, 1000);
		m_blockingObject = true;
		m_offsetY = -50;
		break;
	case DecorType::Armure:
		m_texture = TextureID::Armure;
		m_animation.reset(2, 1000);
		m_blockingObject = true;
		break;
	case DecorType::FloatingCandle:
		m_texture = TextureID::FloatingCandle;
		m_animation.reset(4, 1000);
		m_blockingObject = true;
		break;
	default:
		break;
	}
}

int		Decor::getCaseX()	const { return (this->m_caseX); }
int		Decor::getCaseY()	const { return (this->m_caseY); }

int		Decor::getOffsetX()	const { return (this->m_offsetX); }
int		Decor::getOffsetY()	const { return (this->m_offsetY); }

TextureID	Decor::getTexture() const { return (this->m_texture); }

bool	Decor::isblockingObject()	const { return (this->m_blockingObject); }
int		Decor::getCurrentFrame()	const { return (this->m_animation.getCurrentFrame()); }

void	Decor::update() { m_animation.moveOnLoop(); }

Decor::~Decor() {}