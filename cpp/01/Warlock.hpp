#pragma once
#include <string>
#include "ASpell.hpp"

class Warlock
{
	private:
		std::string	_name;
		std::string	_title;
	public:
		//Warlock();
		Warlock(std::string const &name, std::string const &title);
		~Warlock();
		
		std::string const &	getName() const;
		std::string const &	getTitle() const;
		
		void	setName(std::string const &name);
		void	setTitle(std::string const &title);
		void	introduce() const;

		void	learnSpell(ASpell const *spell);
		void	forgetSpell(std::string const &spellName);
		void	launchSpell(std::string const &spellName, ATarget const &target) const;
};
