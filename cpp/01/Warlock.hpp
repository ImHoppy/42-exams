#pragma once
#include <string>
#include "ASpell.hpp"
#include <map>

class Warlock
{
	private:
		std::string			_name;
		std::string			_title;
		std::map<std::string, ASpell *>	_spells;
	public:
		//Warlock();
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		
		std::string const &	getName() const;
		std::string const &	getTitle() const;
		
		void	setName(std::string const &name);
		void	setTitle(std::string const &title);
		void	introduce() const;

		void	learnSpell(ASpell *spell);
		void	forgetSpell(std::string const &spellName);
		void	launchSpell(std::string const &spellName, ATarget const &target) const;
};
