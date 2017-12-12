#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

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

void twist(vector<int>& buffer, const vector<int> lengths, int rounds)
{
	int skipCount = 0;
	int start = 0;

	for (int round = 0; round < rounds; ++round)
	{
		for (int len : lengths)
		{
			for (int i = 0; i < len / 2; i++)
				std::swap(buffer[(start + i) % buffer.size()], buffer[(start + len - i - 1) % buffer.size()]);

			start = (start + len + skipCount) % buffer.size();
			skipCount++;
		}
	}
}

int part1(const string& input)
{
	vector<int> buffer;
	for (int i = 0; i < 256; i++)
		buffer.push_back(i);

	vector<string> lengthStrs = split(input, ",");
	vector<int> lengths;
	transform(lengthStrs.begin(), lengthStrs.end(), back_inserter(lengths), [](const string& str) { return stoi(str); });

	twist(buffer, lengths, 1 /*round*/);
	return buffer[0] * buffer[1];
}

string part2(const string& input)
{
	vector<int> buffer;
	for (int i = 0; i < 256; i++)
		buffer.push_back(i);

	vector<int> lengths;
	for (const auto& ch : input)
		lengths.push_back((int)ch);

	vector<int> extraLengths { 17, 31, 73, 47, 23};
	lengths.insert(lengths.end(), extraLengths.begin(), extraLengths.end());

	twist(buffer, lengths, 64 /*rounds*/);

	ostringstream oss;
	for (int i = 0; i < 16; i++)
	{
		int dense_hash = 0;
		for (int j = 0; j < 16; j++)
			dense_hash ^= buffer[i * 16 + j];

		oss << hex << setfill('0') << setw(2) << dense_hash;
	}

	return oss.str();
}

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

	string input;
	getline(cin, input);

	cout << "Part 1: " << part1(input) << endl;
	cout << "Part 2: " << part2(input) << endl;

	return 0;
}

