#include "common_tools.h"
#include <map>

using namespace std;

vector<unsigned long> find_indices_of(const char& c, const string& s) {
	vector<unsigned long> indices;
	for (unsigned long i = 0; i < s.length(); ++i)
	if (s[i] == c) indices.push_back(i);
	return indices;
}

vector<string> split_by_spaces(const string& s) {
	std::istringstream buf(s);
	std::istream_iterator<std::string> beg(buf), end;

	std::vector<std::string> tokens(beg, end);

	return tokens;
}

vector<string> split(const string& s) {
	char a = '\n';
	// find the first lower case letter
	for (unsigned long i = 0; i < s.size(); ++i) {
		if (islower(s[i])) {
			a = s[i];
			break;
		}
	}

	if (a == '\n') return split_by_spaces(s); // no lower case letter found => just split by spaces

	vector<unsigned long> indices = find_indices_of(a, s);

	if (indices.size() == 2) // operation 1
	{
		vector<string> head;
		head.push_back(s.substr(indices.front() + 1, indices.back() - indices.front() - 1));
		if (indices.back() < s.length() - 1)
		{
			vector<string> tail = split(s.substr(indices.back() + 1, indices.size() - indices.back() - 1));
			head.insert(head.end(), tail.begin(), tail.end());
		}

		return head;
	}
	else { // operation 2
		string decoded;
		for (unsigned long i = indices.front() - 1; i <= indices.back() + 1; ++i) {
			if (isupper(s[i])) decoded.push_back(s[i]);
		}
		vector<string> head;
		head.push_back(decoded);
		if (indices.back() < s.length() - 2)
		{
			vector<string> tail = split(s.substr(indices.back() + 2, indices.size() - indices.back() - 3));
			head.insert(head.end(), tail.begin(), tail.end());
		}

		return head;
	}
}

void parse(istream& in, int& num_inst, vector<string>& instructions) {
	in >> num_inst;
	for (int i = 0; i < num_inst; ++i)
	{
		string line;
		in >> line;
		instructions.push_back(line);
	}
}

int main(int argc, char* argv[]) try
{
	int num_inst;
	vector<string> instructions;

	parse(cin, num_inst, instructions);

	for (auto s : instructions) {
		auto res = split(s);
		cout << res << endl;
	}
}
catch (exception& e) {
	cout << e.what() << endl;
	return EXIT_FAILURE;
}
