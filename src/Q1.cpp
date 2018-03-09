#include "common_tools.h"

using namespace std;

struct Node
{
	Node() : data(-1), next(NULL) {}
	Node(int d) : data(d), next(NULL) {}
	~Node() {
		if (next) delete next;
	}
	void set_next( Node* n) { next = n; }

	int data;
	struct Node *next;
};


void create_linked_list(const vector<int>& v, Node** head) {
	if (v.size() == 0) return;
	RUNTIME_ASSERT(v.front() >= 0, "invalid negative input: " << v.front());
	(*head) = new Node(v.front());
	Node* tmp = *head;
	for (unsigned long i = 1; i < v.size(); ++i) {
		RUNTIME_ASSERT(v[i] >= 0, "invalid negative input: " << v[i]);
		tmp->set_next(new Node(v[i]));
		tmp = tmp->next;
	}
}

ostream& operator << (ostream& os, Node* head) {
	if (head == NULL) return os;
	os << head->next << " " << head->data; 
	return os;
}

void PrintReverse(Node* head) {
	cout << "[" << head << " ]" << endl;
}

int main(int argc, char* argv[]) try
{
	vector<int> heights{ 0, 10, 20, 50, 80, 100 };
	Node *head = NULL;
	create_linked_list(heights, &head);
	PrintReverse(head);
	delete head;
}
catch (exception& e) {
	cout << e.what() << endl;
	return EXIT_FAILURE;
}
