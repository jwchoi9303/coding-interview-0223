#ifndef COMMON_TOOLS_Hh
#define COMMON_TOOLS_Hh

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define RUNTIME_ASSERT(_exp,_message)                          \
{if (!(_exp))                                                    \
{                                                                  \
	std::ostringstream sout;                                       \
	sout << "\n\nError detected at line " << __LINE__ << ".\n";    \
	sout << "Error detected in file " << __FILE__ << ".\n";        \
	sout << "Error detected in function " << __FUNCTION__ << ".\n\n";  \
	sout << "Failing expression was " << #_exp << ".\n";           \
	sout << std::boolalpha << _message << "\n";                    \
	throw runtime_error(sout.str());							   \
}}

#define printv(x) cout << #x << " = " << x << endl;

//array_type could be std::vector<T> where T has comparison operators <, >, <= and >=
//or could be string as well (sorted in alphabetical order in this case)
template<typename array_type>
array_type quick_sort(const array_type& arr, bool ascending = true) {
	if (arr.size() <= 1) return arr;
	else {
		auto pivot = arr[arr.size() / 2];
		array_type smaller, equal, larger;
		for (auto x : arr) {
			if (x == pivot) equal.push_back(x);
			else if (x < pivot) smaller.push_back(x);
			else larger.push_back(x);
		}

		smaller = quick_sort(smaller, ascending);
		larger = quick_sort(larger, ascending);

		array_type sorted_arr;
		if (ascending) {
			sorted_arr.insert(sorted_arr.end(), smaller.begin(), smaller.end());
			sorted_arr.insert(sorted_arr.end(), equal.begin(), equal.end());
			sorted_arr.insert(sorted_arr.end(), larger.begin(), larger.end());
		}
		else {
			sorted_arr.insert(sorted_arr.end(), larger.begin(), larger.end());
			sorted_arr.insert(sorted_arr.end(), equal.begin(), equal.end());
			sorted_arr.insert(sorted_arr.end(), smaller.begin(), smaller.end());
		}

		return sorted_arr;
	}
}

template<typename entry_type>
ostream& operator << (ostream& os, const vector<entry_type>& vec) {
	if (vec.size() == 0) { os << "[ ]"; return os; }
	else {
		os << "[";
		for (unsigned long i = 0; i < vec.size(); ++i) {
			if (i != 0) os << ", ";
			os << vec[i];
		}
		os << "]";
		return os;
	}
}

template<typename T>
string stringify(const T& obj) {
	ostringstream sout;
	sout << obj;
	return sout.str();
}

class point {
public:
	point() : _x(0), _y(0) {}
	point(long xx, long yy) : _x(xx), _y(yy) {}

	const long& x() const { return _x; }

	const long& y() const { return _y; }

	long& x() { return _x; }

	long& y() { return _y; }

private:
	long _x, _y;
};

ostream& operator << (ostream& os, const point& p) {
	os << "[" << p.x() << ", " << p.y() << "]"; return os;
}

template<typename T>
class table {
public:

	table(){}

	table(const vector<vector<T>>& data) : rows(data) {
#ifdef _DEBUG
		for (auto row : rows) {
			RUNTIME_ASSERT(row.size() == rows.front().size(), "inconsistent row size");
	}
#endif
	}

	table(unsigned long nr, unsigned long nc) {
		set_size(nr, nc);
	}

	table(unsigned long nr, unsigned long nc, const T& val) {
		set_size(nr, nc);
		for (unsigned long r = 0; r < nr; ++r)
			for (unsigned long c = 0; c < nc; ++c)
				rows[r][c] = val;
	}

	void set_size(unsigned long nr, unsigned long nc) {
		rows = vector<vector<T>>(nr, vector<T>(nc, T()));
	}

	long nr() const { return rows.size(); }

	long nc() const { 
		if (rows.size() > 0)
			return rows.front().size();
		else return 0;
	}

	bool contains(const point& p) const {
		return p.x() >= 0 && p.x() < this->nr() && p.y() >= 0 && p.y() < this->nc();
	}

	void set(const point& p, const T& val) {
		RUNTIME_ASSERT(this->contains(p),
			"this object doesn't contain the given point"
			<< "\n\t this->nr(): " << this->nr()
			<< "\n\t this->nc(): " << this->nc()
			<< "\n\t p.x(): " << p.x()
			<< "\n\t p.y(): " << p.y()
			);
		rows[p.x()][p.y()] = val;
	}

	T operator() (const point& p) const {
		RUNTIME_ASSERT(this->contains(p),
			"this object doesn't contain the given point"
			<< "\n\t this->nr(): " << this->nr()
			<< "\n\t this->nc(): " << this->nc()
			<< "\n\t p.x(): " << p.x()
			<< "\n\t p.y(): " << p.y()
			);
		return rows[p.x()][p.y()];
	}

	void set(const long& r, const long& c, const T& val) {
		RUNTIME_ASSERT(r < this->nr() && c < this->nc(),
			"const " << typeid(T).name() << "& table<" << typeid(T).name() << ">::operator(): index out of range"
			<< "\n\t r: " << r
			<< "\n\t c: " << c
			<< "\n\t this->nr(): " << this->nr()
			<< "\n\t this->nc(): " << this->nc()
			);
		rows[r][c] = val;
	}

	T operator() (long r, long c) const {
		RUNTIME_ASSERT(r < this->nr() && c < this->nc(),
			"const " << typeid(T).name() << "& table<" << typeid(T).name() << ">::operator(): index out of range"
			<< "\n\t r: " << r
			<< "\n\t c: " << c
			<< "\n\t this->nr(): " << this->nr()
			<< "\n\t this->nc(): " << this->nc()
			);
		return rows[r][c];
	}

	vector<T> row(long r) const {
		RUNTIME_ASSERT(r < this->nr(),
			"vector<" << typeid(T).name() << "> table<" << typeid(T).name() << ">::row(): index out of range"
			<< "\n\t r: " << r
			<< "\n\t this->nr(): " << this->nr()
			);
		return rows[r];
	}

	vector<T> col(long c) const {
		RUNTIME_ASSERT(c < this->nc(),
			"vector<" << typeid(T).name() << "> table<" << typeid(T).name() << ">::col(): index out of range"
			<< "\n\t c: " << c
			<< "\n\t this->nc(): " << this->nc()
			);
		vector<T> column;
		for (long r = 0; r < nr(); ++r) {
			column.push_back(rows[r][c]);
		}
		return column;
	}

	template<typename T>
	friend ostream& operator << (ostream& os, const table<T>& t);

private:
	vector<vector<T>> rows;
};

template<typename T>
ostream& operator << (ostream& os, const table<T>& t) {
	os << endl;
	for (auto row : t.rows) {
		os << row << endl;
	}
	return os;
}

#endif // COMMON_TOOLS_Hh
