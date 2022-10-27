#pragma once
#include <string>
#include "ATarget.hpp"

class ATarget;

class ASpell {
	private:
		std::string	_name;
		std::string	_effects;
	public:
		
		ASpell();
		ASpell(std::string const & name, std::string const & effects);
		ASpell(ASpell const & cpy);
		virtual ~ASpell();

		ASpell & operator=(ASpell const & other);

		virtual ASpell * 	clone() const = 0;

		std::string const & getName() const;
		std::string const & getEffects() const;

		void	launch(ATarget const &a) const;
};