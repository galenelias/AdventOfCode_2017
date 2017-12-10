#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

string input;
int score = 0;
int garbage = 0;

int GetScore(size_t offset/*, size_t nest*/)
{
	int nest = 0;

	while (offset < input.size())
	{
		if (input[offset] == '{')
		{
			nest++;
			offset++;
		}
		else if (input[offset] == '}')
		{
			score += nest;
			nest--;
			offset++;
		}
		else if (input[offset] == '<')
		{
			// parse garbage
			offset++;
			while (input[offset] != '>')
			{
				if (input[offset] == '!')
					offset += 2;
				else
				{
					garbage++;
					offset++;
				}
			}
			offset++;
		}
		else if (input[offset] == ',')
		{
			offset++;
		}
		else
		{
			cerr << "Unexpected input: " << input[offset] << endl;
			return nest;
		}

	}
}

int main()
{
	vector<string> lines;
	vector<vector<string>> lines_split;

	getline(cin, input);
	GetScore(0);
	//cout << "Result " << GetScore(0, 0) << endl;
	cout << "Result " << score << endl;
	cout << "Garbage " << garbage << endl;
	return 0;
}

