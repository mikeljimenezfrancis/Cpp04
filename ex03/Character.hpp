#pragma once

#include "ICharacter.hpp"
#include "AMateria.hpp"

class Character : public ICharacter
{
	public:
		static const int	SLOTS = 4;

		Character();
		Character(const std::string &newName);
		Character(const Character &other);
		Character &operator=(const Character &other);
		virtual ~Character();

		virtual const std::string	&getName() const;
		virtual void				equip(AMateria *m);
		virtual void				unequip(int idx);
		virtual void				use(int idx, ICharacter &target);

		const AMateria				*getMateria(int idx) const;
		int							getFloorCount() const;

	private:
		std::string	name;
		AMateria	*inventory[SLOTS];

		// Materias dropped with unequip() land on the floor.
		// The Character keeps their addresses and deletes them
		// when it is destroyed, so nothing leaks.
		AMateria	**floor;
		int			floorCount;
		int			floorCapacity;

		void		clearInventory();
		void		copyInventory(const Character &other);
		void		dropOnFloor(AMateria *m);
};
