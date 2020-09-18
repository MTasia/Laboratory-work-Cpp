#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <windows.h>

using namespace std;

void div_word(vector<string>&, int);
void print_strings(vector<string>&, int, const char*);
string center(string, int);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	const char* input_file = argv[1];
	const int max_size = atoi(argv[2]);
	const char* output_file = argv[3];
	ifstream in(input_file);
	string line;
	vector<string> words;
	vector<string> strings;
	int j = 0;
	while (getline(in, line)) {
		stringstream sline;
		sline << line;
		copy(istream_iterator<string>(sline), istream_iterator<string>(), inserter(words, words.end()));
		string new_str = "";
		while (words.size() > 0) {
			if (new_str.size() + words[0].size() + 1 < max_size) {
				new_str.append(words[0] + " ");
				words.erase(words.begin());
			}
			else if (new_str.size() + words[0].size() <= max_size) {
				if (new_str.size() + words[0].size() == max_size)
					new_str.append(words[0]);
				else
					new_str.append(words[0] + " ");
				words.erase(words.begin());
			}
			else {
				if (words[0].size() > max_size) {
					div_word(words, max_size);
				}
				strings.push_back(new_str);
				new_str = "";
			}
		}
		strings.push_back(new_str);
	}

	print_strings(strings, max_size, output_file);
}

void div_word(vector<string>& words, int max_size) {
	string right_part = words[0].substr(max_size - 1);
	words[0].erase(max_size - 1);
	words[0].append("-");
	words.insert(words.begin() + 1, right_part);
}

void print_strings(vector<string>& strings, int max_size, const char* output_file) {
	ofstream fout(output_file);
	string new_str;
	for (auto i : strings)
		fout << center(i, max_size) << endl;
}

string center(string str, int max_size) {
	string new_str = "";
	int k = (max_size - str.size()) / 2;
	for (int i = 0; i < k; i++) new_str += " ";
	new_str += str;
	return new_str;
}