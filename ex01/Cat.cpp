#include "Cat.hpp"
#include <iostream>

Cat::Cat() : Animal(), brain(new Brain())
{
	type = "Cat";
	std::cout << "Cat default constructor called" << std::endl;
}

// deep copy: the new Cat gets its own Brain
Cat::Cat(const Cat &other) : Animal(other), brain(new Brain(*other.brain))
{
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other)
{
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*brain = *other.brain; // copy the content, not the pointer
	}
	return (*this);
}

Cat::~Cat()
{
	std::cout << "Cat destructor called" << std::endl;
	delete brain;
}

void	Cat::makeSound() const
{
	std::cout << "Meow!" << std::endl;
}

const std::string	&Cat::getIdea(int index) const
{
	return (brain->getIdea(index));
}

void	Cat::setIdea(int index, const std::string &idea)
{
	brain->setIdea(index, idea);
}

const Brain	*Cat::getBrain() const
{
	return (brain);
}
