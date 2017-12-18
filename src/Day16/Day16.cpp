#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

vector<string> split(const string& input, const string& separator)
{
	vector<string> result;
	size_t last_pos = 0;
	size_t pos = 0;
	while ((pos = input.find(separator, last_pos)) != string::npos)
	{
		if (pos - last_pos > 0)
			result.push_back(input.substr(last_pos, pos - last_pos));
		last_pos = pos + separator.size();
	}
	result.push_back(input.substr(last_pos));
	return result;
}

int main()
{
	string input;
	getline(cin, input);

	vector<string> moves = split(input, ",");

	string dancers;
	for (int i = 0; i < 16; i++)
		dancers.push_back('a' + i);

	unordered_map<string, uint64_t> dance_patterns;

	for (uint64_t i = 0; i < 1000000000; ++i)
	{
		auto find_iter = dance_patterns.find(dancers);
		if (find_iter != end(dance_patterns))
		{
			uint64_t period = i - find_iter->second;
			uint64_t endPosition = 1000000000 % period;

			cout << "end position: " << endPosition << endl;
			for (const auto& kv : dance_patterns)
			{
				if (kv.second == endPosition)
				{
					cout << "Part 2: " << kv.first << endl;
					return 0;
				}
			}
		}
		else
		{
			dance_patterns[dancers] = i;
		}

		for (const auto& move : moves)
		{
			if (move[0] == 's')
			{
				int amt = stoi(move.substr(1));
				rotate(dancers.rbegin(), dancers.rbegin() + amt, dancers.rend());
			}
			else if (move[0] == 'x')
			{
				vector<string> swapPair = split(move.substr(1), "/");
				swap(dancers[stoi(swapPair[0])], dancers[stoi(swapPair[1])]);
			}
			else if (move[0] == 'p')
			{
				auto iterA = find(dancers.begin(), dancers.end(), move[1]);
				auto iterB = find(dancers.begin(), dancers.end(), move[3]);

				swap(*iterA, *iterB);
			}
			else
			{
				cerr << "Unexpected input: " << move << endl;
			}
		}
	}

	//cout << "Part 1: ";
	//for (auto ch : dancers)
	//	cout << ch;
	//cout << endl;

	return 0;
}

