#include "AAnimal.hpp"
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
		const AAnimal	*j = new Dog();
		const AAnimal	*i = new Cat();

		delete j; // should not create a leak
		delete i;
	}

	title("Array of Animals: half Dogs, half Cats");
	{
		const int	size = 6;
		AAnimal		*animals[size];

		for (int k = 0; k < size; k++)
		{
			if (k < size / 2)
				animals[k] = new Dog();
			else
				animals[k] = new Cat();
		}
		std::cout << "--- sounds ---" << std::endl;
		for (int k = 0; k < size; k++)
		{
			std::cout << "[" << k << "] " << animals[k]->getType() << ": ";
			animals[k]->makeSound();
		}
		std::cout << "--- deleting through AAnimal* ---" << std::endl;
		for (int k = 0; k < size; k++)
			delete animals[k];
	}

	title("Deep copy: Dog copy constructor");
	{
		Dog	original;

		original.setIdea(0, "chase the ball");
		original.setIdea(1, "eat the shoe");

		Dog	copy(original);

		copy.setIdea(0, "sleep on the couch");
		std::cout << "original idea 0: " << original.getIdea(0) << std::endl;
		std::cout << "copy idea 0:     " << copy.getIdea(0) << std::endl;
		std::cout << "copy idea 1:     " << copy.getIdea(1) << std::endl;
		std::cout << "different brains: "
			<< (original.getBrain() != copy.getBrain() ? "yes" : "NO") << std::endl;
	}

	title("Deep copy: Cat copy assignment");
	{
		Cat	a;
		Cat	b;

		a.setIdea(42, "knock the glass off the table");
		b = a;
		a.setIdea(42, "ignore the human");
		std::cout << "a idea 42: " << a.getIdea(42) << std::endl;
		std::cout << "b idea 42: " << b.getIdea(42) << std::endl;
		std::cout << "different brains: "
			<< (a.getBrain() != b.getBrain() ? "yes" : "NO") << std::endl;
	}

	title("Deep copy: copy goes out of scope first");
	{
		Dog	basic;

		basic.setIdea(5, "dig a hole");
		{
			Dog	tmp = basic;

			std::cout << "tmp idea 5: " << tmp.getIdea(5) << std::endl;
		} // tmp deletes its own Brain here
		std::cout << "basic idea 5 still valid: " << basic.getIdea(5) << std::endl;
	}

	title("Self assignment and out-of-range ideas");
	{
		Cat			c;
		const Cat	&same = c;

		c.setIdea(0, "nap");
		c = same;
		c.setIdea(-1, "invalid");
		c.setIdea(100, "invalid");
		std::cout << "idea 0: " << c.getIdea(0) << std::endl;
		std::cout << "idea 100: '" << c.getIdea(100) << "'" << std::endl;
	}

	title("AAnimal is abstract");
	{
		// const AAnimal	*meta = new AAnimal(); // does not compile: abstract class
		// AAnimal			animal;                // does not compile either
		const AAnimal	*j = new Dog();
		const AAnimal	&ref = *j;

		std::cout << "AAnimal pointer/reference to a Dog still works: ";
		ref.makeSound();
		delete j;
	}

	title("Wrong classes still behave wrong");
	{
		const WrongAnimal	*w = new WrongCat();

		w->makeSound();
		delete w;
	}
	return (0);
}
