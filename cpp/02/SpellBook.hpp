#pragma once
#include <string>

class SpellBook {
	private:
		SpellBook(SpellBook const & cpy);
		SpellBook & operator=(SpellBook const & other);

	public:
		SpellBook();
		~SpellBook();

		void	learnSpell(Aspell *spell);
		void	forgetSpell(std::string const & spellName);
		ASpell*	createSpell(std::string const & spellName) const;
};