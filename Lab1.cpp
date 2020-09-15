#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "rus");
	char * name = argv[1];
	ifstream in(name);
	string line;
	vector<string> words;
	while (getline(in, line))
	{
		stringstream sline;
		sline << line;
		copy(istream_iterator<string>(sline), istream_iterator<string>(), inserter(words, words.end()));
	}
	
	for (auto i : words) {
		cout << i << " ";
	}
	cout << endl << endl;
}