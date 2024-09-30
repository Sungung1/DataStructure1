#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <cassert>
using namespace std;



struct Person {
	string name, address;
	string phone, email, web;
};

vector<Person> directory;


vector<string> split_line(string& line, char delimiter) {
	vector<string> tokens;
	stringstream sstream(line);
	string str;
	while (getline(sstream, str, delimiter))
		tokens.push_back(str);
	return tokens;
}

string trim(string str) {
	int s = 0, t = str.length() - 1;;
	while (s < str.length() && isspace(str[s]))
		s++;
	while (t >= 0 && isspace(str[t]))
		t--;
	if (s <= t)
		return str.substr(s, t - s + 1);
	else
		return "";
}

void load_data(string file_name) {
	string line;

	ifstream infile(file_name);

	while (getline(infile, line)) {
		vector<string> tokens = split_line(line, '\t');

		assert(tokens.size() >= 4 && tokens.size() <= 5);

		Person p;
		p.name = tokens.at(0);
		p.address = tokens.at(1);
		p.phone = tokens.at(2);
		p.email = tokens.at(3);
		if (tokens.size() == 5)
			p.web = tokens.at(4);

		directory.push_back(p);
	}
	infile.close();
}

void print_person(Person& p) {
	cout << p.name << ":" << endl;
	cout << " Address : " << p.address << ":" << endl;
	cout << " Phone : " << p.phone << ":" << endl;
	cout << " Email : " << p.email << ":" << endl;
	cout << " Web : " << p.web << ":" << endl;

}

void list_directory() {
	for (auto& person : directory) {
		print_person(person);
	}
}

void search_directory(string& prefix) {
	stringstream ss(prefix);
	string condition;
	vector<string> conditions;

	// 검색어를 & 기준으로 분리하고
	while (getline(ss, condition, '&')) {
		conditions.push_back(trim(condition));
	}

	for (auto& p : directory) {
		bool all_match = true;
		for (const auto& cond : conditions) {
			// 조건 하나라도 안맞으면 break씀
			if (p.name.find(cond) == string::npos &&
				p.address.find(cond) == string::npos &&
				p.phone.find(cond) == string::npos &&
				p.email.find(cond) == string::npos &&
				p.web.find(cond) == string::npos) {
				all_match = false;
				break;
			}
		}

		// 모든 조건 일치 출력
		if (all_match) {
			print_person(p);
		}
	}
}







Person get_person_info(string name) {
	Person p;
	string line;
	p.name = name;
	cout << " Address : ";
	getline(cin, line);
	p.address = trim(line);
	cout << " Phone: ";
	getline(cin, line);
	p.phone = trim(line);
	cout << "Email : ";
	getline(cin, line);
	p.email = trim(line);
	cout << " Web: ";
	getline(cin, line);
	p.web = trim(line);
	return p;
}

void add_person(string name) {
	Person p = get_person_info(name);
	auto it = directory.begin();
	while (it != directory.end() && it->name <= name)
		it++;
	it = directory.insert(it, p);
}

void delete_person(string name)
{
	string answer;
	for (auto it = directory.begin(); it != directory.end(); )
	{
		if (it->name.compare(0, name.size(), name) == 0) {
			cout << "Want to delete " << it->name << "'? ";
			cin >> answer;
			if (answer == "yes" || answer == "y")
				it = directory.erase(it);
			else
				it++;
		}
		else if (it->name.compare(0, name.size(), name) > 0)
			break;
		else
			it++;
	}
}

void save_directory() {
	ofstream outfile("address.tsv");
	for (auto& p : directory)
		outfile << p.name << '\t' << p.address << '\t' << p.phone
		<< '\t' << p.email << '\t' << p.web << endl;
	outfile.close();
}

int main() {
	load_data("address.tsv");
	string command, arguments;
	while (1) {
		cout << "$ ";
		cin >> command;
		cin.ignore();
		if (command == "exit")
			break;
		if (command == "list")
			list_directory();
		else if (command == "find")
		{
			getline(cin, arguments);
			string name = trim(arguments);
			if (name.length() <= 0)
				continue;
			search_directory(name);
		}
		else if (command == "add")
		{
			getline(cin, arguments);
			string name = trim(arguments);
			if (name.length() <= 0)
				continue;
			add_person(name);
		}
		else if (command == "delete")
		{
			getline(cin, arguments);
			string name = trim(arguments);
			if (name.length() <= 0)
				continue;
			delete_person(name);
		}
		else if (command == "save")
		{
			save_directory();
		}
		else if (command == "search") 
		{
			getline(cin, arguments);
			string query = trim(arguments);
			if (query.length() <= 0)
				continue;
			search_directory(query);  
		}
	}
	return 0;
}
