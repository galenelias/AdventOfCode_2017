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

unordered_map<int, vector<int>> nodes;


void find_closure(int node, unordered_set<int>& closure)
{
	if (closure.count(node) != 0)
		return;

	closure.insert(node);

	for (int neighbor : nodes[node])
	{
		find_closure(neighbor, closure);
	}
}

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

	string input;

	while (getline(cin, input) && !input.empty())
	{
		vector<string> a = split(input, " <-> ");
		int n = stoi(a[0]);

		vector<int> neighbors;
		if (a.size() > 1)
		{
			vector<string> b = split(a[1], ", ");
			for (const auto& c : b)
				neighbors.push_back(stoi(c));
		}

		nodes[n] = neighbors;
	}

	unordered_set<int> closure_0;
	find_closure(0, closure_0);

	vector<unordered_set<int>> allGroups;

	for (const auto& kv : nodes)
	{
		bool found = false;
		for (const auto& group : allGroups)
		{
			if (group.count(kv.first) != 0)
				found = true;
		}

		if (found == false)
		{
			unordered_set<int> closure;
			find_closure(kv.first, closure);
			allGroups.push_back(std::move(closure));
		}
	}

	cout << "Part 1: " << closure_0.size() << endl;
	cout << "Part 2: " << allGroups.size() << endl;

	return 0;
}

