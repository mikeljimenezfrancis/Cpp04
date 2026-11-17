#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

static void	title(const std::string &text)
{
	std::cout << std::endl << "===== " << text << " =====" << std::endl;
}

int	main()
{
	title("Subject test");
	{
		const Animal	*meta = new Animal();
		const Animal	*j = new Dog();
		const Animal	*i = new Cat();

		std::cout << j->getType() << " " << std::endl;
		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); // will output the cat sound!
		j->makeSound();
		meta->makeSound();

		delete meta;
		delete j;
		delete i;
	}

	title("Wrong classes: no virtual, so the base version is called");
	{
		const WrongAnimal	*meta = new WrongAnimal();
		const WrongAnimal	*i = new WrongCat();

		std::cout << i->getType() << " " << std::endl;
		i->makeSound(); // will output the WrongAnimal sound
		meta->makeSound();

		delete meta;
		delete i;
	}

	title("WrongCat used directly (static type WrongCat)");
	{
		const WrongCat	wc;

		wc.makeSound();
	}

	title("Objects on the stack and references");
	{
		Dog				dog;
		Cat				cat;
		const Animal	&ref = cat;

		dog.makeSound();
		ref.makeSound();
		std::cout << "ref type: " << ref.getType() << std::endl;
	}

	title("Copy constructor and assignment");
	{
		Dog	a;
		Dog	b(a);
		Cat	c;
		Cat	d;

		d = c;
		std::cout << "b type: " << b.getType() << std::endl;
		std::cout << "d type: " << d.getType() << std::endl;
		b.makeSound();
		d.makeSound();
	}

	title("Array of Animal pointers");
	{
		const Animal	*zoo[4] = { new Dog(), new Cat(), new Animal(), new Dog() };

		for (int k = 0; k < 4; k++)
		{
			std::cout << "[" << k << "] " << zoo[k]->getType() << ": ";
			zoo[k]->makeSound();
		}
		for (int k = 0; k < 4; k++)
			delete zoo[k];
	}
	return (0);
}
