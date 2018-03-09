#include "common_tools.h"

using namespace std;

typedef table<int> map_type;
typedef table<bool> indicator_type;

void grow_blob(const map_type& map, indicator_type& indicator, vector<point>& blob) {
	RUNTIME_ASSERT(map.nr() == indicator.nr() && map.nc() == indicator.nc(),
		"map - indicator size mismatch"
		<< "\n\t map.nr(): " << map.nr()
		<< "\n\t map.nc(): " << map.nc()
		<< "\n\t indicator.nr(): " << indicator.nr()
		<< "\n\t indicator.nc(): " << indicator.nc()
		);
	unsigned long init_size = blob.size();
	for (auto p : blob) {
		for (long x = -1; x <= 1; ++x)
			for (long y = -1; y <= 1; ++y)
			{
				if (x == 0 && y == 0) continue;
				else if (x == 0 || y == 0) {
					point q(p.x() + x, p.y() + y);
					if (map.contains(q) && map(q) == map(p) && indicator(q)) {
						indicator.set(q, false);
						blob.push_back(q);
					}
				}
				else continue;
			}
	}

	if (blob.size() == init_size) return;
	else grow_blob(map, indicator, blob);
}

void make_blobs(const map_type& map, indicator_type& indicator, vector<vector<point>>& blobs) {
	RUNTIME_ASSERT(map.nr() == indicator.nr() && map.nc() == indicator.nc(),
		"map - indicator size mismatch"
		<< "\n\t map.nr(): " << map.nr()
		<< "\n\t map.nc(): " << map.nc()
		<< "\n\t indicator.nr(): " << indicator.nr()
		<< "\n\t indicator.nc(): " << indicator.nc()
		);

	vector<point> blob;

	for (unsigned long r = 0; r < map.nr(); ++r)
	{
		bool found = false;
		for (unsigned long c = 0; c < map.nc(); ++c) {
			if (indicator(r, c)) {
				blob.push_back(point(r, c));
				indicator.set(r, c, false);
				found = true;
				break;
			}
		}
		if (found) break;
	}

	if (blob.size() == 0) return; // finished
	grow_blob(map, indicator, blob);
	blobs.push_back(blob);
	make_blobs(map, indicator, blobs);
}

vector<vector<point>> partition(const map_type& map) {
	indicator_type indicator(map.nr(), map.nc(), true);
	vector<vector<point>> blobs;
	make_blobs(map, indicator, blobs);

	return blobs;
}

int main(int argc, char* argv[]) try
{
	map_type map({
		{1, 1, 1, 0},
		{1, 2, 2, 0},
		{1, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 3},
		{0, 0, 0, 3}
	});

	vector<vector<point>> blobs = partition(map);

	unsigned long max_size = 0;

	for (unsigned long i = 0; i < blobs.size(); ++i)
	{
		if (max_size < blobs[i].size()) max_size = blobs[i].size();
		cout << "region[" << i << "] = " << blobs[i] << endl;
	}

	cout << "maximum region area: " << max_size << endl
		<< "number of regions: " << blobs.size() << endl;
}
catch (exception& e) {
	cout << e.what() << endl;
	return EXIT_FAILURE;
}
