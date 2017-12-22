#include <iostream>
#include <string>
#include <vector>
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
	vector<string> result(sz, string(sz, ' '));
	for (int r = 0; r < sz; ++r)
		for (int c = 0; c < sz; ++c)
			result[c][sz-1-r] = input[r][c];

	return result;
}

vector<string> flip(const vector<string>& input)
{
	const int sz = input.size();
	vector<string> result(sz, string(sz, ' '));
	for (int r = 0; r < sz; ++r)
		for (int c = 0; c < sz; ++c)
			result[r][sz-1-c] = input[r][c];

	return result;
}

void AddPermutatons(const vector<string>& input, const vector<string>& output, map<vector<string>,vector<string>>& map)
{
	vector<string> temp = input;
	for (int i = 0; i < 4; i++)
	{
		map[temp] = output;
		map[flip(temp)] = output;
		temp = rotate90(temp);
	}
}

void Resample(const vector<string>& input, vector<string>& output, int gridSize, const map<vector<string>,vector<string>>& map)
{
	for (int row = 0; row < input.size() / gridSize; row++)
	{
		for (int col = 0; col < input.size() / gridSize; col++)
		{
			vector<string> sq(gridSize, string(gridSize, ' '));

			for (int sr = 0; sr < gridSize; sr++)
				for (int sc = 0; sc < gridSize; sc++)
					sq[sr][sc] = input[row * gridSize + sr][col * gridSize + sc];

			auto iter = map.find(sq);
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

size_t CountPixels(const vector<string>& image)
{
	size_t on = 0;
	for (auto& row : image)
		for (auto& ch : row)
			if (ch == '#')
				on++;
	return on;
}

int main()
{
	map<vector<string>,vector<string>> rules;

	string input;
	while (getline(cin, input) && !input.empty())
	{
		vector<string> rule2 = split(input, " => ");
		vector<string> left = split(rule2[0], "/");
		vector<string> right = split(rule2[1], "/");

		AddPermutatons(left, right, rules);
	}

	vector<string> image {".#.","..#","###"};
	for (int i = 0; i < 18; i++)
	{
		if (i == 5)
			cout << "Part 1: " << CountPixels(image) << endl;

		int sampleSize = ((image.size() % 2) == 0) ? 2 : 3;
		int newSize = image.size() * (sampleSize + 1) / sampleSize;
		vector<string> output(newSize, string(newSize, ' '));
		Resample(image, output, sampleSize, rules);
		image = std::move(output);
	}

	cout << "Part 2: " << CountPixels(image) << endl;

	return 0;
}

