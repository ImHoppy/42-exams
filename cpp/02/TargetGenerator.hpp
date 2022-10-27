#pragma once
#include "ATarget.hpp"
#include <string>
#include <map>

class TargetGenerator {
	private:
		std::map<std::string, ATarget *>	_targets;

		TargetGenerator(TargetGenerator const & cpy);
		TargetGenerator & operator=(TargetGenerator const & other);

	public:
		TargetGenerator();
		~TargetGenerator();

		void	learnTargetType(ATarget *target);
		void	forgetTargetType(std::string const & targetName);
		ATarget*	createTarget(std::string const & targetName) const;
};