#include "common_tools.h"

using namespace std;


class point {
public:
	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	int x, y;
};

bool contains(const point& p, const table<int>& map) {
	return p.x >= 0 && p.x < map.nr() && p.y >= 0 && p.y < map.nc();
}

vector<point> find_neighbors(const point& p, const table<int>& map) {
	vector<point> n;
	for (long i = -1; i <= 1; ++i)
	for (long j = -1; j <= 1; ++j)
	{
		point q(p.x + i, p.y + j);
		if (contains(q, map) && map(q.x, q.y) == map(p.x, p.y))
			n.push_back(q);
	}
}

bool contains(point t, vector<point> vt){
	for (auto item : vt) {
		if (item.x == t.x && t.y == item.y) return true;
	}
	return false;
}

void get_blob(vector<point>& blob, point seed, const table<int>& map) {
	
	if (!contains(seed, blob))
		blob.push_back(seed);


	vector<point> neighbors = find_neighbors(seed, map);

	int previous_size = blob.size();
	for (auto n : neighbors) {
		if (!contains(n, blob)) blob.push_back(n);
		get_blob(blob, n, map);
	}

	if (blob.size() == previous_size) return;
}

vector<vector<point>> split_area(table<int>& map) {
	point pivot(-1, -1);
	for (long r = 0; r < map.nr(); ++r)
	for (long c = 0; c < map.nc(); ++c)
	if (map(r, c) != -1)
	{
		pivot = point(r, c);
		break;
	}

	if (pivot.x == -1 && pivot.y == -1) return vector<vector<point>>();

	vector<point> blob;
	get_blob(blob, pivot, map);
	for (auto p : blob) map(p.x, p.y) = -1;

	auto res = split_area(map);
	res.push_back(blob);

	return res;
}

int main(int argc, char* argv[]) try
{
	table<int> map_info({
		{1, 1, 1, 0},
		{1, 2, 2, 0},
		{1, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 3},
		{0, 0, 0, 3}
	});

	
	auto res = split_area(map_info);
	printv(res);

}
catch (exception& e) {
	cout << e.what() << endl;
	return EXIT_FAILURE;
}
