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

int main()
{
    vector<string> lines;
    vector<vector<string>> lines_split;

    string input;
    while (getline(cin, input) && !input.empty())
    {
        lines.push_back(input);
        lines_split.push_back(split(input, " "));
    }

    cout << "Lines split:\n";
    for (const auto& l : lines_split)
    {
        cout << "(" << l.size() << ") ";
        for (const auto& s : l)
            cout << "[" << s << "] ";
        cout << "\n";
    }

    // cout << "Result " << 0 << endl;
    return 0;
}

