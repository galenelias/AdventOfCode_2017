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

struct scanner
{
	int depth = 0;
	int range = 0;
};

std::pair<bool, int> CheckScanners(const vector<scanner>& scanners, int delay)
{
	bool good = true;
	int score = 0;

	for (auto& scanner : scanners)
	{
		if ((scanner.depth + delay) % ((scanner.range - 1) * 2) == 0)
		{
			score += scanner.depth * scanner.range;
			good = false;
		}
	}

	return { good, score };
}

int main()
{
	string input;

	vector<scanner> scanners;

	while (getline(cin, input) && !input.empty())
	{
		vector<string> parts = split(input, ": ");

		scanner s;
		s.depth = stoi(parts[0]);
		s.range = stoi(parts[1]);

		scanners.push_back(s);
	}

	int delay0_score = 0;
	tie(ignore, delay0_score) = CheckScanners(scanners, 0 /*delay*/);
	cout << "Part 1: " << delay0_score << endl;

	bool good = false;
	for (int delay = 0; !good; delay++)
	{
		tie(good, ignore) = CheckScanners(scanners, delay);

		if (good)
			cout << "Min delay = " << delay << endl;
	}

	return 0;
}

