#include "ASpell.hpp"

ASpell::ASpell()
{}

ASpell::ASpell(std::string const & name, std::string const & effects): _name(name), _effects(effects)
{}

ASpell::ASpell(ASpell const & cpy)
{
	*this = cpy;
}

ASpell::~ASpell()
{}

ASpell & ASpell::operator=(ASpell const & other)
{
	if (this == &other)
		return *this;
	_name = other._name;
	_effects = other._effects;
	return *this;
}

std::string const & ASpell::getName() const
{
	return _name;
}

std::string const & ASpell::getEffects() const
{
	return _effects;
}

void	ASpell::launch(ATarget const &a) const
{
	a.getHitBySpell(*this);
}
