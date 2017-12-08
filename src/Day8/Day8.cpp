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

bool evalCmp(const string& cmpOp, int cmpReg, int cmpAmt)
{
	if (cmpOp == ">")
		return cmpReg > cmpAmt;
	else if (cmpOp == ">=")
		return cmpReg >= cmpAmt;
	else if (cmpOp == "<")
		return cmpReg < cmpAmt;
	else if (cmpOp == "<=")
		return cmpReg <= cmpAmt;
	else if (cmpOp == "==")
		return cmpReg == cmpAmt;
	else if (cmpOp == "!=")
		return cmpReg != cmpAmt;
	else
		cout << "Unrecognized condition: " << cmpOp << endl;
}

int main()
{
    vector<string> lines;
    vector<vector<string>> lines_split;

    
	string input;
	unordered_map<string, int> registers;

	int maxRegisterEver = INT_MIN;

    while (getline(cin, input) && !input.empty())
    {
		vector<string> parts = split(input, " ");

		int& reg = registers[parts[0]];
		string& op = parts[1];
		int amount = stoi(parts[2]);
		int& cmpReg = registers[parts[4]];
		string comparator = parts[5];
		int cmpAmt = stoi(parts[6]);

		if (evalCmp(comparator, cmpReg, cmpAmt))
		{
			if (op == "inc")
				reg += amount;
			else
				reg -= amount;
		}
		maxRegisterEver = max(maxRegisterEver, reg);
    }

	int maxRegister = INT_MIN;
	for (auto& p : registers)
	{
		maxRegister = max(maxRegister, p.second);
	}

	cout << "Max register: " << maxRegister << endl;
	cout << "Max register (ever): " << maxRegisterEver << endl;

    return 0;
}

