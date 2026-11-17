#include "AMateria.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "Character.hpp"
#include "IMateriaSource.hpp"
#include "MateriaSource.hpp"
#include <iostream>

static void	title(const std::string &text)
{
	std::cout << std::endl << "===== " << text << " =====" << std::endl;
}

static void	subjectTest()
{
	IMateriaSource	*src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter		*me = new Character("me");

	AMateria		*tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter		*bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	delete bob;
	delete me;
	delete src;
}

static void	inventoryTest()
{
	MateriaSource	src;
	Character		alice("alice");
	Character		target("target");

	src.learnMateria(new Ice());
	src.learnMateria(new Cure());

	std::cout << "unknown type -> " << (src.createMateria("fire") ? "materia" : "0") << std::endl;

	for (int i = 0; i < 4; i++)
		alice.equip(src.createMateria(i % 2 ? "cure" : "ice"));

	AMateria	*extra = src.createMateria("ice");
	alice.equip(extra);	// inventory full: nothing happens
	std::cout << "5th materia equipped? "
		<< (alice.getMateria(0) == extra || alice.getMateria(3) == extra ? "yes" : "no") << std::endl;
	delete extra;		// still ours, so we delete it

	alice.equip(NULL);	// nothing happens
	for (int i = 0; i < 4; i++)
		alice.use(i, target);

	std::cout << "-- invalid indices --" << std::endl;
	alice.use(-1, target);
	alice.use(4, target);
	alice.unequip(-1);
	alice.unequip(42);

	std::cout << "-- unequip slot 1, then use it --" << std::endl;
	alice.unequip(1);
	alice.use(1, target);	// empty slot: nothing happens
	alice.unequip(1);		// already empty: nothing happens
	std::cout << "floor count: " << alice.getFloorCount() << std::endl;

	std::cout << "-- equip fills the first empty slot (1) --" << std::endl;
	alice.equip(src.createMateria("ice"));
	alice.use(1, target);

	std::cout << "-- equip the same pointer twice --" << std::endl;
	alice.unequip(2);
	AMateria	*same = src.createMateria("cure");
	alice.equip(same);
	alice.equip(same);	// ignored, no double delete later
	alice.use(2, target);
}

static void	deepCopyTest()
{
	MateriaSource	src;
	Character		original("original");
	Character		dummy("dummy");

	src.learnMateria(new Ice());
	src.learnMateria(new Cure());
	original.equip(src.createMateria("ice"));
	original.equip(src.createMateria("cure"));

	Character		copy(original);

	std::cout << "copy name: " << copy.getName() << std::endl;
	std::cout << "slot 0 is a different object: "
		<< (copy.getMateria(0) != original.getMateria(0) ? "yes" : "NO") << std::endl;

	original.unequip(0);
	std::cout << "original slot 0 after unequip: "
		<< (original.getMateria(0) ? "full" : "empty") << std::endl;
	std::cout << "copy slot 0 still: ";
	copy.use(0, dummy);

	Character		assigned("assigned");
	assigned.equip(src.createMateria("cure"));
	assigned.equip(src.createMateria("cure"));
	assigned.equip(src.createMateria("cure"));
	assigned = original;	// old Materias deleted, new ones cloned
	std::cout << "assigned name: " << assigned.getName() << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << "assigned slot " << i << ": ";
		if (assigned.getMateria(i))
			assigned.use(i, dummy);
		else
			std::cout << "empty" << std::endl;
	}

	const Character	&self = assigned;
	assigned = self;		// self assignment must not delete anything
	assigned.use(1, dummy);
}

static void	sourceTest()
{
	MateriaSource	src;

	for (int i = 0; i < 6; i++)	// only 4 fit, the rest is deleted
		src.learnMateria(new Ice());
	src.learnMateria(NULL);

	MateriaSource	copy(src);
	MateriaSource	assigned;
	assigned.learnMateria(new Cure());
	assigned = src;

	std::cout << "copy creates cure? "
		<< (copy.createMateria("cure") ? "yes" : "no (0)") << std::endl;
	AMateria	*m = assigned.createMateria("ice");
	std::cout << "assigned creates: " << (m ? m->getType() : "0") << std::endl;

	AMateria	*clone = m->clone();
	std::cout << "clone type: " << clone->getType() << std::endl;
	delete clone;
	delete m;
}

static void	materiaAssignTest()
{
	Ice		ice;
	Cure	cure;
	AMateria	&ref = ice;

	ref = cure;	// copying the type makes no sense
	std::cout << "ice type after assignment: " << ice.getType() << std::endl;
}

int	main()
{
	title("Subject test");
	subjectTest();
	title("Inventory");
	inventoryTest();
	title("Deep copy of Character");
	deepCopyTest();
	title("MateriaSource");
	sourceTest();
	title("Materia assignment");
	materiaAssignTest();
	return (0);
}
