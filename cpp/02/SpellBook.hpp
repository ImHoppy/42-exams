#pragma once
#include "ASpell.hpp"
#include <string>
#include <map>

class SpellBook {
	private:
		std::map<std::string, ASpell *>	_spells;

		SpellBook(SpellBook const & cpy);
		SpellBook & operator=(SpellBook const & other);

	public:
		SpellBook();
		~SpellBook();

		void	learnSpell(ASpell *spell);
		void	forgetSpell(std::string const & spellName);
		ASpell*	createSpell(std::string const & spellName) const;
};