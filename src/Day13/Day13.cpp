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
	int position = 0;
	int direction = 1;
};

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

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

	for (int delay = 0; ; delay++)
	{
		if (delay % 10000 == 0)
			cout << "Delay: " << delay << endl;

		bool good = true;
		for (auto& scanner : scanners)
		{
			if ((scanner.depth + delay) % ((scanner.range - 1) * 2) == 0)
			{
				good = false;
				break;
			}
		}

		if (good)
		{
			cout << "Min delay = " << delay << endl;
			break;
		}
	}

	//for (int delay = 0; ; delay++)
	//{
	//	int pos = -1;
	//	int score = 0;

	//	if (delay % 10000 == 0)
	//		cout << "Delay: " << delay << endl;

	//	vector<scanner> scanners = orig_scanners;
	//	for (int i = 0; i < delay; i++)
	//	{
	//		for (auto& scanner : scanners)
	//		{
	//			scanner.position += scanner.direction;
	//			if (scanner.position == 0 && scanner.direction == -1)
	//				scanner.direction = 1;
	//			else if (scanner.position == scanner.range - 1 && scanner.direction == 1)
	//				scanner.direction = -1;
	//		}
	//	}

	//	int scanner_offset = 0;

	//	while (pos <= scanners.back().depth)
	//	{
	//		pos += 1;

	//		while (scanner_offset < scanners.size() && scanners[scanner_offset].depth < pos)
	//			scanner_offset++;

	//		if (scanner_offset >= scanners.size())
	//			break;

	//		if (scanners[scanner_offset].depth == pos && scanners[scanner_offset].position == 0)
	//			score += scanners[scanner_offset].depth * scanners[scanner_offset].range + 1;

	//		if (score != 0)
	//			break;
	//		
	//		for (auto& scanner : scanners)
	//		{
	//			scanner.position += scanner.direction;
	//			if (scanner.position == 0 && scanner.direction == -1)
	//				scanner.direction = 1;
	//			else if (scanner.position == scanner.range - 1 && scanner.direction == 1)
	//				scanner.direction = -1;
	//		}
	//	}

	//	if (score == 0)
	//	{
	//		cout << "Min delay = " << delay << endl;
	//		break;
	//	}
	//	//cout << "Result " << score << endl;
	//}


	return 0;
}

