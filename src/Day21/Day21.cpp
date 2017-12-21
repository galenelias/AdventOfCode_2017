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

vector<string> rotate90(const vector<string>& input)
{
	const int sz = input.size();
	vector<string> result(sz, string(input.size(), ' '));
	for (int r = 0; r < sz; ++r)
		for (int c = 0; c < sz; ++c)
			result[c][sz-1-r] = input[r][c];

	return result;
}

vector<string> flip(const vector<string>& input)
{
	const int sz = input.size();
	vector<string> result(sz, string(input.size(), ' '));
	for (int r = 0; r < sz; ++r)
		for (int c = 0; c < sz; ++c)
			result[r][sz-1-c] = input[r][c];

	return result;
}

void AddRotations(const vector<string>& input, const vector<string>& output, map<vector<string>,vector<string>>& map)
{
	map[input] = output;
	map[flip(input)] = output;
	vector<string> temp = rotate90(input);
	map[temp] = output;
	map[flip(temp)] = output;
	temp = rotate90(temp);
	map[temp] = output;
	map[flip(temp)] = output;
	temp = rotate90(temp);
	map[temp] = output;
	map[flip(temp)] = output;
}

void Resample(const vector<string>& input, vector<string>& output, int gridSize, const map<vector<string>,vector<string>>& map)
{
	for (int row = 0; row < input.size() / gridSize; row++)
	{
		for (int col = 0; col < input.size() / gridSize; col++)
		{
			vector<string> sq(gridSize, string(gridSize, ' '));

			for (int sr = 0; sr < gridSize; sr++)
			{
				for (int sc = 0; sc < gridSize; sc++)
				{
					sq[sr][sc] = input[row * gridSize + sr][col * gridSize + sc];
				}
			}

			auto iter = map.find(sq);
			if (iter == end(map))
			{
				cerr << "Didn't find square\n";
				return;
			}

			const int gridSizeBig = gridSize + 1;
			const vector<string>& newTile = iter->second;
			for (int sr = 0; sr < gridSizeBig; sr++)
			{
				for (int sc = 0; sc < gridSizeBig; sc++)
				{
					output[row * gridSizeBig + sr][col * gridSizeBig + sc] = newTile[sr][sc];
				}
			}
		}
	}
}

int main()
{
	string input;

	map<vector<string>,vector<string>> rules2x2;
	map<vector<string>,vector<string>> rules3x3;
	while (getline(cin, input) && !input.empty())
	{
		vector<string> rule2 = split(input, " => ");
		vector<string> left = split(rule2[0], "/");
		vector<string> right = split(rule2[1], "/");

		if (left.size() == 2)
			AddRotations(left, right, rules2x2);
		else if (left.size() == 3)
			AddRotations(left, right, rules3x3);
		else
			cerr << "Bad input\n";
	}

	vector<string> image {".#.","..#","###"};

	for (int i = 0; i < 18; i++)
	{
		cout << "iteration " << i << "(" << image.size() << ")" << endl;
		if ((image.size() % 2) == 0)
		{
			int newSize = image.size() * 3 / 2;
			vector<string> output(newSize, string(newSize, ' '));
			Resample(image, output, 2, rules2x2);
			image = output;
		}
		else if ((image.size() % 3) == 0)
		{
			int newSize = image.size() * 4 / 3;
			vector<string> output(newSize, string(newSize, ' '));
			Resample(image, output, 3, rules3x3);
			image = output;
		}
		else
		{
			cerr << "Unexpected size\n";
		}
	}
	int on = 0;
	for (auto& row : image)
		for (auto& ch : row)
			if (ch == '#')
				on++;

	cout << "On pixels: " << on << endl;

	return 0;
}

