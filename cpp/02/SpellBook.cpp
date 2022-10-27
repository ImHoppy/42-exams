#include "SpellBook.hpp"

SpellBook::SpellBook(SpellBook const & cpy)
{
	*this = cpy;
}

SpellBook & SpellBook::operator=(SpellBook const & other)
{
	if (this == &other)
		return *this;
	
	return *this;
}


SpellBook::SpellBook()
{

}

SpellBook::~SpellBook()
{

}


void	SpellBook::learnSpell(ASpell *spell)
{

	_spells.insert(std::pair<std::string, ASpell *>(spell->getName(), spell->clone()));
}

void	SpellBook::forgetSpell(std::string const & spellName)
{
	try {
		delete _spells.at(spellName);
		_spells.erase(spellName);
	} catch (std::exception const & e)
	{
		(void)e;

	}
}

ASpell*	SpellBook::createSpell(std::string const & spellName) const
{
	try {
		return _spells.at(spellName)->clone();
	} catch (std::exception const & e)
	{
		(void)e;
	}
	return NULL;
}
