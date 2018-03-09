#include "common_tools.h"

using namespace std;

void parse(istream& in, vector<int>& req, int& nd) {
	in >> nd;

	req.clear();
	string line;

	int val;
	while (1)
	{
		in >> val;
		RUNTIME_ASSERT(val >= 0, "invalid negative input given: " << val);
		req.push_back(val);
		if (in.get() == '\n') break;
	}
}

unsigned long max_customers(const vector<int>& req, const int& nd) {
	vector<int> sorted_req = quick_sort(req);
	int sum = 0;
	for (unsigned long i = 0; i < sorted_req.size(); ++i) {
		sum += sorted_req[i];
		if (sum > nd) return i;
	}

	return 0; // in case req is an empty array
}

int main(int argc, char* argv[]) try
{
	vector<int> requests;
	int ndrones;

	parse(cin, requests, ndrones); // parse from console

	int answer = max_customers(requests, ndrones);

	cout << answer << endl;
}
catch (exception& e) {
	cout << e.what() << endl;
	return EXIT_FAILURE;
}
