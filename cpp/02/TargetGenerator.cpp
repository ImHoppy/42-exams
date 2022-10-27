#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator(TargetGenerator const & cpy)
{
	*this = cpy;
}

TargetGenerator & TargetGenerator::operator=(TargetGenerator const & other)
{
	if (this == &other)
		return *this;
	
	return *this;
}


TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{

}


void	TargetGenerator::learnTargetType(ATarget *target)
{

	_targets.insert(std::pair<std::string, ATarget *>(target->getType(), target->clone()));
}

void	TargetGenerator::forgetTargetType(std::string const & targetType)
{
	try {
		delete _targets.at(targetType);
		_targets.erase(targetType);
	} catch (std::exception const & e)
	{
		(void)e;
	}
}

ATarget*	TargetGenerator::createTarget(std::string const & targetType) const
{
	try {
		return _targets.at(targetType)->clone();
	} catch (std::exception const & e)
	{
		(void)e;
	}
	return NULL;
}
