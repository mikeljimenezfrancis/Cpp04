#pragma once

#include <string>

class AAnimal
{
	protected:
		std::string	type;

	public:
		AAnimal();
		AAnimal(const AAnimal &other);
		AAnimal &operator=(const AAnimal &other);
		virtual ~AAnimal();

		const std::string	&getType() const;
		virtual void		makeSound() const = 0; // pure virtual: AAnimal is abstract
};
