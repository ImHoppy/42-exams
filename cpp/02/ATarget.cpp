#include "ATarget.hpp"
#include <iostream>

ATarget::ATarget()
{}

ATarget::ATarget(std::string const & type): _type(type)
{}

ATarget::ATarget(ATarget const & cpy)
{
	*this = cpy;
}

ATarget::~ATarget()
{}

ATarget & ATarget::operator=(ATarget const & other)
{
	if (this == &other)
		return *this;
	_type = other._type;
	return *this;
}

std::string const & ATarget::getType() const
{
	return _type;
}

void	ATarget::getHitBySpell(ASpell const & spell) const
{
	std::cout << _type << " has been " << spell.getEffects() << "!" << std::endl;
}
