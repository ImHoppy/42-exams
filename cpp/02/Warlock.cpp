#include "Warlock.hpp"
#include <iostream>

Warlock::Warlock(std::string const & name, std::string const & title) : _name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day." << std::endl;
}
Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!" << std::endl;
}

std::string const &	Warlock::getName() const
{
	return _name;
}
std::string const &	Warlock::getTitle() const
{
	return _title;
}
void	Warlock::setName(std::string const &name)
{
	_name = name;
}
void	Warlock::setTitle(std::string const &title)
{
	_title = title;
}

void	Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}

void	Warlock::learnSpell(ASpell *spell)
{
	_spellBook.learnSpell(spell);
}

void	Warlock::forgetSpell(std::string const &spellName)
{
	_spellBook.forgetSpell(spellName);
}

void	Warlock::launchSpell(std::string const &spellName, ATarget const &target) const
{
	ASpell *spell = _spellBook.createSpell(spellName);
	if (spell == NULL)
		return;
	spell->launch(target);
	delete spell;
}
