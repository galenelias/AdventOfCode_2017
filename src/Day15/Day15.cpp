#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	uint64_t genA = 512;
	uint64_t genB = 191;
	//uint64_t genA = 65;
	//uint64_t genB = 8921;

	uint64_t rounds = 0;
	uint64_t counter = 0;

	vector<uint64_t> a_arr, b_arr;
	a_arr.reserve(4000000);
	b_arr.reserve(4000000);

	//for (uint64_t round = 0; round < 40000000; round++)
	//if (((genA % 4) == 0) && ((genB % 8) == 0) && (genA & 0xFFFF) == (genB & 0xFFFF))

	for (uint64_t round = 0; a_arr.size() != 5000000 || b_arr.size() != 5000000; round++)
	{
		genA *= 16807;
		genA %= 2147483647;
		genB *= 48271;
		genB %= 2147483647;


		if (((genA % 4) == 0) && a_arr.size() < 5000000)
			a_arr.push_back(genA);
		if (((genB % 8) == 0) && b_arr.size() < 5000000)
			b_arr.push_back(genB);
	}

	for (uint64_t i = 0; i < 5000000; ++i)
	{
		if ((a_arr[i] & 0xFFFF) == (b_arr[i] & 0xFFFF))
			counter++;
	}

	cout << counter << endl;

	return 0;
}

