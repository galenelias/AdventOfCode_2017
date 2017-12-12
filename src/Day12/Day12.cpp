#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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

void find_group(int node, unordered_map<int, vector<int>>& nodes, unordered_set<int>& group)
{
	auto result = group.insert(node);
	if (result.second == false) // Not inserted, therefore already known
		return;

	for (int neighbor : nodes[node])
		find_group(neighbor, nodes, group);
}

int main()
{
	unordered_set<int> ungroupedNodes;
	unordered_map<int, vector<int>> nodes;

	string input;
	while (getline(cin, input) && !input.empty())
	{
		vector<string> a = split(input, " <-> ");
		int n = stoi(a[0]);

		vector<int> neighbors;
		vector<string> b = split(a[1], ", ");
		for (const auto& c : b)
			neighbors.push_back(stoi(c));

		ungroupedNodes.insert(n);
		nodes[n] = std::move(neighbors);
	}

	vector<unordered_set<int>> allGroups;
	while (!ungroupedNodes.empty())
	{
		unordered_set<int> group;
		find_group(*(ungroupedNodes.begin()), nodes, group);

		for (int node : group)
			ungroupedNodes.erase(node);

		allGroups.push_back(std::move(group));
	}

	size_t group0size = find_if(allGroups.begin(), allGroups.end(),
						[](auto& group) { return group.count(0) == 1; })->size();

	cout << "Group 0 size (Part 1): " << group0size << endl;
	cout << "Number of groups (Part 2): " << allGroups.size() << endl;

	return 0;
}

