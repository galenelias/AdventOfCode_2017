#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

void twist(vector<int>& buffer, const vector<int> lengths, int rounds)
{
	int skipCount = 0;
	int start = 0;

	const size_t buf_len = buffer.size();
	for (int round = 0; round < rounds; ++round)
	{
		for (int len : lengths)
		{
			for (int i = 0; i < len / 2; i++)
				std::swap(buffer[(start + i) % buf_len], buffer[(start + len - i - 1) % buf_len]);

			start = (start + len + skipCount) % buf_len;
			skipCount++;
		}
	}
}

string knot_hash(const string& input)
{
	vector<int> buffer;
	buffer.reserve(256);
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
		for (size_t j = 0; j < 16; j++)
			dense_hash ^= buffer[i * 16 + j];

		oss << hex << setfill('0') << setw(2) << dense_hash;
	}

	return oss.str();
}

bool grid[128][128] = { 0 };
int cgrid[128][128] = { 0 };

void fill_color(int i, int j, int color)
{
	if (i < 0 || i >= 128 || j < 0 || j >= 128 || !grid[i][j] || cgrid[i][j] != 0)
		return;

	cgrid[i][j] = color;
	fill_color(i - 1, j, color);
	fill_color(i + 1, j, color);
	fill_color(i, j - 1, color);
	fill_color(i, j + 1, color);
}

int main()
{
	string input;
	getline(cin, input);

	for (size_t i = 0; i < 128; i++)
	{
		string row_str = input + "-" + to_string(i);
		string hash = knot_hash(row_str);

		for (size_t j = 0; j < hash.size(); j++)
		{
			string hexDigitStr {hash[j]};
			long n = strtol(hexDigitStr.c_str(), nullptr, 16);

			grid[i][j * 4 + 0] = n & 0x8;
			grid[i][j * 4 + 1] = n & 0x4;
			grid[i][j * 4 + 2] = n & 0x2;
			grid[i][j * 4 + 3] = n & 0x1;
		}
	}

	size_t countBits = 0;
	for (size_t i = 0; i < 128; i++)
		for (size_t j = 0; j < 128; j++)
			if (grid[i][j])
				countBits++;

	cout << "Part 1: " << countBits << endl;

	int next_color = 0;
	for (size_t i = 0; i < 128; i++)
		for (size_t j = 0; j < 128; j++)
			if (grid[i][j] && cgrid[i][j] == 0)
				fill_color(i, j, ++next_color);

	cout << "Part 2: " << next_color << " regions" << endl;

	return 0;
}
