#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
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

vector<string> split_any(const string& input, const string& separators)
{
	vector<string> result;
	size_t last_pos = 0;
	size_t pos = 0;
	while ((pos = input.find_first_of(separators, last_pos)) != string::npos)
	{
		if (pos - last_pos > 0)
			result.push_back(input.substr(last_pos, pos - last_pos));
		last_pos = pos + 1;
	}
	result.push_back(input.substr(last_pos));
	return result;
}

enum Direction {
	Up, Right, Down, Left,
};

enum State {
	Clean, Weakened, Infected, Flagged
};

int main()
{
	vector<string> grid_input;

	string input;
	while (getline(cin, input) && !input.empty())
	{
		grid_input.push_back(input);
	}

	// set<pair<int,int>> infected;
	map<pair<int,int>, State> states;

	for (int r = 0; r < grid_input.size(); r++)
	{
		for (int c = 0; c < grid_input[r].size(); c++)
		{
			if (grid_input[r][c] == '#')
				states[{r-grid_input.size()/2, c-grid_input.size()/2}] = Infected;
		}
	}

	pair<int,int> pos {0,0};
	Direction dir = Up;
	int infections = 0;
	for (int i = 0; i < 10000000; i++)
	{
		State state = states[pos];
		if (state == Infected) {
			states[pos] = Flagged;
			// turn right
			dir = (Direction)((dir + 1) % 4);
		} else if (state == Clean) {
			states[pos] = Weakened;
			// turn left
			dir = (Direction)((dir + 3) % 4);
		} else if (state == Flagged) {
			states[pos] = Clean;
			dir = (Direction)((dir + 2) % 4);
		} else if (state == Weakened) {
			states[pos] = Infected;
			infections++;
		}

		if (dir == Up)
			pos = {pos.first - 1, pos.second};
		else if (dir == Right)
			pos = {pos.first, pos.second + 1};
		else if (dir == Down)
			pos = {pos.first + 1, pos.second};
		else if (dir == Left)
			pos = {pos.first, pos.second - 1};
	}

	cout << "Infection count: " << infections << endl;

	return 0;
}

