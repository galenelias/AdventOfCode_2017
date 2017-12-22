#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

enum Direction {
	Up, Right, Down, Left,
};

enum State {
	Clean, Weakened, Infected, Flagged
};

namespace std {
	template <>
	class hash<std::pair<int, int>>
	{
	public:
		size_t operator()(const pair<int, int> &x) const
		{
			return x.first * 1337 + x.second;
		}
	};
}

int main()
{
	vector<string> grid_input;

	string input;
	while (getline(cin, input) && !input.empty())
	{
		grid_input.push_back(input);
	}

	unordered_map<pair<int,int>, State> states;
	for (int r = 0; r < grid_input.size(); r++)
		for (int c = 0; c < grid_input[r].size(); c++)
			if (grid_input[r][c] == '#')
				states[{r-grid_input.size()/2, c-grid_input.size()/2}] = Infected;

	pair<int,int> pos {0,0};
	Direction dir = Up;
	int infections = 0;
	for (int i = 0; i < 10000000; i++)
	{
		State& state = states[pos];
		if (state == Clean) {
			state = Weakened;
			dir = (Direction)((dir + 3) % 4); // turn left
		} else if (state == Weakened) {
			state = Infected;
		} else if (state == Infected) {
			state = Flagged;
			dir = (Direction)((dir + 1) % 4); // turn right
		} else if (state == Flagged) {
			state = Clean;
			dir = (Direction)((dir + 2) % 4); // turn around
		}

		if (state == Infected)
			infections++;

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

