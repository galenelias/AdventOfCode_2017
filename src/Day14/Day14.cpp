#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

string knot_hash(const string& input)
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

	ostringstream oss;
	for (int i = 0; i < 16; i++)
	{
		int dense_hash = 0;
		for (int j = 0; j < 16; j++)
			dense_hash ^= values[i * 16 + j];

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
	vector<string> lines;
	vector<vector<string>> lines_split;

	string input;
	getline(cin, input);


	for (int i = 0; i < 128; i++)
	{
		string row_str = input + "-" + to_string(i);
		string hash = knot_hash(row_str);

		int j = 0;
		for (char ch : hash)
		{
			string temp;
			temp += ch;

			long n = strtol(temp.c_str(), nullptr, 16);

			grid[i][j * 4 + 0] = !!(n & 0x8);
			grid[i][j * 4 + 1] = !!(n & 0x4);
			grid[i][j * 4 + 2] = !!(n & 0x2);
			grid[i][j * 4 + 3] = !!(n & 0x1);

			j++;
		}
	}

	int filled = 0;
	for (int i = 0; i < 128; i++)
		for (int j = 0; j < 128; j++)
			if (grid[i][j])
				filled++;

	int next_color = 1;

	cout << "Part 1: " << filled << endl;

	for (int i = 0; i < 128; i++)
	{
		for (int j = 0; j < 128; j++)
		{
			if (grid[i][j] && cgrid[i][j] == 0)
			{
				fill_color(i, j, next_color++);
			}
		}
	}

	cout << "Part 2: " << next_color - 1 << " regions" << endl;

	return 0;
}

