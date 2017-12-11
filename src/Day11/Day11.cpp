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

int dist(int x, int y)
{
	int steps = 0;
	int cx = 0, cy = 0;
	while (cx != x || cy != y)
	{
		if (cx != x)
		{
			int dx = (x - cx) / abs(x - cx);
			int dy = (y == cy) ? 1 : ((y - cy) / abs(y - cy));
			cx += dx;
			cy += dy;
			steps++;
		}
		else
		{
			int dy = (y - cy) / abs(y - cy);
			cy += dy * 2;
			steps++;
		}
	}
	return steps;
}

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

	string input;
	getline(cin, input);

	vector<string> path = split(input, ",");

	int x = 0, y = 0;
	int max_steps = 0;

	for (const auto& dir : path)
	{
		if (dir == "ne") {
			x += 1; y += 1;
		}
		else if (dir == "se") {
			x += 1; y -= 1;
		}
		else if (dir == "nw") {
			x -= 1; y += 1;
		}
		else if (dir == "sw") {
			x -= 1; y -= 1;
		}
		else if (dir == "n") {
			y += 2;
		}
		else if (dir == "s") {
			y -= 2;
		}
		else
		{
			cerr << "Uh oh:" << dir << endl;
		}

		max_steps = std::max(max_steps, dist(x, y));
	}

	cout << x << ", " << y << endl;

	
	cout << dist(x, y) << endl;
	cout << "max: " << max_steps << endl;

	// cout << "Result " << 0 << endl;
	return 0;
}

