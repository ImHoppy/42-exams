#pragma once
#include <string>

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
};
