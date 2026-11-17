#pragma once

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal
{
	private:
		Brain	*brain;

	public:
		Dog();
		Dog(const Dog &other);
		Dog &operator=(const Dog &other);
		virtual ~Dog();

		virtual void		makeSound() const;
		const std::string	&getIdea(int index) const;
		void				setIdea(int index, const std::string &idea);
		const Brain			*getBrain() const;
};
