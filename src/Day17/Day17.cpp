#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
	string input;
	getline(cin, input);
	int skip = stoi(input);

	{	// Part 1
		vector<int> buffer;
		buffer.push_back(0);

		int pos = 0;
		for (int i = 0; i < 2017; ++i)
		{

			pos = (pos + skip) % buffer.size();
			buffer.insert(buffer.begin() + ++pos, i + 1);
		}

		auto iter = find(buffer.begin(), buffer.end(), 2017);
		cout << "Part 1: " << *(iter + 1) << endl;
	}

	{
		int pos = 0;
		int after_0 = 0;
		size_t buffer_size = 1;

		for (int i = 0; i < 50000000; ++i)
		{
			pos = ((pos + skip) % buffer_size) + 1;
			if (pos == 1)
				after_0 = i + 1;
			buffer_size++;
		}

		cout << "Part 2: " << after_0 << endl;
	}

	return 0;
}

