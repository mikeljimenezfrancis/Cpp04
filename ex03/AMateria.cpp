#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <iostream>

AMateria::AMateria() : type("unknown")
{
}

AMateria::AMateria(const std::string &newType) : type(newType)
{
}

AMateria::AMateria(const AMateria &other) : type(other.type)
{
}

// Assigning one Materia to another must not copy the type:
// an Ice stays an Ice. There is nothing else to copy.
AMateria &AMateria::operator=(const AMateria &other)
{
	(void)other;
	return (*this);
}

AMateria::~AMateria()
{
}

const std::string	&AMateria::getType() const
{
	return (type);
}

void	AMateria::use(ICharacter &target)
{
	std::cout << "* uses an unknown materia on " << target.getName() << " *" << std::endl;
}
