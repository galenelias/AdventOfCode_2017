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

vector<string> program;
void SendValue(int64_t val, int64_t programId);

class Program
{
public:
	Program(int64_t id)
		: m_id(id)
	{
		values["p"] = id;
	}

	bool RunOne()
	{
		// cout << "[" << m_id << "] pc = " << pc << endl;
		// print_values();
		// cout << endl;
		if (pc >= program.size())
			return false;

		vector<string> a = split(program[pc++], " ");

		if (a[0] == "set") {
			values[a[1]] = get_value(a[2]);
		}
		else if (a[0] == "add") {
			values[a[1]] += get_value(a[2]);
		}
		else if (a[0] == "mul") {
			values[a[1]] *= get_value(a[2]);
		}
		else if (a[0] == "mod") {
			values[a[1]] %= get_value(a[2]);
		}
		else if (a[0] == "snd")
		{
			send_count++;
			SendValue(get_value(a[1]), m_id);
			// last_sound = get_value(a[1]);
		}
		else if (a[0] == "rcv")
		{
			if (!queue.empty())
			{
				values[a[1]] = queue.front();
				queue.erase(queue.begin());
				cout << "[" << m_id << "] popped " << values[a[1]] << " (size = " << queue.size() << ")" << endl;
			}
			else
			{
				cout << "[" << m_id << "] blocked on RCV" << endl;
				pc--;
				return false;
			}
		}
		else if (a[0] == "jgz")
		{
			if (get_value(a[1]) > 0)
			{
				pc += get_value(a[2]) - 1;
			}
		}
		return true;
	}

	int64_t get_value(const string& s)
	{
		if (s.find_first_of("0123456789") != string::npos) {
			return stoi(s);
		}
		else {
			return values[s];
		}
	}

	void QueueValue(int64_t val)
	{
		queue.push_back(val);
	}

	void print_values()
	{
		for (auto& p : values)
			cout << "[" << m_id << "]\t" << p.first << " = " << p.second << endl;
	}


	int pc = 0;
	int64_t m_id;
	vector<int64_t> queue;
	unordered_map<string, int64_t> values;
	int send_count = 0;
};

Program programs[2] { 0, 1};

void SendValue(int64_t val, int64_t programId)
{
	int destPid = programId == 0 ? 1 : 0;
	cout << "Pid " << programId << " sent " << val << endl;
	programs[destPid].QueueValue(val);
}

int main()
{
	string input;
	while (getline(cin, input) && !input.empty())
	{
		program.push_back(input);
	}

	while (programs[0].RunOne() || programs[1].RunOne())
		;
	
	// cout << "Part 1: " << recovered_sound << endl;
	cout << "Part 2: " << programs[1].send_count << endl;
	return 0;
}

