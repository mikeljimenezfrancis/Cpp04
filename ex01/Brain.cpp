#include "Brain.hpp"
#include <iostream>

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain &other)
{
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < IDEAS; i++)
		ideas[i] = other.ideas[i];
}

Brain &Brain::operator=(const Brain &other)
{
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < IDEAS; i++)
			ideas[i] = other.ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

const std::string	&Brain::getIdea(int index) const
{
	static const std::string	empty;

	if (index < 0 || index >= IDEAS)
		return (empty);
	return (ideas[index]);
}

void	Brain::setIdea(int index, const std::string &idea)
{
	if (index < 0 || index >= IDEAS)
		return ;
	ideas[index] = idea;
}
