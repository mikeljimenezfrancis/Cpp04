#pragma once

#include "IMateriaSource.hpp"
#include "AMateria.hpp"

class MateriaSource : public IMateriaSource
{
	public:
		static const int	SLOTS = 4;

		MateriaSource();
		MateriaSource(const MateriaSource &other);
		MateriaSource &operator=(const MateriaSource &other);
		virtual ~MateriaSource();

		virtual void		learnMateria(AMateria *m);
		virtual AMateria	*createMateria(const std::string &type);

	private:
		AMateria	*templates[SLOTS];

		void		clear();
		void		copyFrom(const MateriaSource &other);
};
