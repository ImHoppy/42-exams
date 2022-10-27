#pragma once
#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget {
	private:
		std::string	_type;
	public:
		
		ATarget();
		ATarget(std::string const & type);
		ATarget(ATarget const & cpy);
		virtual ~ATarget();

		ATarget & operator=(ATarget const & other);

		virtual ATarget * 	clone() const = 0;

		std::string const & getType() const;
		void	getHitBySpell(ASpell const & spell) const;
};