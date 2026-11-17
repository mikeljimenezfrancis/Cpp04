#pragma once

#include <string>

class ICharacter;

class AMateria
{
	protected:
		std::string	type;

	public:
		AMateria();
		AMateria(const std::string &newType);
		AMateria(const AMateria &other);
		AMateria &operator=(const AMateria &other);
		virtual ~AMateria();

		const std::string	&getType() const; // returns the materia type

		virtual AMateria	*clone() const = 0;
		virtual void		use(ICharacter &target);
};
