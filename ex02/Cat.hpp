#pragma once

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal
{
	private:
		Brain	*brain;

	public:
		Cat();
		Cat(const Cat &other);
		Cat &operator=(const Cat &other);
		virtual ~Cat();

		virtual void		makeSound() const;
		const std::string	&getIdea(int index) const;
		void				setIdea(int index, const std::string &idea);
		const Brain			*getBrain() const;
};
