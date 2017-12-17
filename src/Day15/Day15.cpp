#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	uint64_t genA = 512;
	uint64_t genB = 191;
	//uint64_t genA = 65;
	//uint64_t genB = 8921;
	
	uint64_t counter_part1 = 0;
	uint64_t counter_part2 = 0;

	for (uint64_t round = 0; round < 40000000; round++)
	{
		genA *= 16807;
		genA %= 2147483647;
		genB *= 48271;
		genB %= 2147483647;

		if ((genA & 0xFFFF) == (genB & 0xFFFF)) {
			counter_part1++;
		}
	}

	cout << "Part 1: " << counter_part1 << endl;

	genA = 512;
	genB = 191;
	for (uint64_t round = 0; round < 5000000; round++)
	{
		do {
			genA *= 16807;
			genA %= 2147483647;
		} while ((genA % 4) != 0);

		do {
			genB *= 48271;
			genB %= 2147483647;	
		} while ((genB % 8) != 0);
		
		if ((genA & 0xFFFF) == (genB & 0xFFFF)) {
			counter_part2++;
		}
	}

	cout << "Part 2: " << counter_part2 << endl;

	return 0;
}

