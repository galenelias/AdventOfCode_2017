#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iomanip>

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

void part1(const string& input)
{
	vector<int> values;
	for (int i = 0; i < 256; i++)
		values.push_back(i);

	vector<string> skips = split(input, ",");

	int skipCount = 0;
	int start = 0;

	for (const auto& skipStr : skips)
	{
		int skipLen = stoi(skipStr);

		for (int i = 0; i < skipLen / 2; i++)
			std::swap(values[(start + i) % values.size()], values[(start + skipLen - i - 1) % values.size()]);

		start = (start + skipLen + skipCount) % values.size();
		skipCount++;
	}

	cout << "Part 1: " << values[0] * values[1] << endl;
}

void part2(const string& input)
{
	vector<int> values;
	for (int i = 0; i < 256; i++)
		values.push_back(i);

	vector<int> skips;
	for (const auto& ch : input)
	{
		skips.push_back((int)ch);
	}
	skips.push_back(17);
	skips.push_back(31);
	skips.push_back(73);
	skips.push_back(47);
	skips.push_back(23);

	int skipCount = 0;
	int start = 0;

	for (int round = 0; round < 64; round++)
	{
		for (const auto& skipLen : skips)
		{
			for (int i = 0; i < skipLen / 2; i++)
				std::swap(values[(start + i) % values.size()], values[(start + skipLen - i - 1) % values.size()]);

			start = (start + skipLen + skipCount) % values.size();
			skipCount++;
		}
	}

	vector<int> dense_hashes;
	for (int i = 0; i < 16; i++)
	{
		int dense_hash = 0;
		for (int j = 0; j < 16; j++)
			dense_hash ^= values[i * 16 + j];

		dense_hashes.push_back(dense_hash);
	}

	for (int i = 0; i < 16; i++)
		cout << hex << setfill('0') << setw(2) << dense_hashes[i];
	cout << endl;
}

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

	string input;
	getline(cin, input);

	part1(input);
	part2(input);

	return 0;
}

