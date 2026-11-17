#include "Character.hpp"
#include <iostream>

Character::Character()
	: name("nobody"), floor(NULL), floorCount(0), floorCapacity(0)
{
	for (int i = 0; i < SLOTS; i++)
		inventory[i] = NULL;
}

Character::Character(const std::string &newName)
	: name(newName), floor(NULL), floorCount(0), floorCapacity(0)
{
	for (int i = 0; i < SLOTS; i++)
		inventory[i] = NULL;
}

// Deep copy: every Materia is cloned. The floor is not copied,
// it belongs to the original Character.
Character::Character(const Character &other)
	: ICharacter(), name(other.name), floor(NULL), floorCount(0), floorCapacity(0)
{
	for (int i = 0; i < SLOTS; i++)
		inventory[i] = NULL;
	copyInventory(other);
}

Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		name = other.name;
		clearInventory();       // old Materias are deleted first ...
		copyInventory(other);   // ... then the new ones are added
	}
	return (*this);
}

Character::~Character()
{
	clearInventory();
	for (int i = 0; i < floorCount; i++)
		delete floor[i];
	delete[] floor;
}

void	Character::clearInventory()
{
	for (int i = 0; i < SLOTS; i++)
	{
		delete inventory[i];
		inventory[i] = NULL;
	}
}

void	Character::copyInventory(const Character &other)
{
	for (int i = 0; i < SLOTS; i++)
	{
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
	}
}

void	Character::dropOnFloor(AMateria *m)
{
	if (floorCount == floorCapacity)
	{
		int			newCapacity = (floorCapacity == 0) ? 4 : floorCapacity * 2;
		AMateria	**bigger = new AMateria*[newCapacity];

		for (int i = 0; i < floorCount; i++)
			bigger[i] = floor[i];
		delete[] floor;
		floor = bigger;
		floorCapacity = newCapacity;
	}
	floor[floorCount++] = m;
}

const std::string	&Character::getName() const
{
	return (name);
}

void	Character::equip(AMateria *m)
{
	if (m == NULL)
		return ;
	for (int i = 0; i < SLOTS; i++)
	{
		if (inventory[i] == m) // already equipped, avoid a double delete
			return ;
	}
	for (int i = 0; i < SLOTS; i++)
	{
		if (inventory[i] == NULL)
		{
			inventory[i] = m;
			return ;
		}
	}
	// inventory full: nothing happens, the caller still owns m
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= SLOTS || inventory[idx] == NULL)
		return ;
	dropOnFloor(inventory[idx]); // not deleted, just left on the floor
	inventory[idx] = NULL;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= SLOTS || inventory[idx] == NULL)
		return ;
	inventory[idx]->use(target);
}

const AMateria	*Character::getMateria(int idx) const
{
	if (idx < 0 || idx >= SLOTS)
		return (NULL);
	return (inventory[idx]);
}

int	Character::getFloorCount() const
{
	return (floorCount);
}
