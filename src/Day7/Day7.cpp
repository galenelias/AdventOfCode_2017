#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<string> split(const string &input, const string &separator)
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

struct Disc
{
	string name;
	int weight = 0;
	vector<string> subDiscs;

	int totalWeight = 0;
};

unordered_map<string, Disc> discMap;

int ComputeAndCacheWeight(const string& start)
{
	Disc& d = discMap[start];
	int weight = d.weight;
	for (auto& subTower : d.subDiscs)
		weight += ComputeAndCacheWeight(subTower);
	
	// Cache off tower weight
	d.totalWeight = weight;
	return weight;
}

int FindUnbalance(const string& rootDisc, int expectedWeight)
{
	const Disc& d = discMap[rootDisc];
	unordered_map<int, int> weightBuckets;

	for (auto& subTower : d.subDiscs)
		weightBuckets[discMap[subTower].totalWeight]++;

	// If our sub-towers are uneven, recurse down the 'odd man out'
	if (weightBuckets.size() > 1)
	{
		int idealWeight = 0;
		for (auto& p : weightBuckets)
		{
			if (p.second > 1)
				idealWeight = p.first;
		}

		for (auto &subTower : d.subDiscs)
		{
			if (weightBuckets[discMap[subTower].totalWeight] == 1)
				return FindUnbalance(subTower, idealWeight);
		}
		cerr << "Unexpected!! Should have found single unbalanced child disc under " << rootDisc << "\n";
		return -1;
	}
	else
	{
		// Otherwise, we're the unbalanced disc, so figure out how much we should weigh by
		// removing our children's weight from the expected weight
		for (auto &subTower : d.subDiscs)
			expectedWeight -= discMap[subTower].totalWeight;
	}

	// return d.weight - expectedWeight;
	return expectedWeight;
}

int main()
{
	unordered_set<string> allDiscNames;

	string line;
	while (getline(cin, line) && !line.empty())
	{
		vector<string> line_split = split(line, " -> ");
		vector<string> nameAndWeight = split(line_split[0], " ");

		Disc d;
		d.name = nameAndWeight[0];
		d.weight = stoi(nameAndWeight[1].substr(1, nameAndWeight[1].size() - 2));

		if (line_split.size() > 1)
			d.subDiscs = split(line_split[1], ", ");

		allDiscNames.insert(d.name);

		discMap[d.name] = d;
	}

	for (auto& discKV : discMap)
		for (auto& subDisc : discKV.second.subDiscs)
			allDiscNames.erase(subDisc);

	if (allDiscNames.size() != 1)
	{
		cout << "Bad input. " << allDiscNames.size() << " base discs found.\n";
		return -1;
	}

	string baseDisc = *(allDiscNames.begin());
	cout << "Base disc: " << baseDisc << endl;

	ComputeAndCacheWeight(baseDisc);
	cout << "Corrected weight: " << FindUnbalance(baseDisc, 0) << endl;

	return 0;
}

