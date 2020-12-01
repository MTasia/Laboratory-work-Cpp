#ifndef STRUCTURE
#define STRUCTURE

#include <string>
#include <vector>

using namespace std;

class tree {
protected:
	std::string data;
	vector<tree*> children;

public:

	tree() { data = ""; }
	tree(std::string& root) { data = root; }

	std::string get_data() { return data; }

	void add_child(tree* child) { children.push_back(child); }

	int child_num() { return children.size(); }

	tree* first_child() { return children[0]; }

	tree* next_child() {
		static int counter = 0;
		if (counter < children.size() - 1) {
			return children[++counter];
		}
		counter = 0;
		return NULL;
	}
};

#endif 
