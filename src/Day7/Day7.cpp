#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <set>

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

struct Disc
{
	string name;
	int weight;

	vector<string> subDiscs;
};

vector<Disc> discInput;
unordered_map<string, Disc> discHash;
set<string> discNames;

int GetWeight(const string& start)
{
	Disc& d = discHash[start];
	int weight = d.weight;
	for (auto& subTower : d.subDiscs)
	{
		weight += GetWeight(subTower);
	}
	return weight;
}

int FindUnbalance(const string& start, int ideal)
{
	Disc& d = discHash[start];

	vector<int> weightsArr;
	unordered_map<int, int> weights;

	for (auto& subTower : d.subDiscs)
	{
		weightsArr.push_back(GetWeight(subTower));
		weights[weightsArr.back()]++;
	}

	if (weights.size() > 1)
	{
		int idealWeight = 0;
		for (auto& p : weights)
		{
			if (p.second > 1)
				idealWeight = p.first;
		}

		for (size_t i = 0; i < weightsArr.size(); ++i)
		{
			ideal -= discHash[d.subDiscs[i]].weight;
			if (weights[weightsArr[i]] == 1)
				return FindUnbalance(d.subDiscs[i], idealWeight);
		}
	}
	else
	{
		for (auto w : weightsArr)
			ideal -= w;
	}

	return d.weight - ideal;
}

int main()
{
    string input;
    while (getline(cin, input) && !input.empty())
    {
		vector<string> input_split = split(input, " ");

		discInput.push_back(Disc());
		discInput.back().name = input_split[0];
		discInput.back().weight = stoi(input_split[1].substr(1, input_split[1].size() - 2));

		if (input_split.size() > 2)
		{
			for (size_t i = 3; i < input_split.size(); ++i)
				discInput.back().subDiscs.push_back(input_split[i].substr(0, input_split[i].find(',')));
		}

		discNames.insert(discInput.back().name);

		discHash[discInput.back().name] = discInput.back();
    }

	for (auto& disc : discInput)
	{
		for (auto& subDisc : disc.subDiscs)
		{
			auto iter = discNames.find(subDisc);
			if (iter != end(discNames))
				discNames.erase(iter);
		}
	}

	for (auto& name : discNames)
	{
		cout << "Name: " << name << endl;
		cout << "Unbalance: " << FindUnbalance(name, 0) << endl;
	}

    return 0;
}

