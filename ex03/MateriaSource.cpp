#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < SLOTS; i++)
		templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &other) : IMateriaSource()
{
	for (int i = 0; i < SLOTS; i++)
		templates[i] = NULL;
	copyFrom(other);
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	clear();
}

void	MateriaSource::clear()
{
	for (int i = 0; i < SLOTS; i++)
	{
		delete templates[i];
		templates[i] = NULL;
	}
}

void	MateriaSource::copyFrom(const MateriaSource &other)
{
	for (int i = 0; i < SLOTS; i++)
	{
		if (other.templates[i])
			templates[i] = other.templates[i]->clone();
	}
}

// The source takes ownership of m (the subject passes "new Ice()").
// If m cannot be stored, it is deleted so it does not leak.
void	MateriaSource::learnMateria(AMateria *m)
{
	if (m == NULL)
		return ;
	for (int i = 0; i < SLOTS; i++)
	{
		if (templates[i] == m) // already learned, keep it
			return ;
	}
	for (int i = 0; i < SLOTS; i++)
	{
		if (templates[i] == NULL)
		{
			templates[i] = m;
			return ;
		}
	}
	delete m;
}

AMateria	*MateriaSource::createMateria(const std::string &type)
{
	for (int i = 0; i < SLOTS; i++)
	{
		if (templates[i] && templates[i]->getType() == type)
			return (templates[i]->clone());
	}
	return (0);
}
