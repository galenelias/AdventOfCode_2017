#include <iostream>
#include <string>

int main()
{
	for (;;)
	{
		std::string input;
		std::cout << "Input string: ";
		std::getline(std::cin, input);

		int sum = 0;
		for (size_t i = 0; i < input.size(); ++i)
		{
			static const int c_part = 1;
			const size_t nextIndexPart1 = (i + 1) % input.size();
			const size_t nextIndexPart2 = (i + input.size()/2) % input.size();
			if (input[i] == input[c_part == 1 ? nextIndexPart1 : nextIndexPart2])
				sum += input[i] - '0';
		}

		std::cout << "Sum: " << sum << std::endl;
	}
}

