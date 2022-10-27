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
	_spells.insert(std::pair<std::string, ASpell *>(spell->getName(), spell));
}

void	Warlock::forgetSpell(std::string const &spellName)
{
	_spells.erase(spellName);
}

void	Warlock::launchSpell(std::string const &spellName, ATarget const &target) const
{
	try
	{
		_spells.at(spellName)->launch(target);
	}
	catch(const std::exception& e)
	{
		(void)e;
	}
}
