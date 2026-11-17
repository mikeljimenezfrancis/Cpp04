#pragma once

#include <string>

class Brain
{
	public:
		static const int	IDEAS = 100;

		Brain();
		Brain(const Brain &other);
		Brain &operator=(const Brain &other);
		~Brain();

		const std::string	&getIdea(int index) const;
		void				setIdea(int index, const std::string &idea);

	private:
		std::string	ideas[IDEAS];
};
