#include <iostream>
#include <vector>

using namespace std;

int main()
{
	//vector<int> banks = { 0, 2, 7, 0 };
	vector<int> banks = { 11,11,13,7,0,15,5,5,4,4,1,1,7,1,15,11 };
	vector<vector<int>> memory;

	size_t counter = 0;
	for (;;)
	{
		counter++;
		size_t highestIndex = 0;
		size_t highestMem = 0;
		for (size_t i = 0; i < banks.size(); ++i)
		{
			if (banks[i] > highestMem)
			{
				highestMem = banks[i];
				highestIndex = i;
			}
		}

		banks[highestIndex] = 0;
		for (size_t i = 0; i < highestMem; i++)
		{
			banks[(highestIndex + 1 + i) % banks.size()]++;
		}

		for (size_t i = 0; i < memory.size(); ++i)
		{
			if (memory[i] == banks)
			{
				cout << "Part 1: " << counter << " redistributions\n";
				cout << "Part 2: " << memory.size() - i << " cycle length\n";
				return 0;
			}
		}
		memory.push_back(banks);
	}

    return 0;
}

