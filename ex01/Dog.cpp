#include "Dog.hpp"
#include <iostream>

Dog::Dog() : Animal(), brain(new Brain())
{
	type = "Dog";
	std::cout << "Dog default constructor called" << std::endl;
}

// deep copy: the new Dog gets its own Brain
Dog::Dog(const Dog &other) : Animal(other), brain(new Brain(*other.brain))
{
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog &Dog::operator=(const Dog &other)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*brain = *other.brain; // copy the content, not the pointer
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete brain;
}

void	Dog::makeSound() const
{
	std::cout << "Woof! Woof!" << std::endl;
}

const std::string	&Dog::getIdea(int index) const
{
	return (brain->getIdea(index));
}

void	Dog::setIdea(int index, const std::string &idea)
{
	brain->setIdea(index, idea);
}

const Brain	*Dog::getBrain() const
{
	return (brain);
}
