#include <iostream>
#include <string>

int main()
{
	for (;;)
	{
		std::string input;
		std::cout << "Input string: ";
		std::getline(std::cin, input);
		if (input.empty())
			break;

		for (int part = 1; part <= 2; ++part)
		{
			int sum = 0;
			for (size_t i = 0; i < input.size(); ++i)
			{
				const size_t nextIndex = (part == 1)
					? (i + 1) % input.size()
					: (i + input.size()/2) % input.size();

				if (input[i] == input[nextIndex])
					sum += input[i] - '0';
			}
			std::cout << "Part " << part << " sum: " << sum << std::endl;
		}

	}
}

