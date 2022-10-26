#include "Warlock.hpp"
#include <iostream>

Warlock::Warlock(std::string const & name, std::string const & title) : _name(name), _title(title)
{
	std::cout << name << ": constuctor" << std::endl;
}
Warlock::~Warlock()
{
	std::cout << _name << ": destructor" << std::endl;
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
	std::cout << _name << ": introduce" << std::endl;
}
